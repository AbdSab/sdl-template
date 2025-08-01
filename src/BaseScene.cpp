#include "BaseScene.h"
#include "assets.h"
#include "engine/Input.h"
#include "engine/Renderer.h"
#include <common.h>
#include <scenes/GameScene.h>


void Init() {
    Fonts_Init("pixel.ttf");
    Textures_Init();
    Audio_Init();
    Scene_Set(&GameScene);
}

void Update(double dt) {
    CurrentScene->Update(dt);
}

void Render() {
    CurrentScene->Render();
}