#pragma once
#include <SDL2/SDL.h>

int InitSDL(const char* title, int width, int height, SDL_Renderer** renderer, SDL_Window** window);
SDL_Window* InitWindow(const char* title, int width, int height);
SDL_Renderer* InitRenderer(SDL_Window* window);
void ClearSDL(SDL_Renderer* renderer, SDL_Window* window);