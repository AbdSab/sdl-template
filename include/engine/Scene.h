#pragma once

typedef void (*SceneInitFunc)(void);
typedef void (*SceneUpdateFunc)(float);
typedef void (*SceneRenderFunc)();

typedef struct {
    SceneInitFunc Init;
    SceneUpdateFunc Update;
    SceneRenderFunc Render;
} Scene;

void Scene_Set(Scene* newScene);

extern Scene* CurrentScene;