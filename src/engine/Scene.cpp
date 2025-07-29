#include "engine/Scene.h"

Scene* CurrentScene = nullptr;

void Scene_Set(Scene* newScene) {
    CurrentScene = newScene;
    if (CurrentScene && CurrentScene->Init) {
        CurrentScene->Init();
    }
}