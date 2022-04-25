/*
 * spriteManager.h
 *
 *  Created on: Jul 23, 2019
 *      Author: fernando
 */

#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include <SDL2/SDL.h>
#include "globalVars.h"

extern SDL_Texture *textureSheet;

//Sprite obj
#define spriteInitialCap 100
int currentSpriteId;

typedef struct SpriteProps{
	int id;
	int size;
	int xTex;
	int yTex;
} Sprite;

Sprite spriteList[spriteInitialCap];

//Init
void initSpriteManager();
//Sprites
void addSprite(int size, int xTexPos, int yTexPos);
int getSpriteSize(int id);
//Alpha
void setTextureAlphaMod(Uint8 alpha);
void clearTextureAlphaMod();
//Colors
void setTextureColorMod(Uint8 red, Uint8 green, Uint8 blue);
void clearTextureColorMod();
//Drawing
void drawSprite(SDL_Renderer *renderRef, int spriteId, int xScreen, int yScreen, int wScreen, int hScreen);
void drawSpriteQuad(SDL_Renderer *renderRef, int spriteId, int xScreen, int yScreen, int wScreen, int hScreen, int xTex, int yTex, int wTex, int hTex);
void drawSomethingExt(SDL_Renderer *renderRef, int xScreen, int yScreen, int wScreen, int hScreen, int xTex, int yTex, int wTex, int hTex);

#endif /* SPRITEMANAGER_H_ */
