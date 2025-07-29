#include "BaseScene.h"
#include "assets.h"
#include "engine/input.h"
#include "engine/renderer.h"
#include <common.h>
#include <scenes/MainMenu.h>


void Init() {
    Fonts_Init("pixel.ttf");
    Textures_Init();
    Scene_Set(&MainMenuScene);
}

void Update(double dt) {
    CurrentScene->Update(dt);
}

void Render() {
    CurrentScene->Render();
}