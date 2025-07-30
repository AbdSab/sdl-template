#include "scenes/GameScene.h"
#include <engine/Scene.h>
#include <common.h>
#include <engine/renderer.h>
#include <engine/input.h>
#include <engine/Game.h>
#include <assets.h>
#define PI 3.14159265358979323846
#define SIZE 32

#define UNIT_T 0
#define ENEMY_T 1

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

double distance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

double lookAt(double x1, double y1, double x2, double y2) {
    return atan2(y2 - y1, x2 - x1) * (180.0 / PI);
}

int sign(float x) {
    if(x == 0) return 0;
    return x > 0 ? 1 : -1;
}

float lerpAngle(float a, float b, float t) {
    float diff = fmodf(b - a + 180.0f, 360.0f) - 180.0f;
    return a + diff * t;
}

char pointerText[6];

int enemyPath[12] = { 23, 2,  15, 2, 15, 7, 7, 7, 7, 4, 0, 4};

struct Unit {
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
} units [100];

struct Enemy {
    bool active;
    float x; float y;
    int hp;
    float angle;
    int damage;
    int radius;
    int pathIndex;
    SDL_Texture* texture;
} enemies[300];

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
            units[i].damage = damage;
            units[i].radius = radius;
            units[i].texture = texture;
            return;
        }
    }
}

void CreateEnemy(SDL_Texture* texture, float x, float y, int hp, int damage, int radius) {
    for(int i=0; i< 300; i++) {
        if(!enemies[i].active) {
            enemies[i].active = true;
            enemies[i].x = x;
            enemies[i].y = y;
            enemies[i].hp = 5;
            enemies[i].damage = damage;
            enemies[i].angle = 0;
            enemies[i].radius = radius;
            enemies[i].texture = texture;
            enemies[i].pathIndex = 0;
            return;
        }
    }
}

void UpdateEnemies(float dt) {
    for(int i=0; i<300; i++) {
        if(!enemies[i].active) continue;

        float targetX = enemyPath[enemies[i].pathIndex];
        float targetY = enemyPath[enemies[i].pathIndex + 1];

        float dx = targetX - enemies[i].x;
        float dy = targetY - enemies[i].y;
        float dist = sqrtf(dx*dx + dy*dy);

        float speed = 3.0f;

        if (dist > 0.01f) {
            float move = fminf(speed * dt, dist);
            float dirX = dx / dist;
            float dirY = dy / dist;

            enemies[i].x += dirX * move;
            enemies[i].y += dirY * move;
        }
         if (dist <= 0.1f) {
            enemies[i].pathIndex += 2;
            if (enemies[i].pathIndex >= 10) {
                enemies[i].pathIndex = 10;
            }
        }

        float look = lookAt(enemies[i].x, enemies[i].y, enemyPath[enemies[i].pathIndex], enemyPath[enemies[i].pathIndex + 1]);
        enemies[i].angle = lerpAngle(enemies[i].angle, look, .1);
    }
}

void RenderEnemies() {
    for(int i=0; i<300; i++) {
        if(!enemies[i].active) continue;

        SDL_Rect pos = { enemies[i].x * SIZE, enemies[i].y * SIZE, SIZE, SIZE };
        SDL_RenderCopyEx(Renderer, enemies[i].texture, NULL, &pos, enemies[i].angle, NULL, SDL_FLIP_NONE);
    }
}

SDL_Texture* unitTexture;
SDL_Texture* enemyTexture;

void Game_Init() {
    unitTexture = Textures_Load(UNIT_T, "unit.png");
    enemyTexture = Textures_Load(ENEMY_T, "enemy.png");

    for (int i=0; i<100; i++) {
        units[i] = { 0, 0, 0, 0, 0, 0, NULL};
    }
    for (int i=0; i<300; i++) {
        enemies[i] = { 0, 0, 0, 0, 0, 0, 0, NULL};
    }

    CreateEnemy(enemyTexture, 23, 2, 10, 1, 10);
}

int timer = 0;
int pressing = false;
void Game_Update(float dt) {
    timer += dt;
    if(timer > 1) {
        timer = 0;
        CreateEnemy(enemyTexture, enemyPath[0] + 32, enemyPath[1], 10, 1, 10);
    }
    UpdateEnemies(dt);
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

    RenderEnemies();
}

void Game_Clear() {

}

Scene GameScene = {
    .Init = Game_Init,
    .Update = Game_Update,
    .Render = Game_Render,
    .Clear = Game_Clear
};