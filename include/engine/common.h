#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//----Input-------
struct InputData { bool up; bool right; bool left; bool down; bool action; };
extern InputData Input;

void HandleKeyPress(SDL_Keycode key);
void HandleKeyRelease(SDL_Keycode key);


//Text
void DrawText(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color* color, TTF_Font* font);
