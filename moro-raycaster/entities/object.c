/*
 * object.c
 *
 *  Created on: Jul 28, 2019
 *      Author: fernando
 */

#include "object.h"

static int currentObjectId = 0;

StaticObject initStaticObject(float xpos, float ypos, int spriteId, int solid){
	StaticObject tempObj;

	tempObj.id = currentObjectId;
	currentObjectId++;

	tempObj.xpos = xpos;
	tempObj.ypos = ypos;
	tempObj.spriteId = spriteId;
	tempObj.solid = solid;

	tempObj.space = 8;
	tempObj.active = FALSE;

	return tempObj;
}

void addObjectToList(StaticObject object){
	objectList[object.id] = object;
}

void getObjectsInRectangle(DynamicArray array, int x1, int y1, int x2, int y2){
	for(int i = 0; i < currentObjectId; i++){
		StaticObject tempObj = objectList[i];
		int objX = (int)tempObj.xpos;
		int objY = (int)tempObj.ypos;
		int objSize = tempObj.space;

		//printf("objX = %d  >  x1 = %d   and   objX+size = %d  <  x2 = %d\n", objX, x1, objX + objSize, x2);


		if(objX > x1 && objY > y1 && objX + objSize < x2 && objY + objSize < y2){
			printf("called\n");


			if(!tempObj.active){
				dynamicArray_append(&array, tempObj.id);
				tempObj.active = TRUE;
				printf("added to dyn array\n");
			}
		}
	}
}

void objectUpdate(){

}

void objectRender(SDL_Renderer *renderRef, float playerX, float playerY, float angle){
	int tileSize = TILE_SIZE;
	int gridX, gridY;

	for(int i = 0; i < currentObjectId; i++){
		gridX = objectList[i].xpos / tileSize;
		gridY = objectList[i].ypos / tileSize;

		if(getVisibilityData(gridY, gridX) == TILE_IS_VISIBLE){
			StaticObject objRef = objectList[i];
			float midX = objRef.xpos + getSpriteSize(objRef.spriteId)/2;
			float midY = objRef.ypos + getSpriteSize(objRef.spriteId)/2;

			renderSprite(renderRef,	objRef.spriteId, midX, midY, playerX, playerY, angle);
		}
	}
}
