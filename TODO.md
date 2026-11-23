# Sandtris Refactor TODO List

This document tracks the full architectural and performance refactor of Sandtris.

**Execution Order**: Start strictly at **Phase A** and work top-to-bottom through **Phase E** (enforcing the Function Design & Code Architecture rules) before proceeding to the **Legacy / Subsequent Performance Phases** pushed to the bottom. Doing Phases A–E first eliminates live UB, global state, and god-object coupling so the later PMR/SoA/lock-free work sits on a clean, testable foundation.

---

## Phase A: Value Types, Compile-Time Tables & Header Hygiene (START HERE)
*Zero external dependencies. Kills SIOF syscalls, per-TU `unordered_map` allocations, uninitialized POD UB, and unscoped/unvalidated primitives.*

- [ ] **Kill Dynamic Globals & Header Pollution** ([`include/constant.hpp`](include/constant.hpp), [`include/SFX.hpp`](include/SFX.hpp), [`include/Animation.hpp`](include/Animation.hpp), [`include/Button.hpp`](include/Button.hpp), [`include/PersonalBest.hpp`](include/PersonalBest.hpp)):
  - Remove non-`inline` namespace-scope dynamic globals (`base_path` calling `sdlgame::get_base_path()` before `main()`, dead `client_cores` calling `hardware_concurrency()`, `font_path`, `sfx_path`, and runtime-parsed `Color("...")` globals). Compute `asset_root` once in `main()` after `sdlgame::init()` and inject it.
  - Convert compile-time constants (`dx`/`dy`, rects, speeds, colors) to `inline constexpr` (`std::array`, RGBA integer literals) inside `namespace sandtris::cfg`.
  - Strip all file-scope `using` and `namespace fs = ...` declarations from headers.
- [ ] **Replace Unscoped Enums & Split Event Domains** ([`include/constant.hpp`](include/constant.hpp), [`include/TetrisEvent.hpp`](include/TetrisEvent.hpp)):
  - Replace `Window_Constant` and `grid_size` enums with `inline constexpr` values.
  - Replace unscoped bitmask `SandShift` with dense `enum class CellKind : uint8_t { Empty, Red, Yellow, Blue, Green, Wall }` and `enum class SandColor : uint8_t { Red, Yellow, Blue, Green }`.
  - Decouple simulation events from SDL (`TetrisEvent.hpp`): return a pure, trivially-copyable `struct SimTickEvents` (`cleared_cells`, `merged`, `game_over`, `slammed`) from physics; keep UI/app events in a scoped `enum class AppEvent : uint32_t`.
- [ ] **Make `Tetrimino` & `Sand` Pure, Trivial, Compile-Time Driven** ([`include/Tetrimino.hpp`](include/Tetrimino.hpp), [`src/Tetrimino.cpp`](src/Tetrimino.cpp), [`include/tetriminoes.hpp`](include/tetriminoes.hpp), [`src/tetriminoes.cpp`](src/tetriminoes.cpp), [`include/Sand.hpp`](include/Sand.hpp), [`src/Sand.cpp`](src/Sand.cpp)):
  - Delete header-defined `const std::unordered_map<char, ShapeInfo> ShapeInfoList` and `I_info..L_info` (currently heap-allocated per TU). Replace with `inline constexpr` tables indexed by `enum class TetriminoType : uint8_t`: 4x7 masks, exact 4-block occupied `(dx, dy)` offsets, and `{min_col, max_col}` bounds.
  - Make `Tetrimino` a 3-byte `std::is_trivially_copyable` value type (`type`, `color`, `rotation < 4`) with inline `constexpr` `rotate_cw()` and `mask()`; remove `src/Tetrimino.cpp`.
  - Replace the 7 copy-pasted `Tetriminoes::I()..L()` functions and global RNG with a single pure `template <std::uniform_random_bit_generator Rng> Tetrimino random_tetrimino(Rng&)` function.
  - Remove global RNG (`sdlgame::random::randint`) from `Sand::Sand()`; make cell storage trivial (`= default`, zero-init, `static_assert(std::is_trivially_copyable_v<...>)`). Move mutable `extern SandShiftColor` out of simulation into a `constexpr` renderer LUT.
  - Upgrade `GridPos` ([`include/Grid.hpp`](include/Grid.hpp)) from `uint8_t` (overflows if `GRID_HEIGHT > 253`) to `uint16_t` or flat `uint32_t` cell indices with `static_assert(std::is_trivially_copyable_v<...>)`.
- [ ] **Introduce Zero-Cost Invariant Wrapper Types** (new header, e.g., `include/Types.hpp`):
  - Define `std::is_trivially_copyable` wrappers validated once at construction: `PositiveFloat`, `NormalizedFloat`, `NormalizedVolume` (rejects `NaN`, clamps `[0, 1]`), `PositiveSeconds`, `PositiveFrameRate` (precomputes `1.0 / hz`), `ViewportSize` (`w > 0 && h > 0`).
- [ ] **Fix Build-Script Python Hygiene** ([`conanfile.py`](conanfile.py)):
  - Add explicit type annotations to all class attributes (`settings`, `requires`, `default_options`) and method signatures (`-> None`). Delete dead no-op `requirements()`/`configure()` stubs and hoist `CMakeDeps`/`CMakeToolchain` imports to module top.

---

## Phase B: Core Simulation Purity & Hot-Path Mechanical Sympathy
*Highest performance & correctness ROI. Fixes active physics/OOB bugs and makes the entire simulation deterministically unit-testable in GoogleTest without SDL.*

- [ ] **Decouple `SandSimulation` from `GridRenderer` & `Game&`** ([`include/Grid.hpp`](include/Grid.hpp), [`src/Grid.cpp`](src/Grid.cpp), [`include/TetriminoController.hpp`](include/TetriminoController.hpp), [`src/TetriminoController.cpp`](src/TetriminoController.cpp)):
  - Extract pure, SDL-free `SandSimulation` owning SoA `SandField` (`cell_kind` 1B/cell hot physics + `color_noise` 1B/cell render-only), grid-local `ActivePiece` (eliminating repeated `- GRID_X` / `- GRID_Y` conversions), `Tetrimino next`, single `uint64_t score` (remove RNG `score1`/`score2` split), and pre-allocated BFS scratch buffers.
  - Extract `GridRenderer` + `TetriminoRenderer` owning `sand_texture`, `ghost`, and piece textures, reading `const SandSimulation&` via `std::span<const uint8_t>` views.
  - Strip all `Game&`, `sdlgame::key::get_pressed()`, `sdlgame::event::post()`, `sdlgame::random::randint()`, `game.m_clock`, `game.m_window_draw_offset`, and `redraw()` calls out of simulation. Inject `PlayerInput`, `dt`, and `XorShift32& rng` at the scene boundary; return `SimTickEvents`.
  - Remove `GAME_PAUSE` handling from `Grid::handle_event()`; handle pause in `GamePlay` scene and decode SDL events into `PlayerInput` once (removing duplicate `K_w`/`K_UP` checks and stringly-typed `event["key"]` lookups).
  - Delete unimplemented `Grid` 4-arg constructor declaration and add `const [[nodiscard]]` to `get_score()`.
- [ ] **Fix `collision_check()` $O(W \cdot H \cdot 16)$ Scan & Dishonest Side Effects** ([`src/Grid.cpp`](src/Grid.cpp)):
  - Replace the full 14,160-cell × 16-bit `Rect::collidepoint` scan with a pure $O(1)$ `bool collides_at(const SandField&, const ActivePiece&) const noexcept` checking only the 4 precomputed occupied 8×8 blocks.
  - Separate collision detection from depenetration, merging, piece reset, and ghost updates into explicit top-level steps in `SandSimulation::step(...)`.
- [ ] **Fix `step()` Physics Bug & Inlining/RNG Waste** ([`src/Grid.cpp`](src/Grid.cpp)):
  - Inline cellular-automaton stepping directly into the bottom-up SoA row loop using row pointers (`row_curr`, `row_next`).
  - Fix the `(left == 0, mid == 1, right == 0)` bug where `d_row = 1, d_col = 0` swaps directly into the occupied `mid` cell below (pick diagonal left/right via fast injected PRNG/parity bit).
  - Early-exit settled sand (`if (left & mid & right) continue;`) *before* rolling RNG or stepping; stop rolling `sdlgame::random::randint(1, step_range)` up to 14,080 times/tick on immobile cells.
  - Fix accumulator from `if (update_timer >= fixed_delta_time)` to a bounded fixed-timestep `while` loop.
- [ ] **Eliminate Hot-Path Heap Allocations & Empty-Flood Bug in `check_scoring()`** ([`src/Grid.cpp`](src/Grid.cpp)):
  - Guard against `CellKind::Empty` / `CellKind::Wall` entering BFS (fixes flooding empty air/wall borders).
  - Seed BFS only from non-empty cells along `col == 1` (gated by a 4-bit color mask on `col == GRID_WIDTH` to skip BFS entirely on ~99% of ticks).
  - Replace per-tick `std::queue<GridPos>` (`std::deque`), per-component `std::vector<GridPos> tmp`, and per-tick stack `std::bitset` zero-fill with pre-allocated flat member scratch buffers + `uint16_t visited_epoch[]` generation counter ($O(1)$ clear).
  - Clear cells by writing `CellKind::Empty` instead of calling out-of-line `Sand()` + RNG; accept `std::span<const T>` where spans are passed.
- [ ] **Eliminate Redundant Inner Loops & OOB Reads in `normalize_tetrimino()`, `merge()`, `update_ghost()`** ([`src/Grid.cpp`](src/Grid.cpp)):
  - `normalize_tetrimino`: Replace 16-bit + 2x `Rect::colliderect` loops with a single branchless `std::clamp` using precomputed `min_col`/`max_col`.
  - `merge`: Clamp `[y0, y1)` and `[x0, x1)` once per block outside the inner 8×8 loop, then fill contiguous slices (`std::fill_n`).
  - `update_ghost`: Fix OOB negative-row and unchecked-column reads; recompute only when piece or grid changes instead of column-major cache thrashing every render frame (replace magic `144` with `GRID_HEIGHT`).
- [ ] **Optimize & Harden `Grid::draw()` Inside `GridRenderer`** ([`src/Grid.cpp`](src/Grid.cpp)):
  - Wrap `sand_texture.lock()` / `unlock()` in a RAII `TextureLockGuard`.
  - Replace 14,080 per-frame `SandShiftColor.at(...)` calls, `Color::operator+` temporaries, overlapping bit-shift channel bug (`>>4`/`>>2`/`&15`), and signed `(255 << 24)` with a flat L1-resident `uint32_t kPixelLUT[6][256]` lookup (`pixels[x] = kPixelLUT[kind[x]][noise[x]]`).

---

## Phase C: Resource Ownership, Persistence Boundary & God-Object Teardown
*Eliminates raw `new[]` leaks, two-phase init, double startup disk loads, uninitialized UB, and `Game` god-object exposure.*

- [ ] **Rewrite Persistence as an Injected `SaveStore`** ([`include/SaveData.hpp`](include/SaveData.hpp), [`src/SaveData.cpp`](src/SaveData.cpp)):
  - Delete raw `new char[4]` / `new char[8]` leakers (`int_to_bytes`, `double_to_bytes`) and unchecked `const char*` helpers; use fixed-extent `std::span<const std::byte, sizeof(T)>` + `std::bit_cast` (or the linked `protobuf` dependency).
  - Fix `load_grid_data`: remove unused `Game&`, remove `grid.controller.redraw()` rendering side effect, replace 28,160 1-byte `file.read()` calls with a single contiguous buffer read, validate file length/EOF/enum ranges in a pure `std::expected<GridSnapshot, ParseError> parse_grid_save(std::span<const std::byte>)`.
  - Fix volume persistence: make `load_volume` strictly read-only (stop writing files inside getters), validate via `NormalizedVolume` (rejecting `NaN`), replace dead `try/catch` blocks with stream failbit checks + `std::expected`, ensure save directory creation, and eliminate stubs (`get_personal_best`/`set_personal_best`/`save_grid_data`).
  - Fix window persistence: replace unpacked 4-scalar `save_window_info(x, y, w, h)` and nested `pair<pair<int,int>, pair<int,int>>` magic-zero sentinel with `WindowState = std::variant<Fullscreen, WindowRect>`.
- [ ] **Replace Two-Phase `shared_ptr` Asset Bags with Validated Contiguous Tables** ([`include/Images.hpp`](include/Images.hpp), [`src/Images.cpp`](src/Images.cpp), [`include/SFX.hpp`](include/SFX.hpp), [`src/SFX.cpp`](src/SFX.cpp)):
  - `Images`: Replace 41 individual `std::shared_ptr<Surface>` members and 128-line copy-paste loader with `std::array<Surface<SDL_TEXTUREACCESS_STATIC>, kImageCount>` indexed by `enum class ImageId : uint8_t` + `constexpr` path manifest + `static std::expected<Images, LoadError> load(const fs::path& asset_root)` factory (private ctor, returning non-owning `const Surface&` views).
  - `SFX`: Replace 11 public `Sound` fields with `std::array<Sound, kSfxCount>` indexed by `enum class SfxId : uint8_t` + `static std::expected<SFX, LoadError> load(const fs::path& asset_root)` factory.
  - Fix `#include <SDL_render.h>` appearing before include guards in `Images.hpp` and `Game.hpp`.
- [ ] **Purify `AudioManager`** ([`include/AudioManager.hpp`](include/AudioManager.hpp), [`src/AudioManager.cpp`](src/AudioManager.cpp)):
  - Eliminate constructor disk I/O and double-load at startup (`Game` default init + `Sandtris` reassignment); inject `SFX` and initial `NormalizedVolume` values.
  - Make `sfx` private and expose `play(SfxId)`. Replace 35-line `handle_event()` switch and 11-line volume setter repetition with lookup tables / `std::span<Sound>`.
  - Make `sfx_volume()` / `music_volume()` `const noexcept` (read cached memory, never disk); decouple disk writes from per-frame slider drags into explicit `flush_settings()`.
  - Delete empty out-of-line `AudioManager::update()`.
- [ ] **Fix `Animation` UB & Separate Loading from Playback** ([`include/Animation.hpp`](include/Animation.hpp), [`src/Animation.cpp`](src/Animation.cpp)):
  - Fix active UB: initialize `size_t m_frame_id = 0` (currently uninitialized and read via `main.cpp:L120-123`).
  - Remove `Game*` dependency; pass `double dt` explicitly into `update(double dt)`.
  - Split into immutable validated `AnimationClip` (filter regular image files, return `std::expected` instead of release-mode `assert` OOB crashes, store contiguous `std::vector<Surface>` instead of per-frame `shared_ptr`) and pure `AnimationPlayer` using `PositiveFrameRate` (precomputed `frame_duration`, `while` loop instead of `if`, inline trivial `noexcept` getters).
- [ ] **Encapsulate `Game` & Decompose `main.cpp`** ([`include/Game.hpp`](include/Game.hpp), [`src/Game.cpp`](src/Game.cpp), [`src/main.cpp`](src/main.cpp)):
  - Delete shadowed `Sandtris::m_gameactive` and dead `Sandtris::played`.
  - Wrap `sdlgame::init()` / `mixer::init()` / `quit()` in a scoped RAII `EngineRuntime` guard in `main()`; construct `AppPaths`, `SaveStore`, `Images`, `AudioManager`, and `m_window` once and inject into `Game` (eliminate double asset load and `get_window_size()` side-effect hack).
  - Make `Game` members private; move `m_window_draw_offset` to a `Camera2D`/renderer component; replace 4 loose nullable transition pointers (`m_out`, `m_in`, `m_next`, `m_command` — currently silently stranding transitions when `in == nullptr` and risking UB on empty `pop_back`) with a closed `std::variant<Idle, TransitionOut, TransitionIn>` state machine + `NotNullUniquePtr<Scene>`. Fix `current_scene()` return type and inline `out_transitioning()`/`in_transitioning()` as `const noexcept`. Rename `pop_scene` -> `replace_scene`.
  - Decompose 65-line `Sandtris::run()` into focused control-plane methods (`bootstrap_initial_scene`, `poll_and_dispatch_events`, `handle_window_event`, `tick_and_render_frame`). Debounce `save_window_info` (stop rewriting disk on every resize pixel) and throttle FPS `set_caption` updates using stack `std::format_to_n` (stop heap-allocating + WM IPC every frame). Pass explicit `TimerManager` + sink into `print_bench_stat`.

---

## Phase D: UI Widget Collapse & Pure Value Controls
*Deletes 24 boilerplate files, kills per-frame atomic `shared_ptr` refcount churn, and fixes widget UB and side-effect leaks.*

- [ ] **Delete 24 Boilerplate Widget Subclass Files**:
  - Remove all 11 `*Button.{hpp,cpp}` pairs (22 files: `Start`, `Back`, `Credit`, `HTP`, `Menu`, `Option`, `PB`, `Pause`, `Quit`, `Resume`, `Retry` — eliminating 11 vtables, 22 cross-TU forwarding trampolines missing `override`, and public nullable `Game*` drilling).
  - Remove `include/OptionElement.hpp` and `src/OptionElement.cpp` (2 files: 3x byte-for-byte duplicated `draw()`, 5 forwarding trampolines).
  - Move `QuitButton`'s `sdlgame::quit(); exit(0);` (which currently bypasses all C++ destructors!) to a clean `request_quit()` loop exit; move `RetryButton`'s `delete_grid_data()` and `FullscreenSlider`'s `load_window_info()` + `sdlgame::display::*` calls up to scene/app orchestration.
- [ ] **Rewrite `Button` as a Pure, `final` Value Type** ([`include/Button.hpp`](include/Button.hpp), [`src/Button.cpp`](src/Button.cpp)):
  - Remove `sdlgame::sprite::Sprite` inheritance (eliminates 72+ bytes of unused `Group` vectors + `enable_shared_from_this` and lets scenes store buttons by value).
  - Replace 4 `std::shared_ptr<Surface>` fields (eliminating per-frame atomic refcount churn `m_image = m_idle`) with non-owning `std::array<const Surface*, 3>` validated non-null at construction; delete zombie `Button()` and `set_images()`.
  - Replace split `hovering`/`prev_hovered`/`m_image` flags (fixing drag-in click bug and stuck `m_click` visual bug) with `enum class ButtonState : uint8_t { Idle, Hovered, Pressed }`.
  - Inject `Vector2 mouse_pos` into `update`/`handle_event`; return `enum class ButtonAction : uint8_t { None, HoverEntered, Clicked }` (or invoke injected `std::move_only_function<void()>`) instead of calling global `sdlgame::mouse::get_pos()` / `sdlgame::event::post()`.
- [ ] **Rewrite `Slider` as a Pure, `final` Value Type & Extract `ToggleSwitch`** ([`include/Slider.hpp`](include/Slider.hpp), [`src/Slider.cpp`](src/Slider.cpp)):
  - Make `Slider` concrete `final` (fixes missing `virtual ~Slider()` UB) with all fields `private`; move unified `draw(RenderTarget&) const` directly onto `Slider`.
  - Delete zombie `Slider()` (uninitialized floats/bool) and two-phase `"default label"` throwaway texture render + `set_color`/`set_label`; construct once from `SliderSpec` (`PositiveFloat`, `NormalizedFloat`, `SliderPalette`, `std::string_view label`) + injected `const Font&` (removing per-slider `TTF_Font` disk load and member duplication).
  - Inject `Vector2 mouse_pos` into `update`/`handle_event`; derive knob position from `NormalizedFloat` (fixes div-by-zero / `clamp` `hi < lo` UB).
  - Create a dedicated pure `ToggleSwitch` value widget (`bool checked`) replacing `FullscreenSlider` (fixes LSP violation and float-equality toggle hack).

---

## Phase E: Scenes & State Machine Purification
*Removes `Game&` drilling, eliminates 22 unnecessary `shared_ptr` scene members, and fixes 4 active scene state-machine bugs.*

- [ ] **Purify `Scene` Interface** ([`include/Scene.hpp`](include/Scene.hpp), [`src/Scene.cpp`](src/Scene.cpp)):
  - Remove `public: Game &game`; inject narrow read/service interfaces (`const Images&`, `const Font&`, `AudioSink&`, etc.) at construction.
  - Update virtual signatures to `update(Seconds dt) -> SceneAction`, `draw(RenderTarget&) const`, `handle_event(const Event&) -> SceneAction`.
  - Delete `is_working()` polling; add explicit `on_enter()`, `on_pause()`, `on_resume()` lifecycle hooks driven by the scene stack.
- [ ] **Replace `SceneTransition` Hierarchy with `std::variant` & Fix Fade UB** ([`include/SceneTransition.hpp`](include/SceneTransition.hpp), [`src/SceneTransition.cpp`](src/SceneTransition.cpp), [`include/scene_transitions.hpp`](include/scene_transitions.hpp), [`src/scene_transitions.cpp`](src/scene_transitions.cpp)):
  - Collapse 4 heap-allocated virtual classes (`OutSwipeDown`, `InSwipeDown`, `OutFade`, `InFade`, all missing `override`) into `std::variant<SwipeTransition, FadeTransition>` parameterized by `Direction::In | Direction::Out` and `PositiveSeconds` (prevents div-by-zero).
  - Inject `ViewportSize` and `RenderTarget&` instead of querying global `sdlgame::display::get_width/height/surf()`.
  - Fix `OutFade`/`InFade` unclamped `uint8_t(cur_alpha)` overflow/underflow UB, move GPU `fill()` out of `update()`, drop wasteful full-screen `mask` render target, and replace per-frame `Color("black"s)` string lookups with `constexpr Color`.
- [ ] **Fix Critical Bugs & Decompose `GamePlay`** ([`include/GamePlay.hpp`](include/GamePlay.hpp), [`src/GamePlay.cpp`](src/GamePlay.cpp)):
  - Move `m_blipcount == -1` transition out of `draw()` (fixes soft-lock on dropped frames / double-pop + disk I/O inside `draw()`) into `update(dt)` using a time-based `Seconds` timer (not frame-count) and `std::variant<CountdownState, ActiveState, PausedState, GameOverBlinkState, DoneState>`.
  - Stop calling `get_personal_best()`/`set_personal_best()` disk I/O on every `SCORING` event (cache in memory, flush on pause/end), fix double `save_grid_data()` on pause, and stop calling `sdlgame::music::resume()` every frame.
  - Decompose 44-line ctor and 43-line `update()` into single-abstraction helpers; store button/animations by value; delete dead `m_next_color` and broken pass-by-value `load_grid(Grid)` stub; initialize `m_color_flow1/2`; hoist `constexpr Color` out of `redraw_next_shape()`.
- [ ] **Fix Remaining Scene Bugs & Eliminate `shared_ptr`/Disk-I/O Leakage**:
  - [`GameOver`](include/GameOver.hpp) / [`src/GameOver.cpp`](src/GameOver.cpp): Pass `GameOverSummary{final_score, previous_best, is_new_pb}` (fixes unreachable `"NEW PB !"` bug); drop dead `score_font`/`new_score`/`pb` members and disk I/O in ctor; store buttons by value.
  - [`Pause`](include/Pause.hpp) / [`src/Pause.cpp`](src/Pause.cpp): Pre-render `"Progress will be save"` once at ctor instead of re-rasterizing via SDL_ttf on every hover edge; delete dead `std::string message`; inject font; store buttons by value.
  - [`SplashScreen`](include/SplashScreen.hpp) / [`splash_screens`](src/splash_screens.cpp): Guard `handle_event()` against double `on_finish()` clicks; move `soft_wind_blow.play()` out of ctor to `on_enter()`; remove synchronous folder load and unchecked `.back()` UB in `StudioSC::on_finish`; collapse `StudioSC`/`SDLSC` into data-driven `SplashSequenceScene`.
  - [`MainMenu`](include/MainMenu.hpp), [`Option`](include/Option.hpp), [`HowToPlay`](include/HowToPlay.hpp), [`Credit`](include/Credit.hpp), [`PersonalBest`](include/PersonalBest.hpp): Store all widgets by value (eliminate remaining `shared_ptr`s + redundant `can_resume` flag); add missing `override`s in `MainMenu`; inject persistence/font/settings instead of ctor disk I/O (`have_grid_data()`, `get_personal_best()`, `Font(font_path)`); align `Option::draw()` abstraction levels; compute `HowToPlay` scroll bounds from image/viewport dimensions; drop dead `pb_font`/`score` members in `PersonalBest`.

---

## Legacy / Subsequent Performance Phases (Execute After Phases A–E)

### Phase 1: Memory Lifecycle Determinism & RAII
These tasks establish a predictable memory model and prevent leaks before we optimize allocations.

- [x] **Smart Pointer Migration:** Finalize wrapping the remaining legacy raw pointers (especially those from SDL2) in `std::unique_ptr` with custom SDL deleters to enforce strict RAII.
- [ ] **Arena Allocator Core:** Implement the custom `std::pmr` Arena Allocator to manage game state memory contiguously.
- [ ] **Operator Overloading:** Overload `operator new` and `operator delete` to completely bypass the OS heap scheduler on the critical path, utilizing the arena allocator.

### Phase 2: Data-Oriented Design & Cache-line Optimization
These tasks focus on CPU cache efficiency (L1/L2 hits) for single-threaded performance improvements.

- [ ] **Struct of Arrays (SoA):** Refactor entity and component memory layouts (such as sand particles and grid cells) to enforce contiguous linear scans, replacing Arrays of Structs (AoS).
- [ ] **False Sharing Mitigation:** Utilize `alignas(64)` to force atomic counters and frequently updated independent variables onto discrete CPU cache lines.

### Phase 3: Concurrency & Event Sourcing
These tasks parallelize the architecture and establish lock-free communication between threads.

- [ ] **SPSC Ring Buffer:** Implement a single-producer, single-consumer lock-free ring buffer utilizing `std::atomic<size_t>` for event sourcing and state updates.
- [ ] **Memory Ordering:** Enforce correct C++ atomic memory semantics: use `std::memory_order_release` when updating the write index and `std::memory_order_acquire` when reading from the ring buffer.
- [ ] **Game Loop Refactoring:** Architect the simulation as a deterministic fold over the lock-free ring buffer of immutable structs, decoupling the physics simulation from the rendering loop.

## Notes
- As per project rules, any refactoring action must be done in a separate branch and verified before merging.
- Ensure that the refactored features are self-tested.
- Preserve legacy comments that are not strictly your own unless deemed necessary.
