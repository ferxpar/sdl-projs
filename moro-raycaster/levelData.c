/*
 * levelData.c
 *
 *  Created on: Jul 24, 2019
 *      Author: fernando
 */

#include "levelData.h"

void initLevelData(){
	int tempLevelMap[LEVEL_WIDTH][LEVEL_HEIGHT] =
	{
		{1,1,1,1,1,1,1,1,1},
		{1,0,0,0,1,0,1,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,2,0,1},
		{1,0,0,0,0,0,3,0,1},
		{1,0,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1}
	};

	for(int x = 0; x < 9; x++){	//TODO: Variable Level sizes
		for(int y = 0; y < 9; y++){
			levelMap[y][x] = tempLevelMap[y][x];
			levelVisibilityMap[x][y] = TILE_NOT_VISIBLE;
		}
	}
}

int getLevelSolidData(int xpos, int ypos){
	return levelMap[xpos][ypos];
}

//We if tile is visible or not
int getVisibilityData(int xpos, int ypos){
	return levelVisibilityMap[xpos][ypos];
}

void setVisibilityData(int xpos, int ypos, int direction){
	//int currentTile = levelVisibilityMap[xpos][ypos];

	/*if(currentTile == TILE_NOT_VISIBLE){
		levelVisibilityMap[xpos][ypos] = direction;
	} else if(currentTile != TILE_IS_VISIBLE && currentTile != direction){
		levelVisibilityMap[xpos][ypos] = TILE_IS_VISIBLE;
	}*/
	levelVisibilityMap[xpos][ypos] = TILE_IS_VISIBLE;
}

void resetVisibilityData(){
	for(int y = 0; y < LEVEL_HEIGHT; y++){
		for(int x = 0; x < LEVEL_WIDTH; x++){
			levelVisibilityMap[y][x] = TILE_NOT_VISIBLE;
		}
	}
}
