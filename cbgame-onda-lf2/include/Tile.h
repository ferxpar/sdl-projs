#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_image.h>

#include "../globales.h"
#include "Screen.h"

class Tile
{
    public:
        Tile();
        Tile(SDL_Surface *tileset, SDL_Rect *quad);
        ~Tile();

        void render(Screen *screen, int x, int y);


    private:

        SDL_Surface *_tileset;
        SDL_Rect *_quad;

};

#endif // TILE_H
