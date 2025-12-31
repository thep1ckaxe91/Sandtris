/**
 * For security reason, there should be a way to prevent
 * cheater to cheat their pb
 *
 * the config.cfg file will be written in binary mode
 * first 8*4 bytes represent 8 integer is the bytes offset of the data
 * we will compare after merge the first 4 and the last 4,
 * if they are different, it good to say they're trying to cheat
 *
 * But this is good, since author score will be (1<<31)-1
 * Player must figure a way to find this, but randomness will secure
 * my wallet from emptying itself :)
 */

#include "SaveData.hpp"
#include "constant.hpp"
#include <bits/stdc++.h>
int bytes_to_int(const char *c)
{
    union
    {
        int val;
        char cc[4];
    } data;
    memcpy(data.cc, c, 4);
    return data.val;
}
char *int_to_bytes(int x)
{
    union
    {
        int val;
        char c[4];
    } data;
    char *res = new char[4];
    data.val = x;
    memcpy(res, data.c, 4);
    return res;
}
double bytes_to_double(const char *c)
{
    union
    {
        double val;
        char cc[8];
    } data;
    memcpy(data.cc, c, 8);
    return data.val;
}
char *double_to_bytes(double x)
{
    union
    {
        double val;
        char c[8];
    } data;
    char *res = new char[8];
    data.val = x;
    memcpy(res, data.c, 8);
    return res;
}
int get_personal_best()
{
    if (!filesystem::exists(base_path + "data/save/config.sandtris"))
    {
        set_personal_best(0);
        return 0;
    }
    ifstream file(base_path + "data/save/config.sandtris", ios_base::binary);

    int offset[8];
    file.read((char *)offset, sizeof(int) * 8);
    if (file.fail())
    {
        printf("Failed to get personal best offset");
        exit(0);
    }
    char dat[8];
    for (int i = 0; i < 8; i++)
    {
        file.seekg(std::streamoff(sizeof(offset) + offset[i]), ios_base::seekdir(ios_base::beg));
        file.read(dat + i, 1);
    }
    int pb1 = bytes_to_int(dat);
    int pb2 = bytes_to_int(dat + 4);
    if (pb1 != pb2)
    {
        SDL_Quit();
        printf("Oh, you nearly found the answer, it so close, it just that you could never reach it\n");
        system("pause");
        exit(0);
    }

    return pb1;
}
// score must biger than get_personal_best()
void set_personal_best(int score)
{
    ofstream file(base_path + "data/save/config.sandtris", ios_base::binary);
    // offset 0->3 is the first 4 byte of the score value,
    int offset[8];
    map<int, bool> mp;
    for (int i = 0; i < 8; i++)
        do
        {
            offset[i] = sdlgame::random::randint(
                0,
                1 << sdlgame::random::randint(
                    sdlgame::random::randint(15, 17),
                    sdlgame::random::randint(17, 20)));
        } while (mp.find(offset[i]) != mp.end());
    // now the config.cfg should have 8*4 bytes for the offset info, and all of them
    // shall be unique
    file.write((char *)offset, sizeof(offset));
    if (file.fail())
    {
        printf("Failed to write offset\n");
        exit(0);
    }

    char *dat = int_to_bytes(score);
    int data_size = *max_element(offset, offset + 8) + sdlgame::random::randint(20, 30);

    char *data = new char[data_size];
    for (int i = 0; i < data_size; i++)
        data[i] = sdlgame::random::randint(0, 255);

    for (int i = 0; i < 8; i++)
    {
        data[offset[i]] = dat[i % 4];
    }
    file.write(data, data_size);
    if (file.fail())
    {
        printf("Failed to write data\n");
        exit(0);
    }
    file.close();

    delete[] dat;
    delete[] data;
}

float get_sfx_volume()
{
    if (!filesystem::exists(base_path + "data/save/sfx_volume.sandtris"))
    {
        set_sfx_volume(1);
        return 1;
    }
    ifstream file(base_path + "data/save/sfx_volume.sandtris");

    float res;
    try
    {
        file >> res;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return res;
}
float get_music_volume()
{
    if (!filesystem::exists(base_path + "data/save/music_volume.sandtris"))
    {
        set_music_volume(1);
        return 1;
    }
    ifstream file(base_path + "data/save/music_volume.sandtris");

    float res;
    try
    {
        file >> res;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return res;
}
void set_sfx_volume(float value)
{
    ofstream file(base_path + "data/save/sfx_volume.sandtris");
    file << (value < 0 ? 0 : (value > 1 ? 1 : value));
    file.close();
}
void set_music_volume(float value)
{
    ofstream file(base_path + "data/save/music_volume.sandtris");
    file << (value < 0 ? 0 : (value > 1 ? 1 : value));
    file.close();
}

bool have_grid_data()
{
    return filesystem::exists(base_path + "data/save/grid.sandtris");
}
// delete the save file, if not exist or error is thrown, return false
bool delete_grid_data()
{
    try
    {
        return std::filesystem::remove(base_path + "data/save/grid.sandtris");
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
        return false;
    }
}
/**
 * @brief save the grid data
 *
 * overall, this is what we'll save:
 *
 * 16 bytes of controller topleft
 * 1 byte of controller color (sandshift color)
 * 1 byte of tetrimino type (character)
 * 1 byte of tetrimino rotation (0-3)
 * 1 byte of next tetrimino type
 * 1 byte of next tetrimino color (sandshift color)
 * -> controller can be load with shapeinfolist
 * next 4 bytes is interger for the score
 * the rest is
 * GRID_WIDTH * GRID_HEIGHT bytes for the color mask,
 * GRID_WIDTH * GRID_HEIGHT bytes for color offset byte
 *
 * both will lay like every GRIDWIDTH bytes is 1 line, from top to bottom
 *
 *
 *
 * @param grid the grid data to save
 * @return true save grid success
 * @return false save grid failed
 */
bool save_grid_data(Grid &grid)
{
    if (have_grid_data())
        delete_grid_data();
    ofstream file(base_path + "data/save/grid.sandtris", ios_base::binary);
    int data_size = 16 + 5 + 4 + 2 * GRID_WIDTH * GRID_HEIGHT;
    char *data = new char[data_size];
    // prepare data
    char *controller_x = double_to_bytes(grid.controller.topleft.x);
    memcpy(data, controller_x, sizeof(double));
    delete[] controller_x;
    char *controller_y = double_to_bytes(grid.controller.topleft.y);
    memcpy(data + 8, controller_y, sizeof(double));
    delete[] controller_y;

    char controller_color = grid.controller.tetrimino.color;
    memcpy(data + 16, &controller_color, 1);
    char controller_type = grid.controller.tetrimino.type;
    memcpy(data + 17, &controller_type, 1);
    char controller_rotation = grid.controller.tetrimino.current_rotation;
    memcpy(data + 18, &controller_rotation, 1);
    char next_type = grid.next.type;
    memcpy(data + 19, &next_type, 1);
    char next_color = grid.next.color;
    memcpy(data + 20, &next_color, 1);
    char *score = int_to_bytes(grid.get_score());
    memcpy(data + 21, score, 4);
    // cout <<"score saved: "<< grid.get_score() << endl;
    delete[] score;
    // data+25+.. from now
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            memcpy(data + 25 + i * GRID_WIDTH + j, &grid.grid[i + 1][j + 1].mask, 1);
        }
    }
    // char grid_offset[GRID_HEIGHT][GRID_WIDTH];
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            memcpy(data + 25 + GRID_WIDTH * GRID_HEIGHT + i * GRID_WIDTH + j, &grid.grid[i + 1][j + 1].color_offset_rgb, 1);
        }
    }
    file.write(data, data_size);

    // cerr << "Expected Saved:\n"
    //     <<"topleft:\n"
    //     << grid.controller.topleft.x << " " << grid.controller.topleft.y << '\n'
    //     << "color: " << grid.controller.tetrimino.color << '\n'
    //     << "type: " << grid.controller.tetrimino.type << '\n'
    //     << "rotation: "<< uint8_t(grid.controller.tetrimino.current_rotation) <<'\n'
    //     << "next type: "<<
    //     ;

    if (file.bad() or file.fail())
    {
        cerr << "Cant save progess" << endl;
        file.close();   
        return 0;
    }
    file.close();
    return 1;
}
/**
 * @brief load the grid data from file
 * overall, this is what we'll load:
 *
 * 16 bytes of controller topleft
 * 1 byte of controller color (sandshift color)
 * 1 byte of tetrimino type (character)
 * 1 byte of tetrimino rotation (0-3)
 * 1 byte of next tetrimino type
 * 1 byte of next tetrimino color (sandshift color)
 * -> controller can be load with shapeinfolist
 * next 4 bytes is interger for the score
 * the rest is
 * GRID_WIDTH * GRID_HEIGHT bytes for the color mask,
 * GRID_WIDTH * GRID_HEIGHT bytes for color offset byte
 *
 * both will lay like every GRIDWIDTH bytes is 1 line, from top to bottom
 *
 * @return Grid
 */
Grid load_grid_data(Game *game)
{
    Grid grid(*game);

    ifstream file(base_path + "data/save/grid.sandtris", ios_base::binary);

    char tmp[8];
    Uint8 tmp_byte;
    Uint8 tmp_byte2;
    file.read(tmp, 8);
    grid.controller.topleft.x = bytes_to_double(tmp);
    file.read(tmp, 8);
    grid.controller.topleft.y = bytes_to_double(tmp);

    file.read((char *)&tmp_byte, 1); //color
    file.read((char *)&tmp_byte2, 1); // type
    Tetrimino cur_tetrimino((char)tmp_byte2,(SandShift)tmp_byte);

    grid.controller.tetrimino = cur_tetrimino;

    file.read((char *)&tmp_byte, 1);
    grid.controller.tetrimino.current_rotation = tmp_byte;

    grid.controller.redraw();

    file.read((char *)&tmp_byte, 1);  // type
    file.read((char *)&tmp_byte2, 1); // color
    Tetrimino next(char(tmp_byte), (SandShift)tmp_byte2);
    grid.next = next;

    file.read(tmp, 4);
    // cout << "score got: "<<bytes_to_int(tmp)<<endl;
    if (bytes_to_int(tmp) != 0)
    {
        grid.score2 = sdlgame::random::randint(2, bytes_to_int(tmp) - 2);
        grid.score1 = bytes_to_int(tmp) - grid.score2;
    }
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            file.read((char *)&tmp_byte,1);
            grid.grid[i+1][j+1].mask = SandShift(tmp_byte); 
        }
    }
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            file.read((char *)&tmp_byte,1);
            grid.grid[i+1][j+1].color_offset_rgb = tmp_byte; 
        }
    }

    return grid;
}
/**
 * @brief save the current resolution to disk
 * if width or height is 0, it consider fullscreen
 * @param width res_width
 * @param height res_height
 * @return true if saved
 * @return false if error occur
 */
bool save_window_info(int x,int y, int width, int height)
{
    ofstream file(base_path + "data/save/resolution.sandtris");
    try{
        file << x << " " << y << " " << width << " " << height;
    }
    catch(const std::exception &e)
    {
        cerr << "Cant save info" << endl;
        return 0;
    }
    if(file.bad() or file.fail())
    {
        return false;
    }
    file.close();
    return true;
}
/**
 * @brief load last used window x,y,w,h
 * 
 * @return pair<pair<int,int>,pair<int,int>> 
 */
pair<pair<int,int>,pair<int,int>> load_window_info()
{
    pair<pair<int,int>,pair<int,int>> res;

    try{
        ifstream file(base_path + "data/save/resolution.sandtris");
        file >> res.first.first >> res.first.second >> res.second.first >> res.second.second;
        if(res.second.first == 0 or res.second.second == 0) return {{0,0},{0,0}};
    }
    catch(const std::exception &e)
    {
        cerr << "Cant load info\n" << endl;
        return {{0,0},{0,0}};
    }

    return res;

}