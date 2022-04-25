#include "Map.h"

Map::Map(Tile areaTiles[12], Tile areaBg[12]) : _playArea(PLAY_AREA)
{
    for(int i = 0; i < 12; i++){
        _areaFloor[i] = areaTiles[i];
    }

    for(int j = 0; j < 12; j++){
        _areaBg[j] = areaBg[j];
    }

    _xcam = 0;
}

Map::~Map()
{
    //dtor
}

void Map::update(){
    //_xcam--;
}

void Map::render(Screen *screen){

    //render floor
    for(int x = 0; x < TILES_PER_WIDTH + TILESET_FLOOR_WIDTH*2; x++){
        int spriteSwitch = x % TILESET_FLOOR_WIDTH;

        int xcamCorrection = (-_xcam) % (TILE_SIZE*TILESET_FLOOR_WIDTH);
        // mult por cant de  tiles diferentes que loopean

        int xoffset = (x * TILE_SIZE) + xcamCorrection;
        //cada tile en su columna correspondiente

        int xrelative = xoffset - TILESET_FLOOR_WIDTH * TILE_SIZE;

        _areaFloor[0                       + spriteSwitch].render(screen, xrelative, _playArea.y);
        _areaFloor[    TILESET_FLOOR_WIDTH + spriteSwitch].render(screen, xrelative, _playArea.y + TILE_SIZE);
        _areaFloor[2 * TILESET_FLOOR_WIDTH + spriteSwitch].render(screen, xrelative, _playArea.y + TILE_SIZE * 2);
        _areaFloor[3 * TILESET_FLOOR_WIDTH + spriteSwitch].render(screen, xrelative, _playArea.y + TILE_SIZE * 3);
    }


    //render bg
    for(int x = 0; x < TILES_PER_WIDTH + TILESET_FLOOR_WIDTH*2; x++){
        int spriteSwitch = x % TILESET_FLOOR_WIDTH;

        int xslowCorrection = (-_xcam/2) % (TILE_SIZE*TILESET_FLOOR_WIDTH);
        int xslowerCorrection = (-_xcam/8) % (TILE_SIZE*TILESET_FLOOR_WIDTH);
        // mult por cant de  tiles diferentes que loopean

        int xoffset_slow = (x * TILE_SIZE) + xslowCorrection;
        int xoffset_slower = (x * TILE_SIZE) + xslowerCorrection;
        //cada tile en su columna correspondiente

        int xrelative_slow = xoffset_slow - TILESET_FLOOR_WIDTH * TILE_SIZE;
        int xrelative_slower = xoffset_slower - TILESET_FLOOR_WIDTH * TILE_SIZE;

        _areaBg[0                       + spriteSwitch].render(screen, xrelative_slower, 0);
        _areaBg[    TILESET_FLOOR_WIDTH + spriteSwitch].render(screen, xrelative_slower, TILE_SIZE);
        _areaBg[2 * TILESET_FLOOR_WIDTH + spriteSwitch].render(screen, xrelative_slower, TILE_SIZE * 2);
        _areaBg[3 * TILESET_FLOOR_WIDTH + spriteSwitch].render(screen, xrelative_slow, TILE_SIZE * 3);
    }
}

void Map::moveCam(int movex){
    _xcam += movex % TILE_LOOP;
}
