#include "engine/Engine.h"
#include <SDL2/SDL.h>
#include "engine/Input.h"
#include "engine/Renderer.h"
#include "BaseScene.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <game.h>

const double TARGET_FRAME_TIME = 1.0 / FPS;

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
        SDL_DestroyWindow(Window);
        TTF_Quit();
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        return NULL;
    }

    return renderer;
}

int InitSDL(const char* title) {
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

    Window = InitWindow(title, GAME_WIDTH, GAME_HEIGHT);
    Renderer = InitRenderer(Window);

    return 0;
}

void ClearSDL() {
    SDL_DestroyRenderer(Renderer);
   SDL_DestroyWindow(Window);
   TTF_Quit();
   Mix_CloseAudio();
   IMG_Quit();
   SDL_Quit();
}

void GameStart() {
    InitSDL(WINDOW_TITLE);
    bool running = true;
    SDL_Event event;

    Init();

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    double accumulator = 0;

    while (running) {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)(NOW - LAST) / SDL_GetPerformanceFrequency();
        accumulator += deltaTime;
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
               HandleKeyPress(event.key.keysym.sym);
            else if (event.type == SDL_KEYUP)
               HandleKeyRelease(event.key.keysym.sym);

            if(event.type == SDL_MOUSEBUTTONDOWN) {
                HandleMousePress(event.button.button);
            } else if(event.type == SDL_MOUSEBUTTONUP) {
                HandleMouseRelease(event.button.button);
            }
        }
        SDL_GetMouseState(&Mouse.x, &Mouse.y);

        while (accumulator >= TARGET_FRAME_TIME) {
            Update(TARGET_FRAME_TIME);
            accumulator -= TARGET_FRAME_TIME;
        }

        SDL_SetRenderDrawColor(Renderer, 100, 149, 237, 255);
        SDL_RenderClear(Renderer);
        Render();
        SDL_RenderPresent(Renderer);

        double frameTime = (double)(SDL_GetPerformanceCounter() - NOW) / SDL_GetPerformanceFrequency();
        if (frameTime < TARGET_FRAME_TIME) {
            SDL_Delay((Uint32)((TARGET_FRAME_TIME - frameTime) * 1000));
        }
    }

    ClearSDL();
}