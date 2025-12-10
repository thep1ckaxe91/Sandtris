#include "rect.hpp"
#include "display.hpp"
#include "color.hpp"
#include "math.hpp"
#include "stdio.h"
#include "surface.hpp"
sdlgame::surface::Surface::Surface()
{
    texture = NULL;
}

sdlgame::surface::Surface::Surface(int width, int height)
{
    if (!(texture = SDL_CreateTexture(sdlgame::display::renderer, SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE , width, height)))
    {
        printf("Failed to create texture\nErr: %s\n", SDL_GetError());
        exit(0);
    }
    size.x=width; size.y=height;
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(sdlgame::display::renderer, texture);
    SDL_SetRenderDrawColor(sdlgame::display::renderer, 0, 0, 0, 0);
    SDL_RenderClear(sdlgame::display::renderer);
    SDL_SetRenderTarget(sdlgame::display::renderer, NULL);
}

sdlgame::surface::Surface::Surface(const Surface &oth)
{
    int w, h;
    SDL_QueryTexture(oth.texture, NULL, NULL, &w, &h);
    if (!(texture = SDL_CreateTexture(sdlgame::display::renderer, SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE , w, h)))
    {
        printf("Failed to create texture from another Surface object\nErr: %s\n", SDL_GetError());
        exit(0);
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(sdlgame::display::renderer, texture);
    SDL_SetRenderDrawColor(sdlgame::display::renderer, 0, 0, 0, 0);
    SDL_RenderClear(sdlgame::display::renderer);
    SDL_RenderCopy(sdlgame::display::renderer, oth.texture, NULL, NULL);
    SDL_SetRenderTarget(sdlgame::display::renderer, NULL);
    size.x=w; size.y=h;
}

sdlgame::surface::Surface::Surface(SDL_Texture *oth)
{
    int w, h;
    SDL_QueryTexture(oth, NULL, NULL, &w, &h);
    // this->texture = oth;
    if (!(texture = SDL_CreateTexture(sdlgame::display::renderer, SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE , w, h)))
    {
        printf("Failed to create texture from another texture\nErr: %s\n", SDL_GetError());
        exit(0);
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(sdlgame::display::renderer, texture);
    SDL_SetRenderDrawColor(sdlgame::display::renderer, 0, 0, 0, 0);
    SDL_RenderClear(sdlgame::display::renderer);
    SDL_RenderCopy(sdlgame::display::renderer, oth, NULL, NULL);
    SDL_SetRenderTarget(sdlgame::display::renderer, NULL);

    SDL_DestroyTexture(oth);

    size.x=w; size.y=h;
}

sdlgame::surface::Surface::Surface(SDL_Surface *surf)
{
    texture = SDL_CreateTextureFromSurface(sdlgame::display::renderer, surf);
    // printf("tex: %p | surf: %p\n",texture,surf);
    if (texture == NULL)
    {
        printf("Failed to create texture form surface\nErr:%s\n", SDL_GetError());
        exit(0);
    }
    size.x=surf->w; size.y=surf->h;
}

sdlgame::surface::Surface &sdlgame::surface::Surface::operator=(const sdlgame::surface::Surface &other)
{   
    if(!other.texture)
    {
        if(texture) SDL_DestroyTexture(texture);
        this->texture = nullptr;
    }
    else if (this != &other)
    {
        if(texture!=NULL) SDL_DestroyTexture(texture);
        int w, h;
        SDL_QueryTexture(other.texture, NULL, NULL, &w, &h);
        if (!(texture = SDL_CreateTexture(sdlgame::display::renderer, SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE , w, h)))
        {
            printf("Failed to create texture which assigning\nErr: %s\n", SDL_GetError());
            exit(0);
        }
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetRenderTarget(sdlgame::display::renderer, texture);
        SDL_SetRenderDrawColor(sdlgame::display::renderer, 0, 0, 0, 0);
        SDL_RenderClear(sdlgame::display::renderer);
        SDL_RenderCopy(sdlgame::display::renderer, other.texture, NULL, NULL);
        SDL_SetRenderTarget(sdlgame::display::renderer, NULL);
        size = other.size;
    }
    return *this;
}
/**
 * Return a copy of the surface rect
 */
sdlgame::rect::Rect sdlgame::surface::Surface::getRect() const
{
    return sdlgame::rect::Rect(0, 0,size.x, size.y);
}
/**
 * Blit a surface onto this surface with position and size, leave size be -1,-1 will be its original size
 * the surface or image will stretch or shrink acoording to the size
 */
void sdlgame::surface::Surface::blit(Surface &source, sdlgame::math::Vector2 pos, sdlgame::math::Vector2 size, sdlgame::rect::Rect area)
{
    if (area == sdlgame::rect::Rect())
    {
        area = sdlgame::rect::Rect(0, 0, source.getWidth(), source.getHeight());
    }
    sdlgame::rect::Rect destrect = sdlgame::rect::Rect(
        pos.x, pos.y,
        (size.x < 0 ? source.getWidth() : size.x), (size.y < 0 ? source.getHeight() : size.y));
    if (SDL_SetRenderTarget(sdlgame::display::renderer, texture))
    {
        printf("Failed to set target: %s\n", SDL_GetError());
    }
    SDL_Rect srcrect = area.to_SDL_Rect();
    SDL_FRect dstrect = destrect.to_SDL_FRect();
    // printf("src: %p ren: %p \n",source.texture, sdlgame::display::renderer);
    if (SDL_RenderCopyF(sdlgame::display::renderer, source.texture, &srcrect, &dstrect))
    {
        printf("Error copy texture onto another\n%s\n", SDL_GetError());
        exit(0);
    }
    if (SDL_SetRenderTarget(sdlgame::display::renderer, NULL))
    {
        printf("Failed to set target: %s\n", SDL_GetError());
    }
}
void sdlgame::surface::Surface::fill(sdlgame::color::Color color)
{
    if (SDL_SetRenderTarget(sdlgame::display::renderer, texture))
    {
        printf("Failed to set target: %s\n", SDL_GetError());
    }

    if (SDL_SetRenderDrawColor(sdlgame::display::renderer, color.r, color.g, color.b, color.a))
    {
        printf("Failed to set draw color\nErr:%s\n", SDL_GetError());
        exit(0);
    }
    if (SDL_RenderClear(sdlgame::display::renderer))
    {
        printf("Failed to clear the render target\nErr:%s\n", SDL_GetError());
        exit(0);
    }
    if (SDL_SetRenderTarget(sdlgame::display::renderer, NULL))
    {
        printf("Failed to set target: %s\n", SDL_GetError());
    }
}
sdlgame::math::Vector2 sdlgame::surface::Surface::get_size() const
{
    return size;
}
double sdlgame::surface::Surface::getWidth() const
{
    return size.x;
}
double sdlgame::surface::Surface::getHeight() const
{
    return size.y;
}
sdlgame::surface::Surface::~Surface()
{
    if (texture != NULL){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}