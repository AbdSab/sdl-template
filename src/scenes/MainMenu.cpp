#include "scenes/MainMenu.h"
#include "common.h"
#include "engine/input.h"
#include <scenes/GameScene.h>

Scene MainMenuScene = {
    .Init = MainMenu_Init,
    .Update = MainMenu_Update,
    .Render = MainMenu_Render
};

void MainMenu_Init() {

}

void MainMenu_Update(float dt) {
    if(Input.action) {
        Scene_Set(&GameScene);
    }
}

void MainMenu_Render() {
    RenderText(START_TEXT, 200, 200, NULL, NULL);
}