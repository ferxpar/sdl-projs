#include "window.h"

//We pass width and height and receive a initialized windowPointer
SDL_Window * initWindow(int width, int height){
    SDL_Window *windowRef = NULL;

    int windowPos = SDL_WINDOWPOS_CENTERED;
    int windowFlags = SDL_WINDOW_SHOWN;

    windowRef = SDL_CreateWindow("Window title", windowPos, windowPos, width, height, windowFlags);

    if(windowRef == NULL){ //Couldnt init window
        printf("%s %s","Couldn't init window, error: ", SDL_GetError());
        return NULL;
    }

    return windowRef;
}

//We pass the address of a window and receive the address of a renderer
SDL_Renderer * initRenderer(SDL_Window *windowRef){
    SDL_Renderer *rendererRef = NULL;

    int renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    rendererRef = SDL_CreateRenderer(windowRef, 0, renderFlags);

    if(rendererRef == NULL){ //Couldnt init renderer
        printf("%s %s","Couldn't init renderer, error: ", SDL_GetError());
        return NULL;
    }

    return rendererRef;
}

//Destroy a window and assign window pointer to NULL
void killWindow(SDL_Window *windowRef){
    SDL_DestroyWindow(windowRef);
    windowRef = NULL;
}

//Destroy a renderer and assign renderer pointer to NULL
void killRenderer(SDL_Renderer *renderRef){
    SDL_DestroyRenderer(renderRef);
    renderRef = NULL;
}
