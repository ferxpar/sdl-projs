#include "Battle.h"

Battle::Battle(Tile areaTiles[12], Tile areaBg[12], Player plr) : _map(areaTiles, areaBg), _player(plr)
{
    //ctor
    _waves = 5;
    _enemiesPerWave = 0;

    _currentWave = 0;
    _currentEnemies = 0;

    _maxDist = 0;
}

Battle::~Battle()
{
    //dtor
}

void Battle::inputBattle(SDL_Event &e){

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    if(currentKeyStates[SDL_SCANCODE_L]){
        if(_currentWave < _waves){
            _currentWave++;
            _maxDist++;
        }

    }

    _player.handleInput(e);
}

void Battle::updateBattle(){
    _map.update();
    _player.update();

    if(_player.getDx() < 0 && collision(_player.getPos(), _goBackwards)){
        _map.moveCam(_player.getDx());
    }

    if(_player.getDx() > 0 && collision(_player.getPos(), _goFoward)){
        _map.moveCam(_player.getDx());
    }

}

void Battle::renderMap(Screen *screen){
    _map.render(screen);

    screen->scaledDebugRect(&_goBackwards);
    screen->scaledDebugRect(&_goFoward);
}
void Battle::renderMobs(SurfaceHandler *surf, Screen *screen){
    _player.render(surf, screen);

}

bool Battle::collision(SDL_Rect rect1, SDL_Rect rect2){
    bool xcol = false;
    bool ycol = false;

    if(rect1.x >= rect2.x && rect1.x <= rect2.x + rect2.w){
        xcol = true;
    } else {
        xcol = false;
    }

    if(rect1.x + rect1.w >= rect2.x && rect1.x <= rect2.x + rect2.w){
        xcol = true;
    } else {
        xcol = false;
    }



    if(rect1.y >= rect2.y && rect1.y <= rect2.y + rect2.h){
        ycol = true;
    } else {
        ycol = false;
    }

    return xcol && ycol;
}

void Battle::debug(Screen *screen){
    //SDL_Rect rect2 = {0,16,100,100}
}

void Battle::incrementDistance(){
    _maxDist += TILE_LOOP * 10;
}


