#ifndef SDLWRAPPER_H
#define SDLWRAPPER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <map>

class SDLWrapper
{
    public:
        SDLWrapper();
        void createWindow(const std::string windowtitle, int x, int y, int width, int height);
        virtual ~SDLWrapper();
        int createText(const std::string &message);
        int createTexture(const std::string &file);
        void renderTexture(int textureid, int x, int y, int w, int h);
        void renderTexture(int textureid, int x, int y);
        void renderTexture(int textureid, int destinationrect[4], int clip[4]);
        void renderTexture(int textureid, int x, int y, int clip[4]);
        void destroyTexture(int textureid);
        void setupTileset(int textureid, int tilesetinfo[4]);
        void setupTileset(int textureid, int tiles, int tilesetinfo[][4]);
        void setFont(const std::string &font, int fontsize);
        void renderClear();
        void renderPresent();
    private:
        void _logerror(std::ostream &os, const std::string &message) {os << message << " Error: " << SDL_GetError() << std::endl;}
        int _sdlwrapperfailedtoinit = -1;
        SDL_Texture* _loadtexture(const std::string &file, SDL_Renderer *renderer);
        SDL_Texture* _rendertext(const std::string &message, SDL_Color color);
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        TTF_Font* _font;
        std::vector<SDL_Texture*> _textures;
        std::map<int, std::vector<SDL_Rect>> _tilesetdefinition;
};

#endif // SDLWRAPPER_H
