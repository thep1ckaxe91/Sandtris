#ifndef SDLGAME_CONSTANTS_
#define SDLGAME_CONSTANTS_
#include "SDL2/SDL_events.h"
namespace sdlgame {

const uint32_t FULLSCREEN = SDL_WINDOW_FULLSCREEN;
const uint32_t NO_FRAME = SDL_WINDOW_BORDERLESS;
const uint32_t RESIZABLE = SDL_WINDOW_RESIZABLE;
const uint32_t HIDDEN = SDL_WINDOW_HIDDEN;
const uint32_t SKIP_TASK_BAR = SDL_WINDOW_SKIP_TASKBAR;
const uint32_t POPUP_MENU = SDL_WINDOW_POPUP_MENU;
const uint32_t ALWAYS_ON_TOP = SDL_WINDOW_ALWAYS_ON_TOP;
const uint32_t MAXIMIZED = SDL_WINDOW_MAXIMIZED;
const uint32_t MINIMIZED = SDL_WINDOW_MINIMIZED;

const uint32_t QUIT = SDL_QUIT;
const uint32_t KEYUP = SDL_KEYUP;
const uint32_t KEYDOWN = SDL_KEYDOWN;
const uint32_t MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN;
const uint32_t MOUSEBUTTONUP = SDL_MOUSEBUTTONUP;
const uint32_t MOUSEMOTION = SDL_MOUSEMOTION;
const uint32_t MOUSEWHEEL = SDL_MOUSEWHEEL;
const uint32_t WINDOWEVENT = SDL_WINDOWEVENT;
const uint32_t USEREVENT = SDL_USEREVENT;

const uint32_t WINDOWSHOWN = SDL_WINDOWEVENT_SHOWN;   // Window became shown
const uint32_t WINDOWHIDDEN = SDL_WINDOWEVENT_HIDDEN; // Window became hidden
const uint32_t WINDOWEXPOSED =
    SDL_WINDOWEVENT_EXPOSED; // Window got updated by some external event
const uint32_t WINDOWMOVED = SDL_WINDOWEVENT_MOVED;     // Window got moved
const uint32_t WINDOWRESIZED = SDL_WINDOWEVENT_RESIZED; // Window got resized
const uint32_t WINDOWSIZECHANGED =
    SDL_WINDOWEVENT_SIZE_CHANGED; // Window changed its size
const uint32_t WINDOWMINIMIZED =
    SDL_WINDOWEVENT_MINIMIZED; // Window was minimized
const uint32_t WINDOWMAXIMIZED =
    SDL_WINDOWEVENT_MAXIMIZED; // Window was maximized
const uint32_t WINDOWRESTORED = SDL_WINDOWEVENT_RESTORED; // Window was restored
const uint32_t WINDOWENTER = SDL_WINDOWEVENT_ENTER; // Mouse entered the window
const uint32_t WINDOWLEAVE = SDL_WINDOWEVENT_LEAVE; // Mouse left the window
const uint32_t WINDOWFOCUSGAINED =
    SDL_WINDOWEVENT_FOCUS_GAINED; // Window gained focus
const uint32_t WINDOWFOCUSLOST =
    SDL_WINDOWEVENT_FOCUS_LOST;                     // Window lost focus
const uint32_t WINDOWCLOSE = SDL_WINDOWEVENT_CLOSE; // Window was closed
const uint32_t WINDOWTAKEFOCUS =
    SDL_WINDOWEVENT_TAKE_FOCUS; // Window was offered focus (SDL backend
                                // >= 2.0.5)
const uint32_t WINDOWHITTEST =
    SDL_WINDOWEVENT_HIT_TEST; // Window has a special hit test (SDL backend
                              // >= 2.0.5)

const uint32_t K_a = SDL_SCANCODE_A;
const uint32_t K_b = SDL_SCANCODE_B;
const uint32_t K_c = SDL_SCANCODE_C;
const uint32_t K_d = SDL_SCANCODE_D;
const uint32_t K_e = SDL_SCANCODE_E;
const uint32_t K_f = SDL_SCANCODE_F;
const uint32_t K_g = SDL_SCANCODE_G;
const uint32_t K_h = SDL_SCANCODE_H;
const uint32_t K_i = SDL_SCANCODE_I;
const uint32_t K_j = SDL_SCANCODE_G;
const uint32_t K_k = SDL_SCANCODE_K;
const uint32_t K_l = SDL_SCANCODE_L;
const uint32_t K_m = SDL_SCANCODE_M;
const uint32_t K_n = SDL_SCANCODE_N;
const uint32_t K_o = SDL_SCANCODE_O;
const uint32_t K_p = SDL_SCANCODE_P;
const uint32_t K_q = SDL_SCANCODE_Q;
const uint32_t K_r = SDL_SCANCODE_R;
const uint32_t K_s = SDL_SCANCODE_S;
const uint32_t K_t = SDL_SCANCODE_T;
const uint32_t K_u = SDL_SCANCODE_U;
const uint32_t K_v = SDL_SCANCODE_V;
const uint32_t K_w = SDL_SCANCODE_W;
const uint32_t K_x = SDL_SCANCODE_X;
const uint32_t K_y = SDL_SCANCODE_Y;
const uint32_t K_z = SDL_SCANCODE_Z;

const uint32_t K_0 = SDL_SCANCODE_0;
const uint32_t K_1 = SDL_SCANCODE_1;
const uint32_t K_2 = SDL_SCANCODE_2;
const uint32_t K_3 = SDL_SCANCODE_3;
const uint32_t K_4 = SDL_SCANCODE_4;
const uint32_t K_5 = SDL_SCANCODE_5;
const uint32_t K_6 = SDL_SCANCODE_6;
const uint32_t K_7 = SDL_SCANCODE_7;
const uint32_t K_8 = SDL_SCANCODE_8;
const uint32_t K_9 = SDL_SCANCODE_9;
const uint32_t K_F1 = SDL_SCANCODE_F1;
const uint32_t K_F2 = SDL_SCANCODE_F2;
const uint32_t K_F3 = SDL_SCANCODE_F3;
const uint32_t K_F4 = SDL_SCANCODE_F4;
const uint32_t K_F5 = SDL_SCANCODE_F5;
const uint32_t K_F6 = SDL_SCANCODE_F6;
const uint32_t K_F7 = SDL_SCANCODE_F7;
const uint32_t K_F8 = SDL_SCANCODE_F8;
const uint32_t K_F9 = SDL_SCANCODE_F9;
const uint32_t K_F10 = SDL_SCANCODE_F10;
const uint32_t K_F11 = SDL_SCANCODE_F11;
const uint32_t K_F12 = SDL_SCANCODE_F12;
const uint32_t K_F13 = SDL_SCANCODE_F13;
const uint32_t K_F14 = SDL_SCANCODE_F14;
const uint32_t K_F15 = SDL_SCANCODE_F15;
const uint32_t K_F16 = SDL_SCANCODE_F16;
const uint32_t K_F17 = SDL_SCANCODE_F17;
const uint32_t K_F18 = SDL_SCANCODE_F18;
const uint32_t K_F19 = SDL_SCANCODE_F19;
const uint32_t K_F20 = SDL_SCANCODE_F20;
const uint32_t K_F21 = SDL_SCANCODE_F21;
const uint32_t K_F22 = SDL_SCANCODE_F22;
const uint32_t K_F23 = SDL_SCANCODE_F23;
const uint32_t K_F24 = SDL_SCANCODE_F24;

const uint32_t K_LALT = SDL_SCANCODE_LALT;
const uint32_t K_LCTRL = SDL_SCANCODE_LCTRL;
const uint32_t K_TAB = SDL_SCANCODE_TAB;
const uint32_t K_CAPLOCK = SDL_SCANCODE_CAPSLOCK;
const uint32_t K_ESCAPE = SDL_SCANCODE_ESCAPE;
const uint32_t K_RALT = SDL_SCANCODE_RALT;
const uint32_t K_RCTRL = SDL_SCANCODE_RCTRL;
const uint32_t K_UP = SDL_SCANCODE_UP;
const uint32_t K_DOWN = SDL_SCANCODE_DOWN;
const uint32_t K_LEFT = SDL_SCANCODE_LEFT;
const uint32_t K_RIGHT = SDL_SCANCODE_RIGHT;
const uint32_t K_LSHIFT = SDL_SCANCODE_LSHIFT;
const uint32_t K_RSHIFT = SDL_SCANCODE_RSHIFT;

const uint32_t K_NUM0 = SDL_SCANCODE_KP_0;
const uint32_t K_NUM1 = SDL_SCANCODE_KP_1;
const uint32_t K_NUM2 = SDL_SCANCODE_KP_2;
const uint32_t K_NUM3 = SDL_SCANCODE_KP_3;
const uint32_t K_NUM4 = SDL_SCANCODE_KP_4;
const uint32_t K_NUM5 = SDL_SCANCODE_KP_5;
const uint32_t K_NUM6 = SDL_SCANCODE_KP_6;
const uint32_t K_NUM7 = SDL_SCANCODE_KP_7;
const uint32_t K_NUM8 = SDL_SCANCODE_KP_8;
const uint32_t K_NUM9 = SDL_SCANCODE_KP_9;

const uint32_t K_SLASH = SDL_SCANCODE_SLASH;
const uint32_t K_NUM_ENTER = SDL_SCANCODE_KP_ENTER;
const uint32_t K_SEMICOLON = SDL_SCANCODE_SEMICOLON;
const uint32_t K_COMMA = SDL_SCANCODE_COMMA;
const uint32_t K_DOT = SDL_SCANCODE_DECIMALSEPARATOR;

const uint32_t K_LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET;
const uint32_t K_RIGHTBRACKET = SDL_SCANCODE_RIGHTBRACKET;
const uint32_t K_MINUS = SDL_SCANCODE_MINUS;
const uint32_t K_EQUALS = SDL_SCANCODE_EQUALS;
const uint32_t K_PAGEDOWN = SDL_SCANCODE_PAGEDOWN;
const uint32_t K_PAGEUP = SDL_SCANCODE_PAGEUP;
const uint32_t K_PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN;
const uint32_t K_RETURN = SDL_SCANCODE_RETURN;
const uint32_t K_BACKSPACE = SDL_SCANCODE_BACKSPACE;
const uint32_t K_BACKSLASH = SDL_SCANCODE_BACKSLASH;
const uint32_t K_SPACE = SDL_SCANCODE_SPACE;

const uint32_t WINDOWPOS_CENTERED = SDL_WINDOWPOS_CENTERED;
} // namespace sdlgame

#endif