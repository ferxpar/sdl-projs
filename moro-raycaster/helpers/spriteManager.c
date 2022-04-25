#include "spriteManager.h"


void initSpriteManager(){
	currentSpriteId = 0;

	int texWidth;
	int texHeight;

	SDL_QueryTexture(textureSheet, NULL, NULL, &texWidth, &texHeight);

	int loopSize = texWidth / TILE_SIZE;

	for(int y = 0; y < loopSize; y++){
		for(int x = 0; x < loopSize; x++){
			addSprite(TILE_SIZE, TILE_SIZE * x, TILE_SIZE * y);
		}
	}
}

//Sprite array
void addSprite(int size, int xTexPos, int yTexPos){
	Sprite spr;
	spr.id = currentSpriteId;
	currentSpriteId++;

	spr.size = size;
	spr.xTex = xTexPos;
	spr.yTex = yTexPos;

	spriteList[spr.id] = spr;
}

int getSpriteSize(int spriteId){
	return spriteList[spriteId].size;
}

//Alpha mod
void setTextureAlphaMod(Uint8 alpha){
	SDL_SetTextureAlphaMod(textureSheet, alpha);
}

void clearTextureAlphaMod(){
	SDL_SetTextureAlphaMod(textureSheet, 255);
}
//Color mod
void setTextureColorMod(Uint8 red, Uint8 green, Uint8 blue){
    SDL_SetTextureColorMod(textureSheet, red, green, blue);
}

void clearTextureColorMod(){
    SDL_SetTextureColorMod(textureSheet, 255, 255, 255);
}
//Drawing
void drawSprite(SDL_Renderer *renderRef, int spriteId, int xScreen, int yScreen, int wScreen, int hScreen){
	SDL_Rect posInScreen = {xScreen, yScreen, wScreen, hScreen};

	SDL_Rect texQuad = {spriteList[spriteId].xTex, spriteList[spriteId].yTex, getSpriteSize(spriteId), getSpriteSize(spriteId)};

	SDL_RenderCopy(renderRef, textureSheet, &texQuad, &posInScreen);
}

void drawSpriteQuad(SDL_Renderer *renderRef, int spriteId, int xScreen, int yScreen, int wScreen, int hScreen, int xTex, int yTex, int wTex, int hTex){
	SDL_Rect posInScreen = {xScreen, yScreen, wScreen, hScreen};


	SDL_Rect texQuad = {spriteList[spriteId].xTex + xTex, spriteList[spriteId].yTex + yTex, wTex, hTex};

	SDL_RenderCopy(renderRef, textureSheet, &texQuad, &posInScreen);
}

void drawSomethingExt(SDL_Renderer *renderRef, int xScreen, int yScreen, int wScreen, int hScreen, int xTex, int yTex, int wTex, int hTex){
	SDL_Rect posInScreen = {xScreen, yScreen, wScreen, hScreen};
	SDL_Rect texQuad = {xTex, yTex, wTex, hTex};

	SDL_RenderCopy(renderRef, textureSheet, &texQuad, &posInScreen);
}
