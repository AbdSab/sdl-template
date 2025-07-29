#include "engine/common.h"

//Input
InputData Input = { false, false, false, false };

void HandleKeyPress(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP: Input.up = true; break;
        case SDLK_LEFT: Input.left = true; break;
        case SDLK_RIGHT: Input.right = true; break;
        case SDLK_DOWN: Input.down = true; break;
        case SDLK_SPACE: Input.action = true; break;
    }
}

void HandleKeyRelease(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP: Input.up = false; break;
        case SDLK_LEFT: Input.left = false; break;
        case SDLK_RIGHT: Input.right = false; break;
        case SDLK_DOWN: Input.down = false; break;
        case SDLK_SPACE: Input.action = false; break;
    }
}

void DrawText(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color* color, TTF_Font* font) {
    SDL_Color drawColor = color ? *color : SDL_Color{255, 255, 255, 255};
    
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, drawColor);
    if (!surface) {
        SDL_Log("TTF_RenderText_Blended failed: %s", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        return;
    }

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstRect = { x, y, texW, texH };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);
}