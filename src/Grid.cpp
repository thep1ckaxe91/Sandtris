#include "Grid.hpp"
#include "engine/engine.hpp"
#include "tetriminoes.hpp"
#include "TetrisEvent.hpp"
#include "crtdbg.h"
#include "flags.hpp"
#ifdef MULTITHREADING
std::mutex grid_mutex;
Sand **grid_mem_address;
void grid_mem_init()
{
    grid_mem_address = (Sand **)calloc(GRID_HEIGHT + 2, sizeof(Sand *));
    for (int i = 0; i < GRID_HEIGHT + 2; i++)
        grid_mem_address[i] = (Sand *)calloc(GRID_WIDTH + 2, sizeof(Sand));
}
#endif
Grid::Grid(Game &game)
{
    this->game = &game;
    controller = TetriminoController(game, Tetriminoes::randomTetrimino());
    update_ghost_shape();
    this->ghost_topleft.y = -1000;
    this->next = Tetriminoes::randomTetrimino();
    this->ghost = Surface(32, 32);
    this->ghost_color = Color("white");
#ifdef MULTITHREADING
    this->grid = grid_mem_address;

    for (int i = 0; i < GRID_HEIGHT + 2; i++)
        grid[i][0] = grid[i][GRID_WIDTH + 1] = Sand(STATIC_SAND);
    for (int i = 0; i < GRID_WIDTH + 2; i++)
        grid[0][i] = grid[GRID_HEIGHT + 1][i] = Sand(STATIC_SAND);
    for (int i = 1; i <= GRID_HEIGHT; i++)
        for (int j = 1; j <= GRID_WIDTH; j++)
            grid[i][j] = Sand();
#else
    for (int i = 0; i < GRID_HEIGHT + 2; i++)
        grid[i][0] = grid[i][GRID_WIDTH + 1] = Sand(STATIC_SAND);
    for (int i = 0; i < GRID_WIDTH + 2; i++)
        grid[0][i] = grid[GRID_HEIGHT + 1][i] = Sand(STATIC_SAND);
    for (int i = 1; i <= GRID_HEIGHT; i++)
        for (int j = 1; j <= GRID_WIDTH; j++)
            grid[i][j] = Sand();
#endif
}
Grid::Grid() = default;
Grid &Grid::operator=(const Grid &other)
{
#ifdef MULTITHREADING
    this->grid = other.grid;

    this->game = other.game;
    for (int i = 0; i < GRID_HEIGHT + 2; i++)
        grid[i][0] = grid[i][GRID_WIDTH + 1] = Sand(STATIC_SAND);
    for (int i = 0; i < GRID_WIDTH + 2; i++)
        grid[0][i] = grid[GRID_HEIGHT + 1][i] = Sand(STATIC_SAND);
    for (int i = 1; i <= GRID_HEIGHT; i++)
        for (int j = 1; j <= GRID_WIDTH; j++)
            grid[i][j] = other.grid[i][j];
    controller = other.controller;
    next = other.next;
#else
    this->ghost = other.ghost;
    this->ghost_color = other.ghost_color;
    this->game = other.game;
    this->score1 = other.score1;
    this->score2 = other.score2;
    update_ghost_shape();
    this->ghost_topleft.y = -1000;
    for (int i = 0; i < GRID_HEIGHT + 2; i++)
        grid[i][0] = grid[i][GRID_WIDTH + 1] = Sand(STATIC_SAND);
    for (int i = 0; i < GRID_WIDTH + 2; i++)
        grid[0][i] = grid[GRID_HEIGHT + 1][i] = Sand(STATIC_SAND);
    for (int i = 1; i <= GRID_HEIGHT; i++)
        for (int j = 1; j <= GRID_WIDTH; j++)
            grid[i][j] = other.grid[i][j];
    controller = other.controller;
    next = other.next;
#endif
    return *this;
}

void Grid::handle_event(Event &event)
{
    controller.handle_event(event);
    if (event.type == sdlgame::KEYDOWN)
    {
        if (event["key"] == sdlgame::K_SPACE)
        {
            sdlgame::event::post(SLAM);
            // move the tetrimino to the lowest point right below and immediatly merge
            controller.topleft = ghost_topleft;
        }
        else if (event["key"] == sdlgame::K_p)
        {
            sdlgame::event::post(GAME_PAUSE);
            // pause scene
        }
        else if (event["key"] == sdlgame::K_w or event["key"] == sdlgame::K_UP)
        {
            update_ghost_shape();
        }
    }
}
void Grid::normalize_tetrimino()
{
    // when rotate, it possible to collide with edge, in that case, we should shift the position of the tetrimino
    for (int shift = 0; shift < 16; shift++)
    {
        if (controller.tetrimino.mask >> shift & 1)
        {
            Rect tmp = Rect(controller.topleft + Vector2((3 - shift % 4) * 8, (3 - shift / 4) * 8), 8, 8);
            for (int i = 0; i < 2; i++)
            {
                if (tmp.colliderect(left_barrier))
                {
                    // printf("collide left\n");
                    tmp.setLeft(left_barrier.getRight());
                    controller.topleft.x = tmp.getLeft() - (3 - shift % 4) * 8;
                }
            }
            for (int i = 0; i < 2; i++)
            {
                if (tmp.colliderect(right_barrier))
                {
                    // printf("collide right\n");
                    tmp.setRight(right_barrier.getLeft());
                    controller.topleft.x = tmp.getLeft() - (3 - shift % 4) * 8;
                }
            }
        }
    }
}
int Grid::get_score() { return score1 + score2; }

/**
 * @brief check if is scoring anything
 *
 * @param updated_sands a list of position sand that got updated
 * @return an integer represent amount of point we get
 */
int Grid::check_scoring(std::vector<pair<Uint8, Uint8>> &updated_sands)
{
    queue<pair<Uint8, Uint8>> q;
    pos.clear();
    bitset<GRID_WIDTH + 2> visited[GRID_HEIGHT + 2];
    for (auto &[i, j] : updated_sands)
    {
        if (visited[i][j] == 1)
            continue;
        visited[i][j] = 1;
        vector<pair<Uint8, Uint8>> tmp;
        SandShift check_color = grid[i][j].mask;
        bool touchleft = 0, touchright = 0;
        q.push({i, j});
        while (!q.empty())
        {
            auto u = q.front();
            tmp.push_back(u);
            q.pop();
            if (u.second == 1)
                touchleft = 1;
            else if (u.second == GRID_WIDTH)
                touchright = 1;
            for (int k = 0; k < (int)(sizeof(dx) / sizeof(int)); k++)
            {
                int x = dx[k] + u.first;
                int y = dy[k] + u.second;
                if (visited[x][y] == 0 and grid[x][y].mask == check_color)
                {
                    q.push({x, y});
                    visited[x][y] = 1;
                }
            }
        }
        if (touchleft and touchright)
        {
            for (auto &v : tmp)
                pos.push_back(v);
        }
    }
    if (pos.size() > 0)
    {
        for (auto &[i, j] : pos)
        {
            grid[i][j] = Sand();
        }
        sdlgame::event::post(SCORING);
    }
    return pos.size();
}

void Grid::merge(vector<pair<Uint8, Uint8>> &updated)
{
    // if merge at wrong place, game over
    // a bit offset for more comfort ux
    this->game->window_draw_offset.y = 2;
    if (controller.topleft.y + 7 < 0)
    {
        sdlgame::event::post(GAMEOVER);
        this->game->window_draw_offset.y = 0;
        return;
    }
    // merge
    for (int shift = 0; shift < 16; shift++)
    {
        if (controller.tetrimino.mask >> shift & 1)
        {
            Vector2 topleft = (controller.topleft + Vector2(3 - shift % 4, 3 - shift / 4) * 8) - Vector2(GRID_X, GRID_Y);
            topleft.x = int(topleft.x);
            topleft.y = int(topleft.y);
            topleft.x += 1;
            topleft.y += 1;
            for (int i = topleft.y; i < topleft.y + 8; i++)
            {
                for (int j = topleft.x; j < topleft.x + 8; j++)
                {
                    if (i <= GRID_HEIGHT)
                    {
                        updated.push_back({i, j});
                        grid[i][j].mask = controller.tetrimino.color;
                    }
                }
            }
        }
    }
}
void Grid::collision_check(vector<pair<Uint8, Uint8>> &updated)
{
    // check collision if the tetrimino is collided with the grid
    /*
     */

    bool called = 0;
    for (int i = 1; i <= GRID_HEIGHT + 1; i++)
    {
        if (!called)
            for (int j = 1; j <= GRID_WIDTH; j++)
            {
                if (!called)
                    if (grid[i][j].mask)
                    {
                        for (int shift = 0; shift < 16; shift++)
                        {
                            if (controller.tetrimino.mask >> shift & 1)
                            {
                                Rect tmp = Rect(controller.topleft + Vector2((3 - shift % 4) * 8, (3 - shift / 4) * 8), 8, 8);
                                if (tmp.collidepoint(j + GRID_X, i + GRID_Y - 1))
                                {
                                    Vector2 check_point(j + GRID_X, i + GRID_Y);
                                    while (tmp.collidepoint(check_point))
                                    {
                                        controller.topleft.y -= 1;
                                        tmp.move_ip(0, -1);
                                        if (grid[int(check_point.y - GRID_Y - 1)][int(check_point.x - GRID_X)].mask)
                                            check_point.y--;
                                    }
                                    called = 1;
                                    this->merge(updated);
                                    this->controller.reset(this->next);
                                    this->next = Tetriminoes::randomTetrimino();
                                    sdlgame::event::post(MERGING);
                                    update_ghost_shape();
                                    break;
                                }
                            }
                        }
                    }
            }
    }
    // exit(0);
}

pair<Uint8, Uint8> Grid::step(int i, int j, int times)
{
    while (times--)
    {
        if (!grid[i + 1][j].mask)
        {
            swap(grid[i][j], grid[i + 1][j]);
            // return step(i+1,j,times-1);
            i++;
        }
        else if (!grid[i + 1][j - 1].mask and !grid[i][j - 1].mask)
        {
            swap(grid[i][j], grid[i + 1][j - 1]);
            // return step(i+1,j-1,times-1);
            j--;
            i++;
        }
        else if (!grid[i + 1][j + 1].mask and !grid[i][j + 1].mask)
        {
            swap(grid[i][j], grid[i + 1][j + 1]);
            // return step(i+1,j+1,times-1);
            j++;
            i++;
        }
    }
    return {i, j};
}
/**
 * @brief everytime rotate or change shape due to merge, we should redraw the ghost
 * acoording to the current tetrimino
 */
void Grid::update_ghost_shape()
{
    auto get_from_pos = [&](const int i, const int j)
    {
        return (3 - i) * 4 + (3 - j);
    };
    ghost.fill("none");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (this->controller.tetrimino.mask >> get_from_pos(i, j) & 1)
            {
                sdlgame::draw::rect(ghost, ghost_color, Rect(j * 8, i * 8, 8, 8), 1);
            }
        }
    }
}
void Grid::update_ghost()
{
    bitset<4> checked;    // if the ith collumn is check or not
    int min_height = 144; // min distance
    // get the min distance from the tetrimino down to display the ghost
    for (int shift = 0; shift < 16; shift++)
    {
        if ((this->controller.tetrimino.mask >> shift & 1) and !checked[shift % 4])
        {
            checked[shift % 4] = 1;
            int left = this->controller.topleft.x + 8 * (3 - shift % 4) - GRID_X;
            int right = this->controller.topleft.x + 8 * (3 - shift % 4) + 8 - GRID_X;
            for (int j = left; j < right; j++)
            {
                int i = this->controller.topleft.y + 8 * (3 - shift / 4) - GRID_Y;
                int cnt = 0;
                while (grid[i++][j + 1].mask == 0)
                {
                    cnt++;
                    if (cnt >= min_height)
                        break;
                }
                min_height = min(min_height, cnt);
            }
        }
    }
    // update the topleft of the ghost
    ghost_topleft = this->controller.topleft + Vector2(0, min_height - 8);
    ghost_topleft.x = int(ghost_topleft.x);
    ghost_topleft.y = int(ghost_topleft.y) - 1;
}
void Grid::update()
{
    this->update_timer += this->game->clock.delta_time();
    if (this->update_timer >= this->fixed_delta_time)
    {
        vector<pair<Uint8, Uint8>> updated_sands;
        this->update_timer -= this->fixed_delta_time;
#ifndef MULTITHREADING
        for (int i = GRID_HEIGHT; i >= 1; i--)
        {
            for (int j = 1; j <= GRID_WIDTH; j++)
            {
                if (grid[i][j].mask)
                {
                    int step_times = sdlgame::random::randint(1, step_range);
                    pair<Uint8, Uint8> pos = this->step(i, j, step_times);
                    if (i != pos.first or j != pos.second)
                        updated_sands.push_back(pos);
                }
            }
        }
#else
        for (int offset_y = 1; offset_y >= 0; offset_y--)
        {
            for (int offset_x = 0; offset_x < 2; offset_x++)
            {
                for (int i = 1; i >= 0; i--)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        int top = i * GRID_HEIGHT / 2 + offset_y * GRID_HEIGHT / 4 + 1;
                        int left = j * GRID_WIDTH / 2 + offset_x * GRID_WIDTH / 4 + 1;
                        int w = GRID_WIDTH / 4;
                        int h = GRID_HEIGHT / 4;
                        this->update_thread[i][j] =
                            thread(update_part, top, left, w, h, std::ref(updated_sands));
                    }
                }
                for (int i = 1; i >= 0; i--)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        this->update_thread[i][j].join();
                    }
                }
            }
        }
#endif
        collision_check(updated_sands);
        if (!updated_sands.empty())
        {
            int added = check_scoring(updated_sands);
            if (added > 0)
            {
                int split = sdlgame::random::randint(2, added - 2);
                score1 += split;
                score2 += added - split;
            }
        }
    }
    if (this->game->window_draw_offset.y != 0)
        this->game->window_draw_offset.y--;
    controller.update();
    normalize_tetrimino();
    update_ghost_shape();
    update_ghost();
}
void Grid::draw_ghost()
{
    // sdlgame::draw::rect(ghost,"red",Rect(0,0,32,32),1);
    this->game->window.blit(ghost, ghost_topleft);
}
void Grid::draw()
{
#ifndef MULTITHREADING
    for (int i = 1; i <= GRID_HEIGHT; i++)
    {
        for (int j = 1; j <= GRID_WIDTH; j++)
        {
            if (grid[i][j].mask)
                sdlgame::draw::point(
                    this->game->window,
                    SandShiftColor.at(grid[i][j].mask).add_value(grid[i][j].color_offset_rgb >> 4 & 15, grid[i][j].color_offset_rgb >> 2 & 15, grid[i][j].color_offset_rgb & 15),
                    j + GRID_X - 1, i + GRID_Y - 1);
        }
    }

    // for (int i = 1; i >= 0; i--)
    // {
    //     for (int j = 0; j < 2; j++)
    //     {
    //         int top = i * GRID_HEIGHT / 2 + 1;
    //         int left = j * GRID_WIDTH / 2 + 1;
    //         int w = GRID_WIDTH / 2;
    //         int h = GRID_HEIGHT / 2;
    //         grid_draw_thread[i][j] =
    //             thread(draw_part, std::ref(this->grid), std::ref(this->game), top, left, w, h);
    //     }
    // }
    // for (int i = 1; i >= 0; i--)
    // {
    //     for (int j = 0; j < 2; j++)
    //     {
    //         grid_draw_thread[i][j].join();
    //     }
    // }

#else
    for (int i = 1; i <= GRID_HEIGHT; i++)
    {
        for (int j = 1; j <= GRID_WIDTH; j++)
        {
            if (grid[i][j].mask)
                sdlgame::draw::point(
                    this->game->window,
                    SandShiftColor.at(grid[i][j].mask).add_value(grid[i][j].color_offset_rgb >> 4 & 15, grid[i][j].color_offset_rgb >> 2 & 15, grid[i][j].color_offset_rgb & 15),
                    j + GRID_X - 1, i + GRID_Y - 1);
        }
    }
#endif
    controller.draw();
    draw_ghost();
}

// std::thread grid_draw_thread[2][2];
// void draw_part(const Sand **grid, Game *game, const int top, const int left, const int w, const int h)
// {
//     for (int i = top; i < top + h; i++)
//     {
//         for (int j = left; j < left + w; j++)
//         {
//             if (grid[i][j].mask)
//                 sdlgame::draw::point(
//                     game->window,
//                     SandShiftColor.at(grid[i][j].mask).add_value(grid[i][j].color_offset_rgb >> 4 & 15, grid[i][j].color_offset_rgb >> 2 & 15, grid[i][j].color_offset_rgb & 15),
//                     j + GRID_X - 1, i + GRID_Y - 1);
//         }
//     }
// }

#ifdef MULTITHREADING
pair<Uint8, Uint8> step(int i, int j, int times)
{
    while (times--)
    {
        if (!grid_mem_address[i + 1][j].mask)
        {
            swap(grid_mem_address[i][j], grid_mem_address[i + 1][j]);
            // return step(i+1,j,times-1);
            i++;
        }
        else if (!grid_mem_address[i + 1][j - 1].mask and !grid_mem_address[i][j - 1].mask)
        {
            swap(grid_mem_address[i][j], grid_mem_address[i][j - 1]);
            // return step(i+1,j-1,times-1);
            j--;
        }
        else if (!grid_mem_address[i + 1][j + 1].mask and !grid_mem_address[i][j + 1].mask)
        {
            swap(grid_mem_address[i][j], grid_mem_address[i][j + 1]);
            // return step(i+1,j+1,times-1);
            j++;
        }
    }
    return {i, j};
}

void update_part(const int top, const int left, const int width, const int height, vector<pair<Uint8, Uint8>> &updated)
{
    for (int i = top + height - 1; i >= top; i--)
    {
        for (int j = left; j < left + width; j++)
        {
            if (game_ended)
                return;
            if (grid_mem_address[i][j].mask)
            {
                int step_times = sdlgame::random::randint(2, 5);
                pair<Uint8, Uint8> pos = step(i, j, step_times);
                if (i != pos.first or j != pos.second)
                {
                    std::lock_guard<std::mutex> lock(grid_mutex);
                    updated.push_back(pos);
                }
            }
        }
    }
}

#endif