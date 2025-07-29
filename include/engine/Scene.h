#pragma once

typedef void (*SceneInitFunc)(void);
typedef void (*SceneUpdateFunc)(float);
typedef void (*SceneRenderFunc)();
typedef void (*SceneClearFunc)();

typedef struct {
    SceneInitFunc Init;
    SceneUpdateFunc Update;
    SceneRenderFunc Render;
    SceneClearFunc Clear;
} Scene;

void Scene_Set(Scene* newScene);

extern Scene* CurrentScene;