#include <iostream>
#include <string>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "globales.h"
#include "Timer.h"

#include "SurfaceHandler.h"

#include "Screen.h"
#include "Tile.h"
#include "Map.h"
#include "Player.h"
#include "Battle.h"

using namespace std;

SDL_Window  *globalWindow = nullptr;
SDL_Surface *globalSurface = nullptr;
TTF_Font    *globalFont = nullptr;
SDL_Surface *scaledSurface = nullptr;
bool globalLoop = true;

bool init(){
    bool success = true;

    SDL_Init(SDL_INIT_VIDEO);

    globalWindow = SDL_CreateWindow(GAME_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!globalWindow){
        cout << "Error creando la ventana SDL: " << SDL_GetError() << endl;
        success = false;
    } else {
        cout << "Se creo ventana con W = " << WINDOW_WIDTH << ", H = " << WINDOW_HEIGHT << endl;
        globalSurface = SDL_GetWindowSurface(globalWindow);
        if (!globalSurface){
            cout << "Error obteniendo canvas SDL: " << SDL_GetError() << endl;
            success = false;
        } else {
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)){
                cout << "Error creando SDL_IMG: " << IMG_GetError() << endl;
                success = false;
            } else {
                if(TTF_Init() == -1){
                    cout << "Error creando TTF: " << TTF_GetError() << endl;
                    success = false;
                }
            }
        }
    }

    scaledSurface = SDL_CreateRGBSurface(0, GAME_WIDTH, GAME_HEIGHT, 32, 0, 0 ,0 ,0);
    if(scaledSurface == NULL){
        cout << "Error creando surface escalada: " << SDL_GetError() << endl;
        success = false;
    } else {
        cout << "Se creo surface escalada con W = " << GAME_WIDTH << ", H = " << GAME_HEIGHT << endl;
    }

    if(success)
        cout << "Init OK." << endl;

    return success;
}

bool loadMedia(SurfaceHandler *surf){
    bool success = true;

    globalFont = TTF_OpenFont("spr/joysticmono.ttf", 24);

    if(globalFont == NULL){
        cout << "No se pudo leer font: " << TTF_GetError() << endl;
        success = false;
    }

    if(success)
        cout << "Font OK." << endl;

    //textures and text
    surf->loadText("init1", COLOR_WHITE, TEXT_ONE);
    surf->loadText("init2", COLOR_WHITE, TEXT_TWO);
    surf->loadText("init3", COLOR_WHITE, TEXT_THREE);
    surf->loadText("init4", COLOR_WHITE, TEXT_FOUR);
    surf->loadTileset("spr/tileset.png", TILESET_WIDTH, TILESET_HEIGHT, TILE_SIZE);

    return success;
}

void close(){
    TTF_CloseFont(globalFont);
    globalFont = nullptr;

    SDL_FreeSurface(scaledSurface);
    scaledSurface = nullptr;

    SDL_FreeSurface(globalSurface);
    globalSurface = nullptr;

    SDL_DestroyWindow(globalWindow);
    globalWindow = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argv, char** args){

    if(!init()){
        return -1;
    }

    SDL_Event e;
    Screen screen(globalWindow, globalSurface, scaledSurface);
    SurfaceHandler surfHandler(globalSurface);

    if(!loadMedia(&surfHandler)){
        return -3;
    }

    Tile floorTiles[12];
    for(int y = 0; y < TILESET_FLOOR_HEIGHT; y++){
        for(int x = 0; x < TILESET_FLOOR_WIDTH; x++){
            Tile temp(surfHandler.getTileset(), surfHandler.getQuad(x, y));
            int place = x + y * TILESET_FLOOR_WIDTH;
            floorTiles[place] = temp;
        }
    }

    Tile bgTiles[12];
    for(int y = 0; y < TILESET_BG_HEIGHT; y++){
        int tileOffset = 4;
        for(int x = 0; x < TILESET_BG_WIDTH; x++){
            Tile temp(surfHandler.getTileset(), surfHandler.getQuad(x, y + tileOffset));
            int place = x + y * TILESET_FLOOR_WIDTH;
            bgTiles[place] = temp;
        }
    }

    Player plr;
    Battle battle(floorTiles, bgTiles, plr);

    Timer fpsTimer;
    Timer capTimer;
    stringstream fpsText;
    int countedFrames = 0;
    float avgFPS = 0;
    fpsTimer.start();
    string windowName = GAME_NAME + " ";

    while (globalLoop){
        //Clear screen
        screen.cls();
        //FPS Cap timer
        capTimer.start();
        //Calcular fps promedio
        avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 ) {
            avgFPS = 0;
        }
        //render fps text
        fpsText.str( "" );
        fpsText << "FPS " << avgFPS;
        surfHandler.updateText(fpsText.str(), COLOR_WHITE, TEXT_ONE);
        //fps title
        SDL_SetWindowTitle(globalWindow, fpsText.str().c_str());

        //Input
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT ){
                globalLoop = false;
            }
            battle.inputBattle(e);
        }

        //update here
        battle.updateBattle();

        //render here
        battle.renderMap(&screen);
        battle.renderMobs(&surfHandler, &screen);

        //scale pixel art
        screen.scale();

        //GUI, debug and on screen data
        screen.renderFull(surfHandler.getText(TEXT_ONE), NULL);

        //flip
        screen.flip();

        countedFrames++;
        int frameTicks = capTimer.getTicks();
        if( frameTicks < GAME_TICKS_PER_FRAME ){
            //Wait remaining time
            SDL_Delay( GAME_TICKS_PER_FRAME - frameTicks);
        }
    }

    close();
    return 0;
}

