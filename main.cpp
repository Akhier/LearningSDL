//By: Akhier Dragonheart
//Using: TwinklebearDev SDL2 Tutorial at http://www.willusher.io/pages/sdl2/

#include "sdlwrapper.h"

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
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect destination, SDL_Rect *clip = nullptr){
    SDL_RenderCopy(renderer, texture, clip, &destination);
}
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = nullptr){
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    if (clip != nullptr){
        destination.w = clip->w;
        destination.h = clip->h;
    }
    else{
        SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
    }
    renderTexture(texture, renderer, destination, clip);
}

SDL_Texture* renderText(const std::string &message, const std::string &fontfile, SDL_Color color, int fontsize, SDL_Renderer *renderer){
    TTF_Font *font = TTF_OpenFont(fontfile.c_str(), fontsize);
    if (font == nullptr){
        logSDLError(std::cout, "TTF_OpenFont");
        return nullptr;
    }
    SDL_Surface *surface = TTF_RenderText_Blended(font, message.c_str(), color);
    if (surface == nullptr){
        TTF_CloseFont(font);
        logSDLError(std::cout, "TTF_RenderText");
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr){
        logSDLError(std::cout, "CreateTextureFromSurface");
    }
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;
}

int main(int argc, char **argv){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }
    if (TTF_Init() != 0){
        logSDLError(std::cout, "TTF_Init");
        return 2;
    }

    SDL_Window *window = SDL_CreateWindow("LearningSDL", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        logSDLError(std::cout, "SDL_CreateWindow");
        return 3;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        logSDLError(std::cout, "SDL_CreateRenderer");
        return 4;
    }

    SDL_Texture *background = loadTexture("background.bmp", renderer);
    SDL_Texture *image = loadTexture("sample.png", renderer);
    if (background == nullptr || image == nullptr){
        return 5;
    }

    int imageWidth = 100, imageHeight = 100;
    int x = SCREEN_WIDTH / 2 - imageWidth / 2, y = SCREEN_HEIGHT / 2 - imageHeight / 2;
    SDL_Rect clips[4];
    for (int pos = 0; pos < 4; ++pos){
        clips[pos].x = pos / 2 * imageWidth;
        clips[pos].y = pos % 2 * imageHeight;
        clips[pos].w = imageWidth;
        clips[pos].h = imageHeight;
    }
    int useClip = 0;

    std::string fontLocation = "fonts/FreeMono.ttf";

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
                        fontLocation = "fonts/FreeMono.ttf";
                        break;
                    case SDLK_6:
                        fontLocation = "fonts/FreeSans.ttf";
                        break;
                    case SDLK_7:
                        fontLocation = "fonts/FreeSerif.ttf";
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

        SDL_RenderClear(renderer);
        int xTiles = SCREEN_WIDTH / TILE_SIZE, yTiles = SCREEN_HEIGHT / TILE_SIZE;
        for (int pos = 0; pos < xTiles * yTiles; ++pos){
            int x = pos % xTiles;
            int y = pos / xTiles;
            renderTexture(background, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }
        renderTexture(image, renderer, x, y, &clips[useClip]);

        SDL_Color color = {0, 0, 0};
        SDL_Texture *words = renderText("test string", fontLocation, color, 32, renderer);
        if (words == nullptr){
            return 6;
        }
        renderTexture(words, renderer, 0, 0);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
