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
}

void SDLWrapper::createWindow(std::string windowtitle, int x, int y, int width, int height){
    _window = SDL_CreateWindow(windowtitle.c_str(), x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (_window == nullptr){
        _logerror(std::cout, "SDL_CreateWindow");
    }
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr){
        _logerror(std::cout, "SDL_CreateRenderer");
    }
}

SDL_Texture* SDLWrapper::_loadtexture(const std::string &file, SDL_Renderer *renderer){
    SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr){
        _logerror(std::cout, "LoadTexture");
    }
    return texture;
}

void SDLWrapper::renderTexture(int textureid, int x, int y, int w, int h){
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    destination.w = w;
    destination.h = h;
    SDL_RenderCopy(_renderer, _textures[textureid], NULL, &destination);
}

void SDLWrapper::renderTexture(int textureid, int x, int y){
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    SDL_QueryTexture(_textures[textureid], NULL, NULL, &destination.w, &destination.h);
    SDL_RenderCopy(_renderer, _textures[textureid], NULL, &destination);
}

void SDLWrapper::renderTexture(int textureid, int destinationrect[4], int cliprect[4]){
    SDL_Rect destination, clip;
    destination.x = destinationrect[0];
    destination.y = destinationrect[1];
    destination.w = destinationrect[2];
    destination.h = destinationrect[3];
    clip.x = cliprect[0];
    clip.y = cliprect[1];
    clip.w = cliprect[2];
    clip.h = cliprect[3];
    SDL_RenderCopy(_renderer, _textures[textureid], &clip, &destination);
}

void SDLWrapper::renderTexture(int textureid, int x, int y, int clip[4] = nullptr){
    SDL_Rect cliprect;
    cliprect.x = clip[0];
    cliprect.y = clip[1];
    cliprect.w = clip[2];
    cliprect.h = clip[3];
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    if (clip != nullptr){
        destination.w = clip[2];
        destination.h = clip[3];
    }
    else{
        SDL_QueryTexture(_textures[textureid], NULL, NULL, &destination.w, &destination.h);
    }
    SDL_RenderCopy(_renderer, _textures[textureid], &cliprect, &destination);
}

SDL_Texture* SDLWrapper::_rendertext(const std::string &message, SDL_Color color){
    SDL_Surface *surface = TTF_RenderText_Blended(_font, message.c_str(), color);
    if (surface == nullptr){
        _logerror(std::cout, "TTF_RenderText");
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (texture == nullptr){
        _logerror(std::cout, "CreateTextureFromSurface");
    }
    SDL_FreeSurface(surface);
    return texture;
}

int SDLWrapper::createText(const std::string &message){
    SDL_Color color = {0, 0, 0, 255};
    _textures.push_back(_rendertext(message, color));
    return _textures.size() - 1;
}

int SDLWrapper::createTexture(const std::string &file){
    _textures.push_back(_loadtexture(file, _renderer));
    return _textures.size() - 1;
}

void SDLWrapper::destroyTexture(int textureid){
    SDL_DestroyTexture(_textures[textureid]);
}

void SDLWrapper::setupTileset(int textureid, int tilesetinfo[4]){
    SDL_Rect tempRect;
    tempRect.x = tilesetinfo[0];
    tempRect.y = tilesetinfo[1];
    tempRect.w = tilesetinfo[2];
    tempRect.h = tilesetinfo[3];
    _tilesetdefinition[textureid].push_back(tempRect);
}

void SDLWrapper::setupTileset(int textureid, int tiles, int tilesetinfo[][4]){
    for (int iter = 0; iter < tiles; ++iter){
        setupTileset(textureid, tilesetinfo[iter]);
    }
}

void SDLWrapper::setFont(const std::string &font, int fontsize){
    _font = TTF_OpenFont(font.c_str(), fontsize);
}

void SDLWrapper::renderClear(){
    SDL_RenderClear(_renderer);
}

void SDLWrapper::renderPresent(){
    SDL_RenderPresent(_renderer);
}

SDLWrapper::~SDLWrapper(){
    for (size_t iter = 0; iter < _textures.size(); ++iter){
        SDL_DestroyTexture(_textures[iter]);
    }
    TTF_CloseFont(_font);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
