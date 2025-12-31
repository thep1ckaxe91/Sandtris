#include "font.hpp"
#include "stdio.h"
#include <string>
#include "surface.hpp"
#include "color.hpp"
#include "display.hpp"

std::map<TTF_Font *,int> sdlgame::font::__font_pool;
void sdlgame::font::init()
{
    if (TTF_Init())
    {
        printf("Failed to init font\n%s\n", TTF_GetError());
        exit(0);
    }
    else
    {
        printf("Font successfully initialized\n");
        return;
    }
}
sdlgame::font::Font::Font()
{
    this->font = nullptr;
    height = 0;
}
sdlgame::font::Font::Font(std::string path, int size)
{
    this->height = size;
    this->font = TTF_OpenFont(path.c_str(), size);
    if (!font)
    {
        printf("Cant load font\n%s\n", TTF_GetError());
        exit(0);
    }
    __font_pool[this->font]=1;
}
    /**
     * @return a surface that only contain the text
     * @param antialias = 0 no antialiasing fastest
     *                  = 1 low antialiaing faster
     *                  = 2 high antialiasing slowest
     * the higher, the slower the render will be
     * @param wrap_length in pixel, once the text get over the wrap_length
     * it automatically endline, if it is default = 0,
     * then will only endline when use endline character
     *
     */
sdlgame::surface::Surface sdlgame::font::Font::render(const std::string text, int antialias, sdlgame::color::Color color, uint32_t wrap_length, sdlgame::color::Color background)
{
    SDL_Surface *surface;
    if (!antialias)
    {
        surface = TTF_RenderUTF8_Solid_Wrapped(font, text.c_str(), color.to_SDL_Color(), wrap_length);
    }
    else if (antialias == 1)
    {
        surface = TTF_RenderUTF8_Shaded_Wrapped(font, text.c_str(), color.to_SDL_Color(), sdlgame::color::Color(0, 0, 0, 0).to_SDL_Color(), wrap_length);
    }
    else
    {
        surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color.to_SDL_Color(), wrap_length);
    }
    if (surface == NULL)
    {
        printf("Error render font\n%s\n", TTF_GetError());
        exit(0);
    }
    res = sdlgame::surface::Surface(surface->w,surface->h);
    res.fill(background);
    SDL_Texture *tmp = SDL_CreateTextureFromSurface(sdlgame::display::renderer, surface);
    if(tmp == NULL)
    {
        printf("Error convert surf to texture\n%s\n",SDL_GetError());
        exit(0);
    }
    SDL_SetRenderTarget(sdlgame::display::renderer, res.texture);
    if (SDL_RenderCopy(sdlgame::display::renderer,tmp, NULL, NULL))
    {
        printf("Error create a rendered font\n%s\n", SDL_GetError());
        exit(0);
    }
    SDL_SetRenderTarget(sdlgame::display::renderer, NULL);
    SDL_DestroyTexture(tmp);
    SDL_FreeSurface(surface);
    return res;
}
int sdlgame::font::Font::get_height()const{return height;}
sdlgame::font::Font &sdlgame::font::Font::operator = (const sdlgame::font::Font &other)
{
    this->height = other.get_height();
    this->font = other.font;
    __font_pool[this->font]++;
    return *this;
}
sdlgame::font::Font::~Font()
{
    __font_pool[this->font]--;
    if(__font_pool.at(this->font)<=0)
    {
        __font_pool.erase(this->font);
        TTF_CloseFont(this->font);
    }
    this->font = 0;
}