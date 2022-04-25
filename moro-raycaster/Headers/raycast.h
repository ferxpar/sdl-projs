#ifndef raycasth
#define raycasth

#include <SDL2/SDL.h>
#include <math.h>

#include "globalVars.h"
#include "defBoolean.h"

#include "spriteManager.h"
#include "levelData.h"
#include "player.h"

float angleBetweenRays;
int rayAmount;
int wallStripSize;
int distanceToProjPlane;

enum wallSideHit {
    WALL_HIT_HORIZONTAL_SIDE = 0,
    WALL_HIT_VERTICAL_SIDE = 1
};

float zBuffer[APP_SURFACE_WIDTH];

//Logic
void initRaycast(int rayAmount, float fov);
void runRaycast(SDL_Renderer *renderRef, float fov, float angle, float x, float y);

//Draw
void renderWall(SDL_Renderer *renderRef, int xColOnScreen, float rayDistance, int texCol, int wallId);
void renderFloor(SDL_Renderer *renderRef, float x, float y, float currentAngle);
void renderSprite(SDL_Renderer *renderRef, int objSprId, float objX, float objY, float playerX, float playerY, float playerAngle);

//helpers
int clamp(int value, int minval, int maxval);
float fclamp(float value, float minval, float maxval);

#endif
