#include "Scene.h"
#include "assets.h"
#include "engine/input.h"
#include "engine/renderer.h"
#include <common.h>

#define T_PLAYER 0

struct Player { float x; float y; SDL_Texture* texture; } player;

void RenderPlayer() {
    SDL_Rect rect = { player.x, player.y, 32, 32 };
    SDL_RenderCopy(Renderer, player.texture, NULL, &rect);
}


void Init() {
    Fonts_Init("pixel.ttf");
    Textures_Init();
    player = { .x=100, .y=100, .texture = Textures_Load(T_PLAYER, "player.png") };
}

void Update(double dt) {
    if(Input.right) {
        player.x += dt * 100;
    }

}

char mouseCoords[256];
void Render() {
    snprintf(mouseCoords, sizeof(mouseCoords), "x:%d,y:%d", Mouse.x, Mouse.y); 
    RenderText(mouseCoords, 0, 32, NULL, NULL);
    RenderPlayer();
}