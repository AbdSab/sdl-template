#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "engine/renderer.h"
#include "engine/input.h"
#include "engine/init.h"
#include "engine/Game.h"

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;



int main() {

   InitSDL("Game", WINDOW_WIDTH, WINDOW_HEIGHT);

   GameStart();

   ClearSDL();

   return 0;
}
