#pragma once
#include <engine/Scene.h>

#define START_TEXT "Press Enter to Start"

void MainMenu_Init();
void MainMenu_Update(float dt);
void MainMenu_Render();

extern Scene MainMenuScene;