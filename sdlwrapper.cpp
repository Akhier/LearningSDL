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

SDL_Texture* SDLWrapper::_rendertext(const std::string &message, const std::string &fontfile, SDL_Color color, int fontsize, SDL_Renderer *renderer){
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

int SDLWrapper::createText(const std::string &message, const std::string &fontfile, int fontsize){
    SDL_Color color = {0, 0, 0};
    _textures.push_back(_rendertext(message, fontfile, color, fontsize, _renderer));
    return _textures.size() - 1;
}

int SDLWrapper::createTexture(std::string &file){
    _textures.push_back(_loadtexture(file, _renderer));
    return _textures.size() - 1;
}

void SDLWrapper::destroyTexture(int textureid){
    SDL_DestroyTexture(_textures[textureid]);
}

void SDLWrapper::setupTileset(int textureid, std::vector<int[]> *tilesetinfo){
    for (int iter = 0; iter < tilesetinfo.size(); ++iter){
        SDL_Rect tempRect;
        temp.x = tilesetinfo[iter][0];
        temp.y = tilesetinfo[iter][1];
        temp.w = tilesetinfo[iter][2];
        temp.h = tilesetinfo[iter][3];
        _tilesetdefinition[textureid].push_back(tempRect);
    }
}

void SDLWrapper::renderClear(){
    SDL_RenderClear(_renderer);
}

void SDLWrapper::renderPresent(){
    SDL_RenderPresent(_renderer);
}

SDLWrapper::~SDLWrapper(){
    //dtor
}
