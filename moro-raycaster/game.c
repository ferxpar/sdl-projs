//Libs
#include <SDL.h>
#include <SDL2/SDL_image.h>
//Defines and macros
#include "defBoolean.h"
#include "globalVars.h"
//Helpers and etc
#include "window.h"
#include "loaderMedia.h"
#include "spriteManager.h"
//Game includes
#include "levelData.h"
#include "player.h"
#include "object.h"

//Window vars
SDL_Window *appWindow = NULL;
SDL_Renderer *appRenderer = NULL;

//SDL
int initSDL();
void quitSDL();

//Game vars
int gameRunning = TRUE;
SDL_Event events;
void update();
void render(SDL_Renderer *renderer);

//Textures
SDL_Texture *textureSheet = NULL;
int initMedia();
void unloadMedia();

int main(){
    //Init sdl
    if(initSDL() == FALSE){
        return 0;
    } else {
    	if(initMedia() == FALSE){
    		return 0;
    	}
    }

    //DEBUG: init a random obj
    //TODO: Object from map parser
    addObjectToList(initStaticObject(80, 16, 12, TRUE));


    printf("Game world working\n");

    //Init debug rectangles
    initLevelData();
    initRaycast(APP_SURFACE_WIDTH, PLAYER_FOV);
    initPlayer(16,32);

    //Game loop
    while(gameRunning){
        update();
        render(appRenderer);
    }

    printf("Game world died\n");

    //Quit sdl
    quitSDL();

    return 0;
}

void update(){

	resetVisibilityData(); //Visibility map all 0

    while(SDL_PollEvent(&events)!=0){
        if(events.type == SDL_QUIT){
            gameRunning = FALSE;
        }
    }
    playerInput(events);

    playerUpdate();

    objectUpdate();
}

void render(SDL_Renderer *renderer){
    //Empty screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    //PLAYER RAYCAST
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    playerRender(renderer);

    //Show screen
    SDL_RenderPresent(renderer);
}

int initMedia(){
	int success = TRUE;

	textureSheet = loadMedia(appRenderer, "res/tilesheetDebug.png");
	if(!textureSheet){
		success = FALSE;
	}

	if(!success){
		printf("Load Media failed from initMedia\n");
	} else {
		printf("Load Media success!\n");
	}

	initSpriteManager();

	return success;
}

void unloadMedia(){
	freeTexture(textureSheet);
}

int initSDL(){
    int success = TRUE;

    int initFlags = SDL_INIT_VIDEO;

    if((!SDL_Init(initFlags))<1){                            //If <1, couldnt init sdl
        success = FALSE;
    } else {                                                 //If sdl init was successful
        appWindow = initWindow(WINDOW_WIDTH, WINDOW_HEIGHT);               //Try init window
        if(appWindow == NULL){
            success = FALSE;
        } else {
            appRenderer = initRenderer(appWindow);          //If window init was successful
            if(appRenderer == NULL){                         //Try init renderer
                success = FALSE;
            } else {                                         //If render init was successful
                SDL_RenderSetLogicalSize(appRenderer,APP_SURFACE_WIDTH,APP_SURFACE_HEIGHT); //Set scale

                int SDL_IMG_FLAGS = IMG_INIT_PNG;	//Try init SDL_image
                int init_img = IMG_Init(SDL_IMG_FLAGS);
                if((init_img&SDL_IMG_FLAGS) != SDL_IMG_FLAGS) {
                    printf("IMG_Init: Failed to init required png support!\n");
                    printf("IMG_Init: %s\n", IMG_GetError());
                    success = FALSE;
                }
            }
        }
    }
    return success;
}

void quitSDL(){
    killRenderer(appRenderer);
    killWindow(appWindow);

    IMG_Quit();
    SDL_Quit();
}
