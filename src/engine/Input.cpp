#include "engine/Input.h"

InputData Input = { false, false, false, false };

void HandleKeyPress(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP: Input.up = true; break;
        case SDLK_LEFT: Input.left = true; break;
        case SDLK_RIGHT: Input.right = true; break;
        case SDLK_DOWN: Input.down = true; break;
        case SDLK_SPACE: Input.action = true; break;
    }
}

void HandleKeyRelease(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP: Input.up = false; break;
        case SDLK_LEFT: Input.left = false; break;
        case SDLK_RIGHT: Input.right = false; break;
        case SDLK_DOWN: Input.down = false; break;
        case SDLK_SPACE: Input.action = false; break;
    }
}

MouseData Mouse = { false, false, 0, 0 };

void HandleMousePress(Uint8 button) {
    if(button == SDL_BUTTON_LEFT) Mouse.left = true;
    if(button == SDL_BUTTON_RIGHT) Mouse.right = true;
}
void HandleMouseRelease(Uint8 button) {
    if(button == SDL_BUTTON_LEFT) Mouse.left = false;
    if(button == SDL_BUTTON_RIGHT) Mouse.right = false;
}