#include "transform.hpp"
#include "display.hpp"
sdlgame::surface::Surface sdlgame::transform::flip(sdlgame::surface::Surface surface, bool flip_x, bool flip_y)
{
    sdlgame::surface::Surface res = surface;
    if (SDL_SetRenderTarget(sdlgame::display::renderer, res.texture))
    {
        printf("Failed to set target: %s\n", SDL_GetError());
    }
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    if (flip_x)
        flipType = (SDL_RendererFlip)(flipType | SDL_FLIP_HORIZONTAL);
    if (flip_y)
        flipType = (SDL_RendererFlip)(flipType | SDL_FLIP_VERTICAL);
    if (SDL_RenderCopyEx(sdlgame::display::renderer, surface.texture, NULL, NULL, 0, NULL, flipType))
        printf("Failed to flip\n");
    if (SDL_SetRenderTarget(sdlgame::display::renderer, NULL))
    {
        printf("Failed to set target: %s\n", SDL_GetError());
    }
    return res;
}
sdlgame::surface::Surface sdlgame::transform::scale(sdlgame::surface::Surface surface, sdlgame::math::Vector2 size)
{
    sdlgame::surface::Surface res = sdlgame::surface::Surface(size.x, size.y);
    if (SDL_SetRenderTarget(sdlgame::display::renderer, res.texture))
    {
        printf("Failed to set target: %s\n", SDL_GetError());
    }
    SDL_RenderCopyF(sdlgame::display::renderer, surface.texture, NULL, NULL);
    if (SDL_SetRenderTarget(sdlgame::display::renderer, NULL))
    {
        printf("Failed to set target: %s\n", SDL_GetError());
    }
    return res;
}

sdlgame::surface::Surface sdlgame::transform::scale_by(sdlgame::surface::Surface surface, double factor)
{
    return sdlgame::transform::scale(surface, surface.get_size() * factor);
}

/**
 * return a surface that rotated a certain angle counter-clokcwise with passed center
 * angle unit is degrees
 * TODO: calculate the new size for the res surface
 */
sdlgame::surface::Surface sdlgame::transform::rotate(sdlgame::surface::Surface surface, double angle_deg, sdlgame::math::Vector2 center)
{
    sdlgame::math::Vector2 newtopleft = (surface.getRect().getTopLeft() - center).rotate(angle_deg);
    sdlgame::math::Vector2 newbotleft = (surface.getRect().getBottomLeft() - center).rotate(angle_deg);
    sdlgame::math::Vector2 newtopright = (surface.getRect().getTopRight() - center).rotate(angle_deg);
    sdlgame::math::Vector2 newbotright = (surface.getRect().getBottomRight() - center).rotate(angle_deg);

    sdlgame::surface::Surface res = sdlgame::surface::Surface(
        std::max({newtopleft.x, newbotleft.x, newbotright.x, newtopright.x}) - std::min({newtopleft.x, newbotleft.x, newbotright.x, newtopright.x}),
        std::max({newtopleft.y, newbotleft.y, newbotright.y, newtopright.y}) - std::min({newtopleft.y, newbotleft.y, newbotright.y, newtopright.y}));
    if (SDL_SetRenderTarget(sdlgame::display::renderer, res.texture))
    {
        printf("Failed to set target: %s\n", SDL_GetError());
    }
    SDL_FPoint tmp = {float(center.x), float(center.y)};
    SDL_RenderCopyExF(sdlgame::display::renderer, surface.texture, NULL, NULL, angle_deg, &tmp, SDL_FLIP_NONE);
    if (SDL_SetRenderTarget(sdlgame::display::renderer, NULL))
    {
        printf("Failed to set target: %s\n", SDL_GetError());
    }
    return res;
}