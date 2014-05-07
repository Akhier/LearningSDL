//By: Akhier Dragonheart
//Using: TwinklebearDev SDL2 Tutorial at http://www.willusher.io/pages/sdl2/

#include <SDL.h>
#include <iostream>
int main(int argc, char **argv){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("LearningSDL", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Surface *image = SDL_LoadBMP("sample.bmp");
    if (image == nullptr){
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if (texture == nullptr){
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() <<std::endl;
        return 1;
    }
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
