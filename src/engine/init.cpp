#include "engine/init.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

int InitSDL(const char* title, int width, int height, SDL_Renderer** renderer, SDL_Window** window) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("SDL Init failed: %s", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_Log("SDL_image Init failed: %s", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("SDL_mixer Init failed: %s", Mix_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("SDL_ttf Init failed: %s", TTF_GetError());
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    *window = InitWindow(title, width, height);
    *renderer = InitRenderer(*window);

    return 0;
}

SDL_Window* InitWindow(const char* title, int width, int height) {
    SDL_Window* window = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
      SDL_Log("Window creation failed: %s", SDL_GetError());
      TTF_Quit();
      Mix_CloseAudio();
      IMG_Quit();
      SDL_Quit();
      return NULL;
    }
    return window;
}

SDL_Renderer* InitRenderer(SDL_Window* window) {
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        return NULL;
    }

    return renderer;
}

void ClearSDL(SDL_Renderer* renderer, SDL_Window* window) {
    SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   TTF_Quit();
   Mix_CloseAudio();
   IMG_Quit();
   SDL_Quit();
}