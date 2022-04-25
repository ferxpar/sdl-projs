#include "Player.h"

Player::Player(int x, int y, int *frames, int cantFrames, Texture *spritesheet) {
	_x = x;
	_y = y;
	_frames = frames;
	_cantFrames = cantFrames;

	_tick = 0;

	_spritesheet = spritesheet;
}

Player::~Player() {

}

void Player::move(int hor, int ver) {
	_dx = hor * _spd;
	_dy = ver * _spd;

	if (hor < 0) {
		_flip = true;
	} else {
		_flip = false;
	}
}

void Player::update() {
	_tick++;
	_tick %= 60;
	if (_tick == 0) {
		_anim++;
		_anim %= _cantFrames;
	}

	_x += _dx;
	_y += _dy;
	_dx = 0;
	_dy = 0;

}

void Player::render() {
	_spritesheet->render(_x,_y,_frames[_anim], _flip);

}