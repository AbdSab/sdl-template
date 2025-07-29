#pragma once
#include <SDL2/SDL_render.h>

void Init(SDL_Renderer* renderer);
void Update(double dt);
void Render(SDL_Renderer* renderer);