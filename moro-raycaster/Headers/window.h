#ifndef _windowh
#define _windowh

#include "defBoolean.h"
#include <SDL2/SDL.h>

//Window init and kill
SDL_Window * initWindow(int width, int height);
void killWindow(SDL_Window *windowRef);

//Render init and kill
SDL_Renderer * initRenderer(SDL_Window *windowRef);
void killRenderer(SDL_Renderer *renderRef);

#endif
