#pragma once

#ifndef SDLGAME_CONSTANTS_
#define SDLGAME_CONSTANTS_
#include "SDL2/SDL.h"
namespace sdlgame
{

    const Uint32 FULLSCREEN = SDL_WINDOW_FULLSCREEN;
    const Uint32 NO_FRAME = SDL_WINDOW_BORDERLESS;
    const Uint32 RESIZABLE = SDL_WINDOW_RESIZABLE;
    const Uint32 HIDDEN = SDL_WINDOW_HIDDEN;
    const Uint32 SKIP_TASK_BAR = SDL_WINDOW_SKIP_TASKBAR;
    const Uint32 POPUP_MENU = SDL_WINDOW_POPUP_MENU;
    const Uint32 ALWAYS_ON_TOP = SDL_WINDOW_ALWAYS_ON_TOP;
    const Uint32 MAXIMIZED = SDL_WINDOW_MAXIMIZED;
    const Uint32 MINIMIZED = SDL_WINDOW_MINIMIZED;

    const Uint32 QUIT = SDL_QUIT;
    const Uint32 KEYUP = SDL_KEYUP;
    const Uint32 KEYDOWN = SDL_KEYDOWN;
    const Uint32 MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN;
    const Uint32 MOUSEBUTTONUP = SDL_MOUSEBUTTONUP;
    const Uint32 MOUSEMOTION = SDL_MOUSEMOTION;
    const Uint32 MOUSEWHEEL = SDL_MOUSEWHEEL;
    const Uint32 WINDOWEVENT = SDL_WINDOWEVENT;
    const Uint32 USEREVENT = SDL_USEREVENT;

    const Uint32 WINDOWSHOWN = SDL_WINDOWEVENT_SHOWN;              // Window became shown
    const Uint32 WINDOWHIDDEN = SDL_WINDOWEVENT_HIDDEN;            // Window became hidden
    const Uint32 WINDOWEXPOSED = SDL_WINDOWEVENT_EXPOSED;          // Window got updated by some external event
    const Uint32 WINDOWMOVED = SDL_WINDOWEVENT_MOVED;              // Window got moved
    const Uint32 WINDOWRESIZED = SDL_WINDOWEVENT_RESIZED;          // Window got resized
    const Uint32 WINDOWSIZECHANGED = SDL_WINDOWEVENT_SIZE_CHANGED; // Window changed its size
    const Uint32 WINDOWMINIMIZED = SDL_WINDOWEVENT_MINIMIZED;      // Window was minimized
    const Uint32 WINDOWMAXIMIZED = SDL_WINDOWEVENT_MAXIMIZED;      // Window was maximized
    const Uint32 WINDOWRESTORED = SDL_WINDOWEVENT_RESTORED;        // Window was restored
    const Uint32 WINDOWENTER = SDL_WINDOWEVENT_ENTER;              // Mouse entered the window
    const Uint32 WINDOWLEAVE = SDL_WINDOWEVENT_LEAVE;              // Mouse left the window
    const Uint32 WINDOWFOCUSGAINED = SDL_WINDOWEVENT_FOCUS_GAINED; // Window gained focus
    const Uint32 WINDOWFOCUSLOST = SDL_WINDOWEVENT_FOCUS_LOST;     // Window lost focus
    const Uint32 WINDOWCLOSE = SDL_WINDOWEVENT_CLOSE;              // Window was closed
    const Uint32 WINDOWTAKEFOCUS = SDL_WINDOWEVENT_TAKE_FOCUS;     // Window was offered focus (SDL backend >= 2.0.5)
    const Uint32 WINDOWHITTEST = SDL_WINDOWEVENT_HIT_TEST;         // Window has a special hit test (SDL backend >= 2.0.5)

    const Uint32 K_a = SDL_SCANCODE_A;
    const Uint32 K_b = SDL_SCANCODE_B;
    const Uint32 K_c = SDL_SCANCODE_C;
    const Uint32 K_d = SDL_SCANCODE_D;
    const Uint32 K_e = SDL_SCANCODE_E;
    const Uint32 K_f = SDL_SCANCODE_F;
    const Uint32 K_g = SDL_SCANCODE_G;
    const Uint32 K_h = SDL_SCANCODE_H;
    const Uint32 K_i = SDL_SCANCODE_I;
    const Uint32 K_j = SDL_SCANCODE_G;
    const Uint32 K_k = SDL_SCANCODE_K;
    const Uint32 K_l = SDL_SCANCODE_L;
    const Uint32 K_m = SDL_SCANCODE_M;
    const Uint32 K_n = SDL_SCANCODE_N;
    const Uint32 K_o = SDL_SCANCODE_O;
    const Uint32 K_p = SDL_SCANCODE_P;
    const Uint32 K_q = SDL_SCANCODE_Q;
    const Uint32 K_r = SDL_SCANCODE_R;
    const Uint32 K_s = SDL_SCANCODE_S;
    const Uint32 K_t = SDL_SCANCODE_T;
    const Uint32 K_u = SDL_SCANCODE_U;
    const Uint32 K_v = SDL_SCANCODE_V;
    const Uint32 K_w = SDL_SCANCODE_W;
    const Uint32 K_x = SDL_SCANCODE_X;
    const Uint32 K_y = SDL_SCANCODE_Y;
    const Uint32 K_z = SDL_SCANCODE_Z;

    const Uint32 K_0 = SDL_SCANCODE_0;
    const Uint32 K_1 = SDL_SCANCODE_1;
    const Uint32 K_2 = SDL_SCANCODE_2;
    const Uint32 K_3 = SDL_SCANCODE_3;
    const Uint32 K_4 = SDL_SCANCODE_4;
    const Uint32 K_5 = SDL_SCANCODE_5;
    const Uint32 K_6 = SDL_SCANCODE_6;
    const Uint32 K_7 = SDL_SCANCODE_7;
    const Uint32 K_8 = SDL_SCANCODE_8;
    const Uint32 K_9 = SDL_SCANCODE_9;
    const Uint32 K_F1 = SDL_SCANCODE_F1;
    const Uint32 K_F2 = SDL_SCANCODE_F2;
    const Uint32 K_F3 = SDL_SCANCODE_F3;
    const Uint32 K_F4 = SDL_SCANCODE_F4;
    const Uint32 K_F5 = SDL_SCANCODE_F5;
    const Uint32 K_F6 = SDL_SCANCODE_F6;
    const Uint32 K_F7 = SDL_SCANCODE_F7;
    const Uint32 K_F8 = SDL_SCANCODE_F8;
    const Uint32 K_F9 = SDL_SCANCODE_F9;
    const Uint32 K_F10 = SDL_SCANCODE_F10;
    const Uint32 K_F11 = SDL_SCANCODE_F11;
    const Uint32 K_F12 = SDL_SCANCODE_F12;
    const Uint32 K_F13 = SDL_SCANCODE_F13;
    const Uint32 K_F14 = SDL_SCANCODE_F14;
    const Uint32 K_F15 = SDL_SCANCODE_F15;
    const Uint32 K_F16 = SDL_SCANCODE_F16;
    const Uint32 K_F17 = SDL_SCANCODE_F17;
    const Uint32 K_F18 = SDL_SCANCODE_F18;
    const Uint32 K_F19 = SDL_SCANCODE_F19;
    const Uint32 K_F20 = SDL_SCANCODE_F20;
    const Uint32 K_F21 = SDL_SCANCODE_F21;
    const Uint32 K_F22 = SDL_SCANCODE_F22;
    const Uint32 K_F23 = SDL_SCANCODE_F23;
    const Uint32 K_F24 = SDL_SCANCODE_F24;

    const Uint32 K_LALT = SDL_SCANCODE_LALT;
    const Uint32 K_LCTRL = SDL_SCANCODE_LCTRL;
    const Uint32 K_TAB = SDL_SCANCODE_TAB;
    const Uint32 K_CAPLOCK = SDL_SCANCODE_CAPSLOCK;
    const Uint32 K_ESCAPE = SDL_SCANCODE_ESCAPE;
    const Uint32 K_RALT = SDL_SCANCODE_RALT;
    const Uint32 K_RCTRL = SDL_SCANCODE_RCTRL;
    const Uint32 K_UP = SDL_SCANCODE_UP;
    const Uint32 K_DOWN = SDL_SCANCODE_DOWN;
    const Uint32 K_LEFT = SDL_SCANCODE_LEFT;
    const Uint32 K_RIGHT = SDL_SCANCODE_RIGHT;
    const Uint32 K_LSHIFT = SDL_SCANCODE_LSHIFT;
    const Uint32 K_RSHIFT = SDL_SCANCODE_RSHIFT;

    const Uint32 K_NUM0 = SDL_SCANCODE_KP_0;
    const Uint32 K_NUM1 = SDL_SCANCODE_KP_1;
    const Uint32 K_NUM2 = SDL_SCANCODE_KP_2;
    const Uint32 K_NUM3 = SDL_SCANCODE_KP_3;
    const Uint32 K_NUM4 = SDL_SCANCODE_KP_4;
    const Uint32 K_NUM5 = SDL_SCANCODE_KP_5;
    const Uint32 K_NUM6 = SDL_SCANCODE_KP_6;
    const Uint32 K_NUM7 = SDL_SCANCODE_KP_7;
    const Uint32 K_NUM8 = SDL_SCANCODE_KP_8;
    const Uint32 K_NUM9 = SDL_SCANCODE_KP_9;

    const Uint32 K_SLASH = SDL_SCANCODE_SLASH;
    const Uint32 K_NUM_ENTER = SDL_SCANCODE_KP_ENTER;
    const Uint32 K_SEMICOLON = SDL_SCANCODE_SEMICOLON;
    const Uint32 K_COMMA = SDL_SCANCODE_COMMA;
    const Uint32 K_DOT = SDL_SCANCODE_DECIMALSEPARATOR;

    const Uint32 K_LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET;
    const Uint32 K_RIGHTBRACKET = SDL_SCANCODE_RIGHTBRACKET;
    const Uint32 K_MINUS = SDL_SCANCODE_MINUS;
    const Uint32 K_EQUALS = SDL_SCANCODE_EQUALS;
    const Uint32 K_PAGEDOWN = SDL_SCANCODE_PAGEDOWN;
    const Uint32 K_PAGEUP = SDL_SCANCODE_PAGEUP;
    const Uint32 K_PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN;
    const Uint32 K_RETURN = SDL_SCANCODE_RETURN;
    const Uint32 K_BACKSPACE = SDL_SCANCODE_BACKSPACE;
    const Uint32 K_BACKSLASH = SDL_SCANCODE_BACKSLASH;
    const Uint32 K_SPACE = SDL_SCANCODE_SPACE;


    const Uint32 WINDOWPOS_CENTERED = SDL_WINDOWPOS_CENTERED;
}

#endif