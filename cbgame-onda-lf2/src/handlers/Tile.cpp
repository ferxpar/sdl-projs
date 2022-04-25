#include "Tile.h"

Tile::Tile() : _tileset(nullptr), _quad(nullptr){
}

Tile::Tile(SDL_Surface *tileset, SDL_Rect *quad) : _tileset(tileset), _quad(quad){
}

Tile::~Tile(){
    //dtor
}

void Tile::render(Screen *screen, int x, int y){
    SDL_Rect pos = {x, y, TILE_SIZE, TILE_SIZE};
    screen->scaledQuad(_tileset, _quad, &pos);
}
