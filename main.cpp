//By: Akhier Dragonheart
//Using: TwinklebearDev SDL2 Tutorial at http://www.willusher.io/pages/sdl2/

#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

void logSDLError(std::ostream &os, const std::string &message){
    os << message << " Error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadBMPTexture(const std::string &file, SDL_Renderer *renderer){
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedBMP = SDL_LoadBMP(file.c_str());
    if (loadedBMP != nullptr){
        texture = SDL_CreateTextureFromSurface(renderer, loadedBMP);
        SDL_FreeSurface(loadedBMP);
        if (texture == nullptr){
            logSDLError(std::cout, "CreateTextureFromSurface");
        }
    }
    else {
        logSDLError(std::cout, "LoadBMP");
    }
    return texture;
}

int main(int argc, char **argv){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("LearningSDL", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        logSDLError(std::cout, "SDL_CreateWindow");
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        logSDLError(std::cout, "SDL_CreateRenderer");
        return 1;
    }
    SDL_Texture *texture = loadBMPTexture("sample.bmp", renderer);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
