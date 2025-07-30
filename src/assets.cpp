#include "assets.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <engine/Renderer.h>

//Images
SDL_Texture* textures[TOTAL_TEXTURES] = { NULL };

bool Textures_Init() {
    for (int i = 0; i < TOTAL_TEXTURES; ++i) {
        textures[i] = NULL;
    }
    return true;
}

SDL_Texture* Textures_Load(int index, const char* filepath) {
    char fullpath[ASSETS_NAME_MAX_LENGTH];

    if (index < 0 || index >= TOTAL_TEXTURES) {
        SDL_Log("Textures_Load: index out of bounds\n");
        return NULL;
    }

    snprintf(fullpath, sizeof(fullpath), "assets/%s", filepath);
    SDL_Surface* surface = IMG_Load(fullpath);
    if (!surface) {
        SDL_Log("IMG_Load failed for %s: %s\n", fullpath, IMG_GetError());
        return NULL;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_FreeSurface(surface);

    if (!tex) {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
        return NULL;
    }

    textures[index] = tex;
    return textures[index];
}

void Textures_Clear(void) {
    for (int i = 0; i < TOTAL_TEXTURES; ++i) {
        if (textures[i]) {
            SDL_DestroyTexture(textures[i]);
            textures[i] = NULL;
        }
    }
}

//Audio
Mix_Chunk* audios[TOTAL_AUDIO] = { NULL };
bool Audio_Init() {
    for (int i = 0; i < TOTAL_AUDIO; ++i) {
        audios[i] = NULL;
    }
    return true;
}
Mix_Chunk* Audio_Load(int index, const char* filepath) {
    if(audios[index] == NULL) {
        char fullpath[ASSETS_NAME_MAX_LENGTH];
        snprintf(fullpath, sizeof(fullpath), "assets/%s", filepath);
        audios[index] = Mix_LoadWAV(fullpath);

        if (!audios[index]) {
            SDL_Log("Mix_LoadWAV Error: %s\n", Mix_GetError());
            Mix_Quit();
            SDL_Quit();
            return NULL;
        }
    }

    return audios[index];
}
void Audio_Clear() {
    for (int i = 0; i < TOTAL_AUDIO; ++i) {
        if (audios[i]) {
            Mix_FreeChunk(audios[i]);
            audios[i] = NULL;
        }
    }
}


//Fonts
TTF_Font* fonts[TOTAL_FONTS] = { NULL };

bool Fonts_Init(const char* path) {
    char fullpath[ASSETS_NAME_MAX_LENGTH];

    for(int i=0; i<TOTAL_FONTS; i++) {
        snprintf(fullpath, sizeof(fullpath), "assets/%s", path);
        fonts[i] = TTF_OpenFont(fullpath, FONT_SIZES[i]);
        if (!fonts[i]) {
            SDL_Log("TTF_OpenFont failed: %s", TTF_GetError());
            return false;
        }
    }
    return true;
}

TTF_Font* Fonts_Get(int size) {
    return fonts[size];
}
    

void Fonts_Clear() {
    for(int i=0; i<TOTAL_FONTS; i++) {
        TTF_CloseFont(fonts[i]);
        fonts[i] = NULL;
    }
}