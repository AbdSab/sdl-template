#include "engine/Game.h"
#include <SDL2/SDL_events.h>
#include "engine/input.h"
#include "engine/renderer.h"
#include "Scene.h"

void GameStart() {
    bool running = true;
    SDL_Event event;

    Init();

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

            if(event.type == SDL_MOUSEBUTTONDOWN) {
                HandleMousePress(event.button.button);
            } else if(event.type == SDL_MOUSEBUTTONUP) {
                HandleMouseRelease(event.button.button);
            }
        }
        SDL_GetMouseState(&Mouse.x, &Mouse.y);

        SDL_SetRenderDrawColor(Renderer, 100, 149, 237, 255);
        SDL_RenderClear(Renderer);

        Update(deltaTime);
        Render();

        SDL_RenderPresent(Renderer);
    }
}