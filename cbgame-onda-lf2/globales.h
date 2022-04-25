#ifndef __GLOBALES_H__
#define __GLOBALES_H__

#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

typedef SDL_Surface Sprite;
typedef SDL_Rect Quad;


const std::string GAME_NAME = "Game";
const int GAME_WIDTH = 224;  //14 tiles de 16 largo
const int GAME_HEIGHT = 128; //8 tiles de 16 alto
const int GAME_SCALE = 4;
const int GAME_FPS = 60;
const int GAME_TICKS_PER_FRAME = 1000 / GAME_FPS;

//ventana
const int WINDOW_WIDTH = GAME_WIDTH * GAME_SCALE;
const int WINDOW_HEIGHT = GAME_HEIGHT * GAME_SCALE;

//surfaces
enum textID{
    TEXT_ONE,
    TEXT_TWO,
    TEXT_THREE,
    TEXT_FOUR,
    TEXT_SIZE
};

//game vars
const SDL_Rect PLAY_AREA = {0, GAME_HEIGHT / 2, GAME_WIDTH, GAME_HEIGHT};
const float GRAVITY = 0.2;

//tileset floor vars
const int TILESET_WIDTH = 256;
const int TILESET_HEIGHT = 256;
const int TILE_SIZE = 16;
const int TILESET_WIDTH_TILES = TILESET_WIDTH / TILE_SIZE;
const int TILESET_HEIGHT_TILES = TILESET_HEIGHT / TILE_SIZE;

const int TILESET_FLOOR_WIDTH = 3;
const int TILESET_FLOOR_HEIGHT = 4;
const int TILESET_BG_WIDTH = 3;
const int TILESET_BG_HEIGHT = 4;

const int TILE_LOOP = TILE_SIZE * TILESET_FLOOR_WIDTH;
const int TILES_PER_WIDTH = GAME_WIDTH / TILE_SIZE;
const int TILES_PER_HEIGHT = GAME_HEIGHT / TILE_SIZE;

//colores
const SDL_Color COLOR_WHITE = {255,255,255};
const SDL_Color COLOR_DARK_BLUE = {0, 43, 128};
const SDL_Color COLOR_RED = {255, 0, 0};

#endif // __GLOBALES_H__
