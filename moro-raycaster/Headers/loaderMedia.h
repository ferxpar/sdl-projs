/*
 * loaderMedia.h
 *
 *  Created on: Jul 21, 2019
 *      Author: fernando
 */

#ifndef LOADERMEDIA_H_
#define LOADERMEDIA_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defBoolean.h"

SDL_Texture *loadMedia(SDL_Renderer *renderRef, char *resPath);
void freeTexture(SDL_Texture *textureToKill);

#endif /* LOADERMEDIA_H_ */
