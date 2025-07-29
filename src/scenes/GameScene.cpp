#include "scenes/GameScene.h"
#include <engine/Scene.h>
#include <common.h>

Scene GameScene = {
    .Init = Game_Init,
    .Update = Game_Update,
    .Render = Game_Render
};

void Game_Init() {

}
void Game_Update(float dt) {

}
void Game_Render() {
    RenderText("Game Scene !", 200, 200, NULL, NULL);
}
