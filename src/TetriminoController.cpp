#include "TetriminoController.hpp"

TetriminoController::TetriminoController(Game &game, Tetrimino tetrimino) {
  game = &game;
  tetrimino = tetrimino;
  draw_surf = Surface(EDGE_SIZE, EDGE_SIZE);
  topleft = spawn_pos;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      sdlgame::draw::rect(
          draw_surf,
          (tetrimino.mask >> (15 - i * 4 - j) & 1
               ? SandShiftColor[static_cast<uint8_t>(tetrimino.color)]
               : Color()),
          Rect(8 * j, 8 * i, 8, 8));
}
TetriminoController::TetriminoController() {
  game = nullptr;
  tetrimino = Tetrimino('I', SandShift::RED_SAND);
}
void TetriminoController::reset(Tetrimino tetrimino) {
  tetrimino = tetrimino;
  topleft = spawn_pos;
  redraw();
}
void TetriminoController::draw() { game->window.blit(draw_surf, topleft); }
void TetriminoController::update() {
  // movement
  //  redraw();
  auto keys = sdlgame::key::get_pressed();
  topleft.x += ((keys[sdlgame::K_d] or keys[sdlgame::K_RIGHT]) -
                (keys[sdlgame::K_a] or keys[sdlgame::K_LEFT])) *
               sideway_move_speed * game->clock.delta_time().count();
  topleft.y += game->clock.delta_time().count() *
               (keys[sdlgame::K_s] or keys[sdlgame::K_DOWN] ? fast_fall_speed
                                                            : fall_speed);
}
void TetriminoController::rotate() {
  tetrimino.rotate();
  redraw();
}
void TetriminoController::redraw() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      sdlgame::draw::rect(
          draw_surf,
          (tetrimino.mask >> (15 - i * 4 - j) & 1
               ? SandShiftColor[static_cast<uint8_t>(tetrimino.color)]
               : Color()),
          Rect(8 * j, 8 * i, 8, 8));
}
void TetriminoController::handle_event(Event &event) {
  if (event.type == sdlgame::KEYDOWN) {
    if (event["key"] == sdlgame::K_UP or event["key"] == sdlgame::K_w)
      rotate();
  }
}