#include "common.h"
#include <assets.h>
#include <engine/Renderer.h>

void RenderText(const char* text, int x, int y, SDL_Color* _color, TTF_Font* _font) {
    if (!text) return;

    SDL_Color fallbackColor = {255, 255, 255, 255};
    SDL_Color* color = _color ? _color : &fallbackColor;
    TTF_Font* font = _font ? _font : Fonts_Get(FONT_DEFAULT);
    
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, *color);
    if (!surface) {
        SDL_Log("Text render failed: %s", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, surface);
    if (!texture) {
        SDL_Log("Texture creation failed: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dst = { x, y, surface->w, surface->h };
    SDL_RenderCopy(Renderer, texture, NULL, &dst);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}