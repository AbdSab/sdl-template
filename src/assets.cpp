#include "assets.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//Images
SDL_Texture* textures[TOTAL_TEXTURES] = { NULL };

bool Textures_Init() {
    for (int i = 0; i < TOTAL_TEXTURES; ++i) {
        textures[i] = NULL;
    }
    return true;
}

SDL_Texture* Textures_Load(SDL_Renderer* renderer, int index, const char* filepath) {
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

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
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