#include "engine/Game.h"
#include <SDL2/SDL_events.h>
#include "engine/common.h"
#include "Scene.h"

void GameStart(SDL_Renderer* renderer) {
    bool running = true;
    SDL_Event event;

    Init(renderer);

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    while (running) {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) * 1000) / SDL_GetPerformanceFrequency();
        deltaTime /= 1000.0;
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
               HandleKeyPress(event.key.keysym.sym);
            else if (event.type == SDL_KEYUP)
               HandleKeyRelease(event.key.keysym.sym);
        }

        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
        SDL_RenderClear(renderer);

        Update(deltaTime);
        Render(renderer);

        SDL_RenderPresent(renderer);
    }
}