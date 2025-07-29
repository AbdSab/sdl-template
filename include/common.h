#pragma once
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>

void RenderText(const char* text, int x, int y, SDL_Color* _color, TTF_Font* _font);