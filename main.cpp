//By: Akhier Dragonheart
//Using: TwinklebearDev SDL2 Tutorial at http://www.willusher.io/pages/sdl2/

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480, TILE_SIZE = 40;

void logSDLError(std::ostream &os, const std::string &message){
    os << message << " Error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer){
    SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr){
        logSDLError(std::cout, "LoadTexture");
    }
    return texture;
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h){
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    destination.w = w;
    destination.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &destination);
}
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y){
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    renderTexture(texture, renderer, x, y, w, h);
}

int main(int argc, char **argv){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("LearningSDL", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        logSDLError(std::cout, "SDL_CreateWindow");
        return 2;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        logSDLError(std::cout, "SDL_CreateRenderer");
        return 3;
    }
    SDL_Texture *background = loadTexture("background.bmp", renderer);
    SDL_Texture *image = loadTexture("sample.png", renderer);
    if (background == nullptr || image == nullptr){
        return 4;
    }
    SDL_RenderClear(renderer);
    int xTiles = SCREEN_WIDTH / TILE_SIZE, yTiles = SCREEN_HEIGHT / TILE_SIZE;
    for (int pos = 0; pos < xTiles * yTiles; ++pos){
        int x = pos % xTiles;
        int y = pos / xTiles;
        renderTexture(background, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    }
    int imageWidth, imageHeight;
    SDL_QueryTexture(image, NULL, NULL, &imageWidth, &imageHeight);
    renderTexture(image, renderer, SCREEN_WIDTH / 2 - imageWidth / 2, SCREEN_HEIGHT / 2 - imageHeight / 2);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
