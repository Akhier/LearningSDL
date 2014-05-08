//By: Akhier Dragonheart
//Using: TwinklebearDev SDL2 Tutorial at http://www.willusher.io/pages/sdl2/

#include "sdlwrapper.h"

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480, TILE_SIZE = 40;

int main(int argc, char **argv){
    SDLWrapper* wrapper = new SDLWrapper();
    wrapper->createWindow("extraction test", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT);
    int background = wrapper->createTexture("background.bmp");
    int image = wrapper->createTexture("sample.png");
    int imageWidth = 100, imageHeight = 100;
    int x = SCREEN_WIDTH / 2 - imageWidth / 2, y = SCREEN_HEIGHT / 2 - imageHeight / 2;
    int clips[4][4];
    for (int pos = 0; pos < 4; ++pos){
        clips[pos][0] = pos / 2 * imageWidth;
        clips[pos][1] = pos % 2 * imageHeight;
        clips[pos][2] = imageWidth;
        clips[pos][3] = imageHeight;
    }
    wrapper->setupTileset(image, 4, clips);
    int useClip = 0;
    wrapper->setFont("fonts/FreeMono.ttf", 32);

    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym){
                    case SDLK_1:
                        useClip = 0;
                        break;
                    case SDLK_2:
                        useClip = 1;
                        break;
                    case SDLK_3:
                        useClip = 2;
                        break;
                    case SDLK_4:
                        useClip = 3;
                        break;
                    case SDLK_5:
                        wrapper->setFont("fonts/FreeMono.ttf", 32);
                        break;
                    case SDLK_6:
                        wrapper->setFont("fonts/FreeSans.ttf", 32);
                        break;
                    case SDLK_7:
                        wrapper->setFont("fonts/FreeSerif.ttf", 32);
                        break;
                    default:
                        quit = true;
                        break;
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
        wrapper->renderClear();
        int xTiles = SCREEN_WIDTH / TILE_SIZE, yTiles = SCREEN_HEIGHT / TILE_SIZE;
        for (int pos = 0; pos < xTiles * yTiles; ++pos){
            int x = pos % xTiles;
            int y = pos / xTiles;
            wrapper->renderTexture(background, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }
        wrapper->renderTexture(image, x, y, clips[useClip]);
        int words = wrapper->createText("test string");
        wrapper->renderTexture(words, 0, 0);
        wrapper->renderPresent();
    }
    return 0;
}
