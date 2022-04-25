#include "player.h"

int areaOfCollision = TILE_SIZE*2;

void initPlayer(float posx, float posy){
	int tileSize = TILE_SIZE;
	//position
    player.x = posx;
    player.y = posy;
    player.space = tileSize;
    //angle
    player.angle = -0.001f;
    player.fov = PLAYER_FOV;
    player.rotSpeed = 0.02f;
    player.rotVel = 0;
    //movement
    player.moveSpeed = 0.4f;
    player.velx = 0;
    player.vely = 0;
    //

    int playerCenterX = floor(player.x) + player.space/2;
    int playerCenterY = floor(player.y) + player.space/2;

    collisionZone.x = playerCenterX - areaOfCollision/2;
    collisionZone.y = playerCenterY - areaOfCollision/2;
    collisionZone.w = areaOfCollision;
    collisionZone.h = areaOfCollision;

    dynamicArray_init(&nearObjects);
}

void playerInput(SDL_Event eventRef){

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    //Movement
    if(state[SDL_SCANCODE_W]){
        player.velx = cos(player.angle) * player.moveSpeed;
        player.vely = -sin(player.angle) * player.moveSpeed;
    } else if(state[SDL_SCANCODE_S]){
        player.velx = -cos(player.angle) * player.moveSpeed;
        player.vely = sin(player.angle) * player.moveSpeed;
    } else {
        player.velx = 0;
        player.vely = 0;
    }
    //Rotations
    if(state[SDL_SCANCODE_A]){
        player.rotVel = player.rotSpeed;
    } else if(state[SDL_SCANCODE_D]){
        player.rotVel = -player.rotSpeed;
    } else {
        player.rotVel = 0;
    }
}

void playerSearchNearObjects(){
	getObjectsInRectangle(nearObjects, collisionZone.x, collisionZone.y, collisionZone.x + collisionZone.w, collisionZone.y + collisionZone.h);
}

void playerCollision(){
	int tileSize = TILE_SIZE;

    float middleX = player.x+player.space/2;
    float middleY = player.y+player.space/2;

    int mapX = (int)floor(middleX/tileSize);
    int mapY = (int)floor(middleY/tileSize);

    int nextPosX = (int)floor((middleX+player.velx*2))/tileSize;
    int nextPosY = (int)floor((middleY+player.vely*2))/tileSize;

    //Coll X
    if(getLevelSolidData(mapY,nextPosX) > 0){
        player.velx = 0;
    }

    //Coll Y
    if(getLevelSolidData(nextPosY,mapX) > 0){
        player.vely = 0;
    }

}

void playerUpdate(){
    //Cap angle at 2pi
    if(player.angle < 0){
        player.angle += 2*M_PI;
    } else if(player.angle > 2*M_PI){
        player.angle -= 2*M_PI;
    }

    playerSearchNearObjects();

    playerCollision();
    //Add velocity
    player.x += player.velx;
    player.y += player.vely;
    //Coll zone
    collisionZone.x = player.x - player.space/2 - areaOfCollision/2;
    collisionZone.y = player.y - player.space/2 - areaOfCollision/2;
    //printf("x = %d, y = %d, w = %d, h = %d \n", collisionZone.x, collisionZone.y, collisionZone.w, collisionZone.h);

    //Add vel to angle
    player.angle += player.rotVel;
}

void playerRender(SDL_Renderer *renderer){
    float midX = player.x+player.space/2;
    float midY = player.y+player.space/2;

    //Render raycast
    //renderFloor(renderer, midX, midY, player.angle);

    runRaycast(renderer, player.fov, player.angle, midX, midY);

    //SPRITE RENDER
    objectRender(renderer, midX, midY, player.angle);
    //Render weapon

}
