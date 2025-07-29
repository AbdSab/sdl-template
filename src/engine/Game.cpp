#include "engine/Game.h"
#include <SDL2/SDL_events.h>
#include "engine/input.h"
#include "engine/renderer.h"
#include "BaseScene.h"

const double TARGET_FPS = 60.0;
const double TARGET_FRAME_TIME = 1.0 / TARGET_FPS;

void GameStart() {
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
}