/*
 * object.h
 *
 *  Created on: Jul 28, 2019
 *      Author: fernando
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <SDL2/SDL.h>

#include "dynamicArray.h"
#include "spriteManager.h"
#include "defBoolean.h"

#include "levelData.h"
#include "raycast.h"

#define MAX_OBJECTS 255

typedef struct{
	int id;
	float xpos, ypos;
	int solid;
	int spriteId;
	int space;
	int active;
} StaticObject;

StaticObject objectList[MAX_OBJECTS];

StaticObject initStaticObject(float xpos, float ypos, int spriteId, int solid);
void addObjectToList(StaticObject object);

void getObjectsInRectangle(DynamicArray array, int x1, int y1, int x2, int y2);

void objectUpdate();
void objectRender(SDL_Renderer *renderRef, float playerX, float playerY, float angle);

#endif /* OBJECT_H_ */
