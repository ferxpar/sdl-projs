/*
 * levelData.h
 *
 *  Created on: Jul 24, 2019
 *      Author: fernando
 */

#ifndef LEVELDATA_H_
#define LEVELDATA_H_

#include "defBoolean.h"

#define LEVEL_WIDTH 9
#define LEVEL_HEIGHT 9

int levelMap[LEVEL_WIDTH][LEVEL_HEIGHT];
int levelVisibilityMap[LEVEL_WIDTH][LEVEL_HEIGHT];

enum tileVisibility{
	TILE_NOT_VISIBLE = 0,
	TILE_IS_VISIBLE_BY_RAY_HORIZONTAL = 1,
	TILE_IS_VISIBLE_BY_RAY_VERTICAL = 2,
	TILE_IS_VISIBLE = 3
};

void initLevelData();
int getLevelSolidData(int xpos, int ypos);

int getVisibilityData(int xpos, int ypos);
void setVisibilityData(int xpos, int ypos, int direction);
void resetVisibilityData();

#endif /* LEVELDATA_H_ */
