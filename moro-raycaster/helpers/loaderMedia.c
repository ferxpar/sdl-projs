#include "loaderMedia.h"

SDL_Texture *loadMedia(SDL_Renderer *renderRef, char *resPath){
	int success = TRUE;

	SDL_Surface *tempSurface = NULL;
	SDL_Texture *loadedTexture = NULL;

	tempSurface = IMG_Load(resPath);
	if(!tempSurface){
		printf("Couldn't load media on surface! Error: %s", IMG_GetError());
		success = FALSE;
	} else {
		loadedTexture = SDL_CreateTextureFromSurface(renderRef, tempSurface);

		if(!loadedTexture){
			printf("Couldn't create texture from surface! Error: %s", SDL_GetError());
			success = FALSE;

			SDL_DestroyTexture(loadedTexture);
			loadedTexture = NULL;
		}
	}

	SDL_FreeSurface(tempSurface);
	tempSurface = NULL;

	if(success){
		return loadedTexture;
	} else {
		return NULL;
	}
}

void freeTexture(SDL_Texture *textureToKill){
	SDL_DestroyTexture(textureToKill);
	textureToKill = NULL;
}
