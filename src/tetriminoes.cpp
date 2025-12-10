#include "tetriminoes.hpp"
#include "engine/engine.hpp"
namespace Tetriminoes
{
    //Return a random color I tetrimino
    Tetrimino I()
    {
        int shift = (1 << sdlgame::random::randint(0,3));
        return Tetrimino('I',SandShift(shift));
    }
    //Return a random color O tetrimino
    Tetrimino O()
    {
        int shift = (1 << sdlgame::random::randint(0,3));
        return Tetrimino('O',SandShift(shift));
    }
    //Return a random color T tetrimino
    Tetrimino T()
    {
        int shift = (1 << sdlgame::random::randint(0,3));
        return Tetrimino('T',SandShift(shift));
    }
    //Return a random color S tetrimino
    Tetrimino S()
    {
        int shift = (1 << sdlgame::random::randint(0,3));
        return Tetrimino('S',SandShift(shift));
    }
    //Return a random color Z tetrimino
    Tetrimino Z()
    {
        int shift = (1 << sdlgame::random::randint(0,3));
        return Tetrimino('Z',SandShift(shift));
    }
    //Return a random color J tetrimino
    Tetrimino J()
    {
        int shift = (1 << sdlgame::random::randint(0,3));
        return Tetrimino('J',SandShift(shift));
    }
    //Return a random color L tetrimino
    Tetrimino L()
    {
        int shift = (1 << sdlgame::random::randint(0,3));
        return Tetrimino('L',SandShift(shift));
    }
    Tetrimino randomTetrimino()
    {
        int r_num = sdlgame::random::randint(1,7);
        switch (r_num)
        {
        case 1:
            return I();
            break;
        case 2:
            return O();
            break;
        case 3:
            return T();
            break;
        case 4:
            return S();
            break;
        case 5:
            return Z();
            break;
        case 6:
            return J();
            break;
        default:
            return L();
            break;
        }
    }
}