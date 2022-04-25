#pragma once
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

extern SDL_Window* WINDOW;
extern SDL_Renderer* RENDERER;

const int WIDTH = 256;
const int HEIGHT = 192;
const int SCALE = 3;
const std::string NAME = "Sonori Zombies";

const int SPRITE_SIZE = 16;

#endif