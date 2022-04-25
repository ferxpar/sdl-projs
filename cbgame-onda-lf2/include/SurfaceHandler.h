#ifndef SURFACEHANDLER_H
#define SURFACEHANDLER_H

#include <iostream>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../globales.h"
#include "Screen.h"

class SurfaceHandler
{
    public:
        SurfaceHandler(SDL_Surface *screen);
        ~SurfaceHandler();

        void loadTileset(std::string path, int width, int height, int spriteSize);
        //carga un tileset

        void loadText(std::string text, SDL_Color color, textID id);
        //carga texto en un ID (1-4)

        void updateText(std::string text, SDL_Color color, textID id);
        //Desc: carga en la sprite _text un nuevo surface de texto, el anterior lo borra.
        //Aliasing: la surface en _text es intercambiada por una nueva surface con el texto nuevo.

        SDL_Surface* optimize(SDL_Surface* surf);
        //optimiza surface

        void free(SDL_Surface *surf);
        //libera recursos, pone el parametro a nullpointer

        SDL_Surface* getTileset();
        //devuelve tileset

        bool isTilesetLoaded();
        //devuelve true si hay un tilesetcargado

        SDL_Surface* getText(textID id);
        //devuelve texto

        Quad* getQuad(int x, int y);

        void renderQuad(int xTile, int yTile, Quad *pos, Screen *screen);

        void renderQuadFlip(int xTile, int yTile, Quad *pos, Screen *screen);

        SDL_Surface* flipSurface(SDL_Surface *refSurf);

        Uint32 getPixel(int x, int y, SDL_Surface *surf);

        void setPixel(int x, int y, Uint32 pixel, SDL_Surface *placeSurf);

    private:

        SDL_Surface *_screenSurface;

        SDL_Surface *_text[TEXT_SIZE];

        SDL_Surface *_tiles;
        SDL_Surface *_tilesFlip;

        std::vector<Quad*> _quads;
};

#endif // SURFACEHANDLER_H
