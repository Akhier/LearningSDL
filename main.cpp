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
    SDL_Quit();
    return 0;
}
