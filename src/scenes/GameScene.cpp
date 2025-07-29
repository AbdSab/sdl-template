#include "scenes/GameScene.h"
#include <engine/Scene.h>
#include <common.h>
#include <engine/renderer.h>
#include <engine/input.h>
#include <engine/Game.h>
#include <assets.h>

#define SIZE 32

#define UNIT_T 0

char pointerText[6];

typedef struct Unit {
    bool active;
    int x;
    int y;
    int hp;
    int damage;
    int xp;
    int level;
    float angle;
    int radius;
    SDL_Texture* texture;
} Unit;

Unit units[100];

void CreateUnit(SDL_Texture* texture, int x, int y, int hp, int damage, int radius) {
    for(int i=0; i< 100; i++) {
        if(!units[i].active) {
            units[i].active = true;
            units[i].x = x;
            units[i].y = y;
            units[i].hp = 5;
            units[i].xp = 0;
            units[i].level = 1;
            units[i].angle = 0;
            units[i].radius = radius;
            units[i].texture = texture;
            return;
        }
    }
}

SDL_Texture* unitTexture;

void Game_Init() {
    unitTexture = Textures_Load(UNIT_T, "unit.png");
    for (int i=0; i<100; i++) {
        units[i] = { 0, 0, 0, 0, 0, 0, NULL};
    }
}

int pressing = false;
void Game_Update(float dt) {
    for (int i=0; i<100; i++)
     {
        if(units[i].active) {
            units[i].angle += 100 * dt;
        }
    }
    if(Mouse.left) {
        if(!pressing) {
            pressing = true;

            int x = Mouse.x / SIZE;
            int y = Mouse.y / SIZE;
            CreateUnit(unitTexture, x, y, 10, 1, 10);
        }
    } else {
        pressing = false;
    }
}

char highlightedUnitData[100];

void Game_Render() {
    int x = Mouse.x / SIZE;
    int y = Mouse.y / SIZE;
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_Rect pointer = { x * SIZE, y * SIZE, SIZE, SIZE };
    SDL_RenderDrawRect(Renderer, &pointer);

    snprintf(pointerText, sizeof(pointerText), "%d,%d", x, y);
    RenderText(pointerText, 0, 0, NULL, NULL);

    for (int i=0; i<100; i++)
     {
        if(units[i].active) {
            SDL_Rect rect = { units[i].x * SIZE, units[i].y * SIZE, SIZE, SIZE };
            SDL_RenderCopyEx(Renderer, units[i].texture, NULL, &rect, units[i].angle, NULL, SDL_FLIP_NONE);

            if(x == units[i].x && y == units[i].y) {
                snprintf(highlightedUnitData, sizeof(highlightedUnitData), "Hp: %d, Damage: %d", units[i].hp, units[i].damage);
                RenderText(highlightedUnitData, 0, 32, NULL, NULL);
            }
        }
    }
}

void Game_Clear() {

}

Scene GameScene = {
    .Init = Game_Init,
    .Update = Game_Update,
    .Render = Game_Render,
    .Clear = Game_Clear
};