#include "GamePlay.hpp"
#include "Game.hpp"
#include "constant.hpp"
#include "TetrisEvent.hpp"
#include "scene_transitions.hpp"
#include "GameOver.hpp"
#include "SaveData.hpp"
GamePlay::GamePlay(Game &game) : Scene(game)
{
    this->game = &game;
    grid = Grid(game);

    this->score_font = Font(base_path + "data\\fonts\\sandtris pixel.ttf", FONT_SIZE);
    this->score_surf = score_font.render("0", 0, "white");
    this->score_rect = score_surf.getRect();
    score_rect.setCenter(score_display_center);

    next_display_color = this->grid.next.color;
    flow1 = next_color_display_rect.inflate(0, 5);
    flow2 = flow1.move(0, next_color_display_rect.getHeight());
    color_flow1 = "none";
    color_flow2 = "none";

    next_shape_surf = Surface(next_shape_display_rect.getWidth(), next_shape_display_rect.getHeight());
    redraw_next_shape();
    change_shape = Animation(game, 120);
    change_shape.load(base_path + "data/animations/change_next_shape/");
    Surface tmp = Surface(next_shape_display_area.getWidth(), next_shape_display_area.getHeight());
    tmp.fill("none");
    change_shape.set_default(tmp);

    count_down = Animation(game, 1);
    count_down.load(base_path + "data/animations/count_down/");
    tmp = Surface(count_down_display_rect.getWidth(), count_down_display_rect.getHeight());
    tmp.fill("none");
    count_down.set_default(tmp);
    count_down.play();

    sdlgame::music::load(base_path + "data/audio/music/tetris_theme_loop_instrument.mp3");
    sdlgame::music::play(-1, 2000);

    pause_button = PauseButton(game);
    pause_button.rect.setTopRight(RESOLUTION_WIDTH, 0);

    this->gameover = 0;
    this->blipcount = 100;
    pausing = 0;
}
void GamePlay::load_grid(Grid grid)
{
    this->grid = grid;
}
void GamePlay::redraw_next_shape()
{
    next_shape_surf.fill(Color());
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (this->grid.next.mask >> (15 - i * 4 - j) & 1)
                sdlgame::draw::rect(
                    this->next_shape_surf,
                    Color("white"),
                    Rect(
                        Vector2(6 * j, 6 * i) +
                            (this->grid.next.type != 'I' and this->grid.next.type != 'O' ? Vector2(4, 1) : Vector2()),
                        6, 6));
}
void GamePlay::handle_event(sdlgame::event::Event &event)
{
    if (!this->count_down.playing)
    {
        this->grid.handle_event(event);
        this->pause_button.handle_event(event);
    }
    if (event.type == SCORING)
    {
        this->score_surf = score_font.render(to_string(this->grid.get_score()), 0, "white");
        this->score_rect = score_surf.getRect();
        score_rect.setCenter(score_display_center);
        if(get_personal_best() < this->grid.get_score() ) set_personal_best(this->grid.get_score());
    }
    else if (event.type == MERGING)
    {
        next_display_color = this->grid.next.color;
        redraw_next_shape();
        this->change_shape.play();
    }
    else if (event.type == GAMEOVER)
    {
        sdlgame::music::stop();
        delete_grid_data();
        gameover = 1;
    }
    else if (event.type == BUTTON_CLICK)
    {
        sdlgame::music::pause();
        pausing = 1;
        save_grid_data(this->grid);
    }
    else if (event.type == sdlgame::KEYDOWN)
    {
        if ((event["key"] == sdlgame::K_p or event["key"] == sdlgame::K_ESCAPE)
        and !this->game->in_transitioning() and !this->game->out_transitioning() and !this->gameover)
        {
            pause_button.on_click();
            sdlgame::music::pause();
            pausing = 1;
            save_grid_data(this->grid);
        }
    }
}
void GamePlay::update()
{
    if (this->pausing and this->is_working() and !(this->game->out_transitioning() or this->game->in_transitioning()))
    {
        pausing = 0;
        count_down.reset();
        count_down.play();
    }
    if (!gameover)
    {
        if (!count_down.playing and !pausing)
        {
            sdlgame::music::resume();
            this->grid.update();
            double delta_y = -flow_speed * this->game->clock.delta_time();
            flow1.move_ip(0, delta_y);
            flow2.move_ip(0, delta_y);
            if (flow1.getBottom() - 1 <= next_color_display_rect.getTop())
            {
                flow1.setTop(flow2.getBottom());
                color_flow1 = SandShiftColor.at(next_display_color);
            }
            if (flow2.getBottom() - 1 <= next_color_display_rect.getTop())
            {
                flow2.setTop(flow1.getBottom());
                color_flow2 = SandShiftColor.at(next_display_color);
            }
            change_shape.update();
        }
        else
        {
            if (count_down.frame_change)
            {
                if (count_down.frame_id != 4)
                    sdlgame::event::post(COUNT_DOWN);
                else
                    sdlgame::event::post(COUNT_DOWN_START);
            }
            count_down.update();
        }
        this->bg_offset.x -= gameplay_bg_speed * this->game->clock.delta_time();
        this->bg_offset.y -= gameplay_bg_speed * this->game->clock.delta_time();
        if (this->bg_offset.x <= -8)
            this->bg_offset = Vector2();
        this->pause_button.update();
    }
    else
    {
        blipcount--;
    }
}
void GamePlay::draw()
{
    this->game->window.blit(this->game->images.gameplay_background, bg_offset);

    sdlgame::draw::rect(
        this->game->window, color_flow1,
        flow1.overlap(next_color_display_rect));
    sdlgame::draw::rect(
        this->game->window, color_flow2,
        flow2.overlap(next_color_display_rect));

    this->game->window.blit(this->game->images.game_frame, Vector2());

    this->game->window.blit(this->next_shape_surf, next_shape_display_rect.getTopLeft());

    this->game->window.blit(this->change_shape.image, next_shape_display_area.getTopLeft());
    if (!(blipcount / 10 & 1) and blipcount >= 0)
        this->grid.draw();

    if (count_down.playing)
        this->game->window.blit(this->count_down.image, count_down_display_rect.getTopLeft());

    if (blipcount == -1)
    {
        InSwipeDown *in = new InSwipeDown();
        OutSwipeDown *out = new OutSwipeDown();
        GameOver *next = new GameOver(*game, this->grid.get_score());
        this->game->pop_scene(out, next, in);
    }

    this->game->window.blit(this->pause_button.image, pause_button.rect.getTopLeft());
    this->game->window.blit(this->score_surf, this->score_rect.getTopLeft());
}

GamePlay::~GamePlay()
{
    // sdlgame::music::stop();
}