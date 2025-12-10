#include "TetriminoController.hpp"

TetriminoController::TetriminoController(Game &game, Tetrimino tetrimino)
{
    this->game = &game;
    this->tetrimino = tetrimino;
    draw_surf = Surface(EDGE_SIZE,EDGE_SIZE);
    topleft = spawn_pos;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            sdlgame::draw::rect(
                draw_surf,
                (this->tetrimino.mask>>(15-i*4-j)&1 ? SandShiftColor[this->tetrimino.color] : Color()),
                Rect(8*j,8*i,8,8)
            );
}
TetriminoController::TetriminoController(){game=nullptr; tetrimino = Tetrimino('I',RED_SAND);}
void TetriminoController::reset(Tetrimino tetrimino)
{
    this->tetrimino = tetrimino;
    topleft = spawn_pos;
    this->redraw();
}
void TetriminoController::draw()
{
    this->game->window.blit(this->draw_surf,this->topleft);
}
void TetriminoController::update()
{
    //movement
    this->redraw();
    auto keys = sdlgame::key::get_pressed();
    this->topleft.x +=
        (
            (keys[sdlgame::K_d] or keys[sdlgame::K_RIGHT])
            -(keys[sdlgame::K_a] or keys[sdlgame::K_LEFT])
        ) * sideway_move_speed * this->game->clock.delta_time();
    this->topleft.y += this->game->clock.delta_time() * (keys[sdlgame::K_s] or keys[sdlgame::K_DOWN] ? fast_fall_speed : fall_speed);
}
void TetriminoController::rotate()
{
    this->tetrimino.rotate();
    this->redraw();
}
void TetriminoController::redraw()
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            sdlgame::draw::rect(
                draw_surf,
                (this->tetrimino.mask>>(15-i*4-j)&1 ? SandShiftColor[this->tetrimino.color] : Color()),
                Rect(8*j,8*i,8,8)
            );
}
void TetriminoController::handle_event(Event &event)
{
    if(event.type == sdlgame::KEYDOWN)
    {
        if(event["key"] == sdlgame::K_UP or event["key"] == sdlgame::K_w) this->rotate();
    }
}