#ifndef BATTLE_H
#define BATTLE_H

#include "SurfaceHandler.h"
#include "Tile.h"
#include "Map.h"
#include "Player.h"

class Battle
{
    public:
        Battle(Tile areaTiles[12], Tile areaBg[12], Player plr);
        ~Battle();

        void inputBattle(SDL_Event &e);

        void updateBattle();

        void renderMap(Screen *screen);
        void renderMobs(SurfaceHandler *surf, Screen *screen);

        bool collision(SDL_Rect rect1, SDL_Rect rect2);
        void debug(Screen *screen);

        void incrementDistance();
        //Pre: newDist > 0


    private:
        Map _map;
        Player _player;

        SDL_Rect _goBackwards = {PLAY_AREA.x, PLAY_AREA.y, PLAY_AREA.x + TILE_SIZE, PLAY_AREA.h};
        SDL_Rect _goFoward = {PLAY_AREA.w - TILE_SIZE, PLAY_AREA.y, PLAY_AREA.w, PLAY_AREA.h};
        SDL_Rect _endGame = {PLAY_AREA.w, PLAY_AREA.y, PLAY_AREA.w + TILE_SIZE, PLAY_AREA.h};

        int _waves;
        int _enemiesPerWave;

        int _currentWave;
        int _currentEnemies;

        int _maxDist;
        /*
        int _wavesPerLevel;
        int _levels;

        Object _possibleDrops[4];
        Mob _possibleGenericEnemies[6];
        Mob _possibleStrongEnemies[2];
        */
};

#endif // BATTLE_H
