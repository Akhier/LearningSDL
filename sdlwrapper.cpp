#include "sdlwrapper.h"

SDLWrapper::SDLWrapper()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        _logerror(std::cout, "SDL_Init");
        _sdlwrapperfailedtoinit = 0;
    }
    if (TTF_Init() != 0){
        _logerror(std::cout, "TTF_Init");
        _sdlwrapperfailedtoinit = 1;
    }
    _window = SDL_CreateWindow("LearningSDL", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        _logerror(std::cout, "SDL_CreateWindow");
        _sdlwrapperfailedtoinit = 2;
    }
    _renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        _logerror(std::cout, "SDL_CreateRenderer");
        _sdlwrapperfailedtoinit = 3;
    }
}

SDLWrapper::~SDLWrapper()
{
    //dtor
}

SDL_Texture* SDLWrapper::loadTexture(const std::string &file, SDL_Renderer *renderer){
    SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr){
        _logerror(std::cout, "LoadTexture");
    }
    return texture;
}

void SDLWrapper::renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h){
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    destination.w = w;
    destination.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void SDLWrapper::renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect destination, SDL_Rect *clip = nullptr){
    SDL_RenderCopy(renderer, texture, clip, &destination);
}

void SDLWrapper::renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = nullptr){
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

SDL_Texture* SDLWrapper::renderText(const std::string &message, const std::string &fontfile, SDL_Color color, int fontsize, SDL_Renderer *renderer){
    TTF_Font *font = TTF_OpenFont(fontfile.c_str(), fontsize);
    if (font == nullptr){
        _logerror(std::cout, "TTF_OpenFont");
        return nullptr;
    }
    SDL_Surface *surface = TTF_RenderText_Blended(font, message.c_str(), color);
    if (surface == nullptr){
        TTF_CloseFont(font);
        _logerror(std::cout, "TTF_RenderText");
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr){
        _logerror(std::cout, "CreateTextureFromSurface");
    }
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;
}
