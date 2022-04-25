#include "Texture.h"

Texture::Texture() {
	_width = 0;
	_height = 0;
	_tex = nullptr;
}

Texture::~Texture() {
	free();
}

bool Texture::loadFromPath(std::string path){
	bool success = true;

	this->free();

	SDL_Texture* new_texture = NULL;
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());

	if (loaded_surface == NULL) {
		printf("Error cargando media de %s \n Error: %s\n", path.c_str(), IMG_GetError());
		success = false;
	} else {
		SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0xFF, 0x00, 0xFF));
		new_texture = SDL_CreateTextureFromSurface(RENDERER, loaded_surface);
		if (new_texture == NULL) {
			printf("Error creando textura de %s \n Error: %s\n", path.c_str(), SDL_GetError());
			success = false;
		} else {
			_width = loaded_surface->w;
			_height = loaded_surface->h;

			init_quads();
		}
		SDL_FreeSurface(loaded_surface);
		_tex = new_texture;
		success = success && (_tex != NULL);
	}
	return success;
}

void Texture::init_quads() {

	int cant_quads_w = _width / SPRITE_SIZE;
	int cant_quads_h = _height / SPRITE_SIZE;
	int total = cant_quads_w * cant_quads_h;

	for (int y = 0; y < cant_quads_h; y++) {
		for (int x = 0; x < cant_quads_w; x++) {
			SDL_Rect* quad = new SDL_Rect;
			quad->x = x * SPRITE_SIZE;
			quad->y = y * SPRITE_SIZE;
			quad->w = SPRITE_SIZE;
			quad->h = SPRITE_SIZE;
			_quads.push_back(quad);
		}
	}

}

void Texture::free() {
	if (_tex != nullptr) {
		SDL_DestroyTexture(_tex);
		_tex = nullptr;
	}
	
	for (unsigned int i = 0; i < _quads.size(); i++) {
		delete _quads[i];
	}

	for (unsigned int i = 0; i < _quads.size(); i++) {
		_quads.pop_back();
	}

	_quads.clear();

	_width = 0;
	_height = 0;
}

void Texture::render(int x, int y, int clip, bool flip) {
	SDL_Rect pos = {x, y, _width * SCALE, _height * SCALE};
	SDL_Rect *quad = NULL;
	if (clip != -1) {
		quad = _quads[clip];
		pos.w = quad->w * SCALE;
		pos.h = quad->h * SCALE;
	}

	SDL_RendererFlip flipped = SDL_FLIP_NONE;;
	if (flip) {
		flipped = SDL_FLIP_HORIZONTAL;
	}

	SDL_RenderCopyEx(RENDERER, _tex, quad, &pos, 0, NULL, flipped);
}

int Texture::getWidth() {
	return _width;
}


int Texture::getHeight() {
	return _height;
}