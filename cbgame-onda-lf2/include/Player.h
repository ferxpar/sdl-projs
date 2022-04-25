#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "../globales.h"
#include "Screen.h"
#include "SurfaceHandler.h"

enum FACING{
    IZQ,
    DER
};

enum STATE{
    IDLE,
    WALK,
    RUN
};

class Player
{
    public:
        Player();
        ~Player();

        void handleInput(SDL_Event &e);
        void handleJump();
        void handleAnims(int mx, int my);

        void movement(int dx, int dy);
        void collision();

        SDL_Rect getPos();
        int getDx();

        void update();
        void render(SurfaceHandler *surf, Screen *screen);

    private:

        //Sprite *_sprite;
        SDL_Rect _pos;
        int _jmpPos;

        //dynamic stats
        int _hp;
        int _mana;
        int _dx;
        int _dy;
        float _jy;
        STATE _state;
        FACING _facing;
        bool _jumping;

        //anims
        int _animFrame;
        int _idleFrame;
        int _wlkFrame;
        int _runFrame;

        //static stats
        int _wlkSpd;
        int _runSpd;
        float _jumpSpd;



};

#endif // PLAYER_H
