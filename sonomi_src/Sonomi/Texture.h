#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Globals.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool loadFromPath(std::string path);
	void free();
	void render(int x, int y, int clip = -1, bool flip = false);

	int getWidth();
	int getHeight();

private:
	void init_quads();

	int _width;
	int _height;
	SDL_Texture* _tex;
	std::vector<SDL_Rect*> _quads;
};

#endif // !_TEXTURE_H_
