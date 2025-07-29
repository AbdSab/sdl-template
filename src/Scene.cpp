#include "Scene.h"
#include "assets.h"
#include "engine/common.h"

#define T_PLAYER 0

struct Player { float x; float y; SDL_Texture* texture; } player;

void RenderPlayer(SDL_Renderer* renderer) {
    SDL_Rect rect = { player.x, player.y, 32, 32 };
    SDL_RenderCopy(renderer, player.texture, NULL, &rect);
}


void Init(SDL_Renderer* renderer) {
    Fonts_Init("pixel.ttf");
    Textures_Init();
    player = { .x=100, .y=100, .texture = Textures_Load(renderer, T_PLAYER, "player.png") };
}

void Update(double dt) {
    if(Input.right) {
        player.x += dt * 100;
    }

}

void Render(SDL_Renderer* renderer) {
    DrawText(
        renderer,
        "HELLO", 
        0,0,
        NULL,
        Fonts_Get(FONT_DEFAULT)
    );
    RenderPlayer(renderer);
}