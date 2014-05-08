#include "sdlwrapper.h"

SDLWrapper::SDLWrapper()
{
    //ctor
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
