#pragma once

#include "Globals.h"
#include "Texture.h"

class Player
{
public:
	Player(int x, int y, int *frames, int cantFrames, Texture *spritesheet);
	~Player();

	void move(int hor, int ver);
	void update();
	void render();

private:
	int _x;
	int _y;

	int _dx = 0;
	int _dy = 0;
	int _spd = 3;

	int *_frames;
	int _cantFrames;

	int _tick;
	int _anim = 0;
	int _animSpd = 10;
	bool _flip = false;

	Texture* _spritesheet;

};

