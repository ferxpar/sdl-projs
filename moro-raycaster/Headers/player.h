#ifndef playerh
#define playerh

#include <SDL2/SDL.h>
#include <math.h>

#include "globalVars.h"
#include "dynamicArray.h"

#include "levelData.h"
#include "object.h"
#include "raycast.h"

typedef struct{
    float x, y;
    float velx, vely;
    float angle, fov, rotSpeed, rotVel;
    float moveSpeed;
    float space;
} Player;

Player player;

SDL_Rect collisionZone;
DynamicArray nearObjects;

void initPlayer(float posx, float posy);

void playerUpdate();
void playerInput(SDL_Event eventRef);
void playerSearchNearObjects();
void playerCollision();

void playerRender(SDL_Renderer *renderer);

#endif
