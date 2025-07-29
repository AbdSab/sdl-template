#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//----Input-------
struct InputData { bool up; bool right; bool left; bool down; bool action; };
extern InputData Input;

void HandleKeyPress(SDL_Keycode key);
void HandleKeyRelease(SDL_Keycode key);

struct MouseData { bool right; bool left; int x; int y; };
extern MouseData Mouse;

void HandleMousePress(Uint8 button);
void HandleMouseRelease(Uint8 button);
