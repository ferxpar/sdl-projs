#include "SurfaceHandler.h"

SurfaceHandler::SurfaceHandler(SDL_Surface *screen) : _screenSurface(screen), _tiles(nullptr){
    for(int i = 0; i < TEXT_SIZE; i++){
        _text[i] = nullptr;
    }

    int w = TILESET_WIDTH_TILES;
    int h = TILESET_HEIGHT_TILES;

    for(int y = 0; y < h; y++){
        int qy = y * TILE_SIZE;

        for(int x = 0; x < w; x++){
            int qx = x * TILE_SIZE;
            Quad *quad = new Quad({qx, qy, TILE_SIZE, TILE_SIZE});
            _quads.push_back(quad);
        }
    }
}

SurfaceHandler::~SurfaceHandler(){
    for(unsigned int i = 0; i < _quads.size(); i++){
        delete(_quads[_quads.size()-1]);
        _quads.pop_back();
    }

    free(_text[TEXT_ONE]);
    free(_text[TEXT_TWO]);
    free(_text[TEXT_THREE]);
    free(_text[TEXT_FOUR]);

    free(_tiles);
    free(_tilesFlip);
    _screenSurface = nullptr;
}

void SurfaceHandler::loadTileset(std::string path, int width, int height, int spriteSize){
    SDL_Surface *temp = nullptr;
    temp = IMG_Load(path.c_str());

    if(temp == NULL){
        std::cout << "Error leyendo tileset," << " Error: " << IMG_GetError() << std::endl;
    } else{
        SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB( temp->format, 0xFF, 0, 0xFF ) );
    }

    SDL_Surface *optimized = nullptr;
    optimized = optimize(temp);

    if(optimized == NULL){
        std::cout << "Error optimizando tileset," << " Error: " << IMG_GetError() << std::endl;
    } else {
        SDL_FreeSurface(temp);
        temp = nullptr;
    }

    _tiles = optimized;
    _tilesFlip = flipSurface(optimized);
}

extern TTF_Font *globalFont;
void SurfaceHandler::loadText(std::string text, SDL_Color color, textID id){
    SDL_Surface *textSur = nullptr;
    textSur = TTF_RenderText_Solid(globalFont, text.c_str(), color);

    if(textSur == NULL){
        std::cout << "No se pudo cargar texto en loadText: " << TTF_GetError() << std::endl;
    } else {
        _text[id] = textSur;
    }
}

void SurfaceHandler::updateText(std::string text, SDL_Color color, textID id){

    SDL_Surface *temp = nullptr;
    temp = TTF_RenderText_Solid(globalFont, text.c_str(), color);

    if(temp == NULL){
        std::cout << "No se pudo cargar texto en loadFromText: " << TTF_GetError() << std::endl;
    } else {
        free(_text[id]);
        _text[id] = temp;
    }
}

SDL_Surface* SurfaceHandler::optimize(SDL_Surface *surf){
    SDL_Surface *optimized = nullptr;
    optimized = SDL_ConvertSurface(surf, _screenSurface->format, 0);

    if(optimized == NULL){
        std::cout << "Error optimizando media." << std::endl;
    }

    return optimized;
}

void SurfaceHandler::free(SDL_Surface *surf){
    if(surf != nullptr){
        SDL_FreeSurface(surf);
        surf = nullptr;
    }
}

SDL_Surface* SurfaceHandler::getTileset(){
    return _tiles;
}

bool SurfaceHandler::isTilesetLoaded(){
    return _tiles != nullptr;
}

SDL_Surface* SurfaceHandler::getText(textID id){
    return _text[id];
}

Quad* SurfaceHandler::getQuad(int x, int y){
    return _quads[x + y * TILESET_WIDTH_TILES];
}

void SurfaceHandler::renderQuad(int xTile, int yTile, Quad *pos, Screen *screen){
    screen->scaledQuad(_tiles, getQuad(xTile, yTile), pos);
}

Uint32 SurfaceHandler::getPixel(int x, int y, SDL_Surface *surf){
    Uint32 *pixels = (Uint32 *)surf->pixels;
    return pixels[x + y * surf->w];
}

void SurfaceHandler::setPixel(int x, int y, Uint32 pixel, SDL_Surface *placeSurf){
    Uint32 *pixels = (Uint32 *)placeSurf->pixels;
    pixels[x + y * placeSurf->w] = pixel;
}

SDL_Surface* SurfaceHandler::flipSurface(SDL_Surface *refSurf){
    SDL_Surface *flipped = nullptr;

    flipped = SDL_CreateRGBSurface(0, refSurf->w, refSurf->h, refSurf->format->BitsPerPixel, refSurf->format->Rmask,
                                                                                             refSurf->format->Gmask,
                                                                                             refSurf->format->Bmask,
                                                                                             0);

    if(SDL_MUSTLOCK(refSurf)){
        SDL_LockSurface(refSurf);
    }

    for(int y = 0; y < refSurf->h; y++){
        for(int x = 0; x < refSurf->w; x++){

            int row = x / TILE_SIZE;
            int flip_x = (x % TILE_SIZE);

            int x_flipped = (TILE_SIZE - 1 - flip_x) + (row * TILE_SIZE);


            Uint32 pixel = getPixel(x, y, refSurf);

            setPixel(x_flipped, y, pixel, flipped);


        }
    }

    if(SDL_MUSTLOCK(refSurf)){
        SDL_UnlockSurface(refSurf);
    }

    SDL_SetColorKey(flipped, SDL_TRUE, SDL_MapRGB( refSurf->format, 0xFF, 0, 0xFF ) );


    return flipped;

}


void SurfaceHandler::renderQuadFlip(int xTile, int yTile, Quad *pos, Screen *screen){
    screen->scaledQuad(_tilesFlip, getQuad(xTile, yTile), pos);
}
