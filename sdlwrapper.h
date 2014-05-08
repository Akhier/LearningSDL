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
        void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
        void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect destination, SDL_Rect *clip);
        void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip);
        SDL_Texture* renderText(const std::string &message, const std::string &fontfile, SDL_Color color, int fontsize, SDL_Renderer *renderer);
    private:
        void _logerror(std::ostream &os, const std::string &message) {os << message << " Error: " << SDL_GetError() << std::endl;}
};

#endif // SDLWRAPPER_H
