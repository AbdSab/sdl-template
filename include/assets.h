#pragma once

#include <SDL2/SDL_ttf.h>

#define ASSETS_NAME_MAX_LENGTH 256

//----Textures----
#define TOTAL_TEXTURES 32

extern SDL_Texture* textures[TOTAL_TEXTURES];

bool Textures_Init();
SDL_Texture* Textures_Load(int index, const char* filepath);
void Textures_Clear();



//----Font--------
#define TOTAL_FONTS 3

#define FONT_DEFAULT 0
#define FONT_SMALL 1
#define FONT_LARGE 2

const int FONT_SIZES[TOTAL_FONTS] = {24, 12, 48};
extern TTF_Font* fonts[TOTAL_FONTS];

bool Fonts_Init(const char* path);
TTF_Font* Fonts_Get(int size);
void Fonts_Clear();
