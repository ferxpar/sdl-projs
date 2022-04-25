#ifndef MAP_H
#define MAP_H

#include "Screen.h"
#include "Tile.h"

class Map
{
    public:
        Map(Tile areaTiles[12], Tile areaBg[12]);
        ~Map();

        void update();
        void render(Screen *screen);

        void moveCam(int movex);

    private:

        int _xcam;

        Tile _areaFloor[12];
        Tile _areaBg[12];
        SDL_Rect _playArea;


};

#endif // MAP_H
