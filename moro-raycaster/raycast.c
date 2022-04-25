#include "raycast.h"

void initRaycast(int rayAmountRef, float fov){
    rayAmount = rayAmountRef;
    wallStripSize = floor(APP_SURFACE_WIDTH / rayAmount);
    angleBetweenRays = fov / rayAmount;
    distanceToProjPlane = floor((APP_SURFACE_WIDTH / 2) / tan(fov/2));
}

void runRaycast(SDL_Renderer *renderRef, float fov, float angle, float x, float y){
	renderFloor(renderRef, 0, 0, 0);
	//Globals Reference
	int tileSize = TILE_SIZE;
    int textureSize = WALL_WIDTH;
    int levelSize = 9-1;	//TODO Level get size! Avoid out of bounds in array

    //position vars
    float posX = x;
    float posY = y;
    float tiledPosX = posX / tileSize;
    float tiledPosY = posY / tileSize;
    int gridX = floor(tiledPosX);
    int gridY = floor(tiledPosY);

    //Angle vars
	float currentAngle =  0;
    float betaAngle = 0;	//Angle relative to fov
    float currentDistance = 0;

    //direction vector
    float dirX = 0;
    float dirY = 0;

    //ray vars
    int stepX, stepY;
    float distToClosestX, smallTriangleY;
    float distToClosestY, smallTriangleX;

    int checkX, checkY;
    float gridMoveOnYEveryX, gridMoveOnXEveryY;
    float distToVertical, distToHorizontal;

    //Wall draw vars
    int side;
    int texCol;
    int wallId = 0;

    int visibilityDirection;

    for(int column = 0; column < rayAmount; column++){
        //angle vars
    	currentAngle =  angle + (angleBetweenRays*column - fov/2);
        betaAngle = currentAngle - angle;	//Angle relative to fov
        currentDistance = 0;

        //direction vector
        dirX = cos(currentAngle);
        dirY = -sin(currentAngle);

        //Intersections in X (verticals)    --> |
        visibilityDirection = TILE_IS_VISIBLE_BY_RAY_HORIZONTAL;
        if(dirX < 0){ //Looking left
            stepX = -1;
            distToClosestX = gridX - tiledPosX;
        } else {
            stepX = 1;
            distToClosestX = (gridX + 1) - tiledPosX;
        }

        if(currentAngle == M_PI/2 || currentAngle == 3*M_PI/2){ //if angle goes up or down we never hit a vertical axis
        	visibilityDirection = TILE_IS_VISIBLE;
        	smallTriangleY = 0;
        	gridMoveOnYEveryX = 0;
        } else if(currentAngle == 0 || currentAngle == M_PI){ //If angle goes left or right we avoid x by 0
            smallTriangleY = distToClosestX;
            gridMoveOnYEveryX =  stepX;
        } else {
            smallTriangleY = distToClosestX * -tan(currentAngle);
            gridMoveOnYEveryX =  stepX * -tan(currentAngle); // Move in Y for every xGrid (= 1),  --> (1*lado) * -tan(angle)
        }

        //Check in map vars
        checkX = floor(tiledPosX + distToClosestX) + (-1 + stepX)/2; //If looking left, we add -1 to grid
        checkX = clamp(checkX, 0, levelSize);
        checkY = floor(tiledPosY + smallTriangleY);
        checkY = clamp(checkY, 0, levelSize);

        while(getLevelSolidData(checkY,checkX) == 0){
        	setVisibilityData(checkY, checkX, visibilityDirection);

            distToClosestX += stepX;
            smallTriangleY += gridMoveOnYEveryX;

            checkX = floor(tiledPosX + distToClosestX) + (-1 + stepX)/2; //If looking left, we add -1 to grid
            checkX = clamp(checkX, 0, levelSize);
            checkY = floor(tiledPosY + smallTriangleY);
            checkY = clamp(checkY, 0, levelSize);
        }

        wallId = getLevelSolidData(checkY,checkX);

        //Distance to vertical line / ray intersection
        distToVertical = sqrt(distToClosestX * distToClosestX + smallTriangleY * smallTriangleY);

        //Intersections in Y (horizontal)    --> ____
        visibilityDirection = TILE_IS_VISIBLE_BY_RAY_VERTICAL;
        if(dirY < 0){ //Looking up
            stepY = -1;
            distToClosestY = gridY - tiledPosY;
        } else {
            stepY = 1;
            distToClosestY = (gridY + 1) - tiledPosY;
        }

        if(currentAngle == 0 || currentAngle == M_PI){ //if angle=0 or pi, tan = 0. Plus we never hit a horizontal line
        	visibilityDirection = TILE_IS_VISIBLE;
            smallTriangleX = 0;
            gridMoveOnXEveryY = 0;
        } else {
            smallTriangleX = distToClosestY / -tan(currentAngle);
            gridMoveOnXEveryY = stepY / -tan(currentAngle); //Movement in X every 1 in gridY
        }

        checkY = floor(tiledPosY + distToClosestY) + (-1 + stepY)/2;
        checkY = clamp(checkY, 0, levelSize);
        checkX = floor(tiledPosX + smallTriangleX);
        checkX = clamp(checkX, 0, levelSize);

        while(getLevelSolidData(checkY,checkX) == 0){
        	setVisibilityData(checkY, checkX, visibilityDirection);

            distToClosestY += stepY;
            smallTriangleX += gridMoveOnXEveryY;

            checkY = floor(tiledPosY + distToClosestY) + (-1 + stepY)/2;
            checkY = clamp(checkY, 0, levelSize);
            checkX = floor(tiledPosX + smallTriangleX);
            checkX = clamp(checkX, 0, levelSize);
        }

        distToHorizontal = sqrt(distToClosestY * distToClosestY + smallTriangleX * smallTriangleX); //TODO: ABS EN VEZ DE PITAGORAS

        if(distToVertical < distToHorizontal){ //TODO: TEXTURE SIZE EN VEZ DE TILESIZE
            currentDistance = distToVertical;
            side = WALL_HIT_HORIZONTAL_SIDE;
            texCol = floor(  fmod(   (   (tiledPosY + smallTriangleY) * textureSize), textureSize));
        } else {
            currentDistance = distToHorizontal;
            side = WALL_HIT_VERTICAL_SIDE;
            texCol = floor(  fmod(	 (	 (tiledPosX + smallTriangleX) * textureSize), textureSize));
            wallId = getLevelSolidData(checkY,checkX);
        }

        currentDistance *= tileSize; //Re scale
        currentDistance *= cos(betaAngle); //Fish eye correction

        zBuffer[column] = currentDistance;

        //Render walls, return the point on the bottom of the wall (on the projection plane)
        renderWall(renderRef, (rayAmount - 1) - column, currentDistance, texCol, wallId);
    }
    //After ray casting clean the color distortion
    clearTextureColorMod();

}

void renderWall(SDL_Renderer *renderRef, int xColOnScreen, float rayDistance, int texCol, int wallId){

	int wallH = WALL_HEIGHT; //Global world define
    int columnHeight = floor(wallH / rayDistance * distanceToProjPlane);

    //Light vars
    SDL_Color paintColor = {255,255,255,255};
    int objectIntensity = 1;
    float multiplier = 10;
    float lightIntensity = objectIntensity / rayDistance * multiplier;
    lightIntensity = fclamp(lightIntensity, 0, 1);

    setTextureColorMod(paintColor.r * lightIntensity, paintColor.b * lightIntensity, paintColor.g * lightIntensity);

    //Texture quad
    SDL_Rect quad = {texCol, 0, 1, 16};

    //Screen positions
    SDL_Rect column;
    column.x = xColOnScreen;
    column.y = (APP_SURFACE_HEIGHT/2) - columnHeight/2;
    column.w = wallStripSize;
    column.h = columnHeight;

    drawSpriteQuad(renderRef, wallId-1, column.x, column.y, column.w, column.h, quad.x, quad.y, quad.w, quad.h);
}

SDL_Rect techo = {0,0, APP_SURFACE_WIDTH, APP_SURFACE_HEIGHT/2};
SDL_Rect piso = {0,APP_SURFACE_HEIGHT/2, APP_SURFACE_WIDTH, APP_SURFACE_HEIGHT/2};

void renderFloor(SDL_Renderer *renderRef, float xpos, float ypos, float currentAngle){

	SDL_SetRenderDrawColor(renderRef, 100, 200, 200, 1);
    SDL_RenderFillRect(renderRef, &techo);
	SDL_SetRenderDrawColor(renderRef, 100, 200, 100, 1);
    SDL_RenderFillRect(renderRef, &piso);

	/*
	int width = APP_SURFACE_WIDTH;
	int widthHalf = width/2;

	int height = APP_SURFACE_HEIGHT;
	int heightHalf = height/2; //Middle of screen

	int xOff = (int)xpos;
	int yOff = (int)ypos;

	float cosAngle = cos(currentAngle);
	float sinAngle = -sin(currentAngle);

	for(int y = 1; y < heightHalf; y++){ //Proj plane mid to bot
		int z = y;

		for(int x = -widthHalf; x < widthHalf; x++){ //Proj plane x

			float projX = (x * cosAngle + height * sinAngle) / z;
			float projY = (x * sinAngle - height * cosAngle) / z;

			projX += widthHalf;
			projY += heightHalf;

			int texX = floor(projX) + yOff;
			int texY = floor(projY) - xOff;

			texY = abs(texY);

			texX %= 8; //TODO! Texture sizes!
			texY %= 8;

			drawSomethingExt(renderRef, x + widthHalf, y + heightHalf, 1, 1, texX, texY, 1, 1);

		}
	}*/
}

void renderSprite(SDL_Renderer *renderRef, int objSprId, float objX, float objY, float playerX, float playerY, float angle){

	float dx = objX-playerX;
	float dy = objY-playerY;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);

	//Rotate the world around the player instead of the player view
	float xPos = dx * cosAngle - dy * sinAngle;
	float yPos = dx * sinAngle + dy * cosAngle;

	//We use distance from 0 since we translated to origin to rotate relative to the player
	float newDx = xPos;
	float newDy = yPos;
	float distance = sqrt(newDx * newDx + newDy * newDy);

	if(newDx < 1){
		return;
	}

	//Screen pos x
	int renderX = floor((newDy/newDx) * distanceToProjPlane);//Where to render x relative to screen
	renderX += APP_SURFACE_WIDTH/2;

	//Screen width
	int spriteSize = getSpriteSize(objSprId);
	//renderX = clamp(renderX, -spriteSize, APP_SURFACE_WIDTH-1 + spriteSize);

	float spriteWidth;
	if(distance > distanceToProjPlane){
		spriteWidth = spriteSize;//TODO We can make this smaller...
	} else {
		spriteWidth = floor(spriteSize / distance * distanceToProjPlane);
	}

	//Render y and height vars
	int spriteHeight = WALL_HEIGHT;
	int colHeight = floor(spriteHeight / distance * distanceToProjPlane);

	int yScreenPos = -colHeight/2 + APP_SURFACE_HEIGHT/2;

    //Light vars
    SDL_Color paintColor = {255,255,255,255};
    int objectIntensity = 1;
    float multiplier = 10;
    float lightIntensity = objectIntensity / distance * multiplier;
    lightIntensity = fclamp(lightIntensity, 0, 1);

    setTextureColorMod(paintColor.r * lightIntensity, paintColor.b * lightIntensity, paintColor.g * lightIntensity);

    //Draw vars
    int currentScreenX = 0;
    int currentRow = 0;
    float xTex = 0;

	//Draw
	for(int x = -spriteWidth/2; x < spriteWidth/2; x++){
		currentScreenX = floor(renderX + x);
		currentRow = (APP_SURFACE_WIDTH - 1) - currentScreenX;

		if(distance < zBuffer[currentRow]){

			xTex = (x + spriteWidth/2) / spriteWidth; //Normalize
			xTex *= spriteSize;
			xTex = floor(xTex);

			drawSpriteQuad(renderRef, objSprId, currentScreenX, yScreenPos, 1, colHeight, xTex, 0, 1, 16);
		}

	}
	clearTextureColorMod();
}

int clamp(int value, int minval, int maxval){
    if(value < minval){
        value = minval;
    } else if(value > maxval){
        value = maxval;
    }
    return value;
}

float fclamp(float value, float minval, float maxval){
    if(value < minval){
        value = minval;
    } else if(value > maxval){
        value = maxval;
    }
    return value;
}
