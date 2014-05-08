#ifndef SDLWRAPPER_H
#define SDLWRAPPER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class SDLWrapper
{
    public:
        SDLWrapper();
        virtual ~SDLWrapper();
        SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);
    private:
        void _logerror(std::ostream &os, const std::string &message) {os << message << " Error: " << SDL_GetError() << std::endl;}
};

#endif // SDLWRAPPER_H
