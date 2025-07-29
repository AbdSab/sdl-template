#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "engine/renderer.h"
#include "engine/input.h"
#include "engine/init.h"
#include "engine/Game.h"



int main() {

   InitSDL("Game");

   GameStart();

   ClearSDL();

   return 0;
}
