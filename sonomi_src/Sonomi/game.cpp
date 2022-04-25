
#include "Globals.h"
#include "Texture.h"
#include "Player.h"

SDL_Window* WINDOW = NULL;
SDL_Renderer* RENDERER = NULL;

Texture spritesheet;
int sprites[4] = { 0, 1, 2, 3 };
Player player = Player(10, 10, sprites, 4, &spritesheet);
bool running = true;

bool init_sdl() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		success = false;
		printf("Error en SDL_Init: %s\n", SDL_GetError());
	} else {
		WINDOW = SDL_CreateWindow(NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH*SCALE, HEIGHT*SCALE, SDL_WINDOW_SHOWN);

		if (WINDOW == NULL) {
			success = false;
			printf("Error creando SDL_Window: %s\n", SDL_GetError());
		} else {
			RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (RENDERER == NULL) {
				success = false;
				printf("Error creando SDL_Renderer: %s\n", SDL_GetError());
			} else {
				SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)){
					printf("Error creando SDL_image: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

void quit_sdl() {
	spritesheet.free();

	SDL_DestroyRenderer(RENDERER);
	RENDERER = NULL;
	SDL_DestroyWindow(WINDOW);
	WINDOW = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool load_media() {
	bool success = true;
	
	if (!spritesheet.loadFromPath("art/spritesheet.png")) {
		success = false;
	}

	return success;
}

void update() {
	player.update();
}

void render() {
	//spritesheet.render(10,10, 0);
	player.render();
}

int main(int argc, char* argv[]) {

	if (!init_sdl()) {
		printf("No se pudo inicializar SDL.\n");
	} else {
		if (!load_media()) {
			printf("No se pudieron leer los recursos.\n");
		} else {
			SDL_Event e;

			while (running) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						running = false;
					} else if (e.type == SDL_KEYDOWN) {

						switch (e.key.keysym.sym) {
						case SDLK_w:
							player.move(0, -1);
							break;

						case SDLK_s:
							player.move(0, 1);
							break;

						case SDLK_a:
							player.move(-1, 0);
							break;
						case SDLK_d:
							player.move(1, 0);
							break;

						}
					}
				}

				update();

				SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(RENDERER);
				render();
				SDL_RenderPresent(RENDERER);
			}
		}
	}
	quit_sdl();
	return 0;
}