#ifndef globalVars
#define globalVars

//Window vars
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define SCALE 4

//App surface (projection plane vars)
#define APP_SURFACE_WIDTH  WINDOW_WIDTH/SCALE
#define APP_SURFACE_HEIGHT  WINDOW_HEIGHT/SCALE

//World propieties
#define TILE_SIZE 16 //WORLD GRID SIZE, FOR WALKING, RAYCASTING COORDINATES
#define WALL_WIDTH 16 //WALL PROPS FOR SIZE RELATIVE TO GRID AND FOR TEXTURES
#define WALL_HEIGHT WALL_WIDTH/2

//Player propieties
#define PLAYER_FOV M_PI/3
#define PLAYER_HEIGHT TILE_HEIGHT/2

#endif
