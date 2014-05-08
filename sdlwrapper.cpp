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
