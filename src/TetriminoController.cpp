#include "TetriminoController.hpp"
#include "Sand.hpp"

TetriminoController::TetriminoController(Game &g, Tetrimino t)
    : game(g), tetrimino(t), draw_surf(TETRIMINO_EDGE_SIZE, TETRIMINO_EDGE_SIZE),
      topleft(spawn_pos) {
  redraw();
}

void TetriminoController::reset(Tetrimino t) {
  tetrimino = t;
  topleft = spawn_pos;
  redraw();
}

void TetriminoController::draw() { game.m_window.blit(draw_surf, topleft); }

void TetriminoController::update() {
  auto keys = sdlgame::key::get_pressed();
  topleft.x += ((keys[sdlgame::K_d] or keys[sdlgame::K_RIGHT]) -
                (keys[sdlgame::K_a] or keys[sdlgame::K_LEFT])) *
               sideway_move_speed * game.m_clock.delta_time().count();
  topleft.y += game.m_clock.delta_time().count() *
               (keys[sdlgame::K_s] or keys[sdlgame::K_DOWN] ? fast_fall_speed
                                                            : fall_speed);
}

void TetriminoController::rotate() {
  tetrimino.rotate();
  redraw();
}

void TetriminoController::redraw() {
  draw_surf.fill(Color());
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (tetrimino.mask >> (15 - i * 4 - j) & 1)
        sdlgame::draw::rect(
            draw_surf, SandShiftColor[static_cast<uint8_t>(tetrimino.color)],
            Rect(8 * j, 8 * i, 8, 8));
}

void TetriminoController::handle_event(const Event &event) {
  if (event.type == sdlgame::KEYDOWN) {
    if (event["key"] == sdlgame::K_UP or event["key"] == sdlgame::K_w)
      rotate();
  }
}
