#include "Player.h"

Player::Player() : _dx(0), _dy(0), _jy(0),
                   _wlkSpd(1), _runSpd(2), _jumpSpd(4),
                   _animFrame(0), _wlkFrame(0), _idleFrame(0), _runFrame(0){
    //ctor
    _hp = 100;
    _mana = 100;
    _state = IDLE;
    _facing = DER;
    _jumping = false;
    _jmpPos = 0;

    int rndInPlayArea = rand() % (PLAY_AREA.h - PLAY_AREA.y - 10) + PLAY_AREA.y;
    _pos = {10, rndInPlayArea, 10, 10};


}

Player::~Player(){
    //dtor
}

void Player::handleInput(SDL_Event &e){
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    int move_x = 0;
    int move_y = 0;

    if(currentKeyStates[SDL_SCANCODE_C]){
        if(!_jumping){
            _jumping = true;
            _jy = -_jumpSpd;
        }
    }

    if( currentKeyStates[ SDL_SCANCODE_W ] ){
        move_y = -1;
    } else if(currentKeyStates[ SDL_SCANCODE_S ] ){
        move_y = 1;
    } else {
        move_y = 0;
    }

    if( currentKeyStates[ SDL_SCANCODE_A ] ){
        move_x = -1;
        _facing = IZQ;
    } else if( currentKeyStates[ SDL_SCANCODE_D ] ){
        move_x = 1;
        _facing = DER;
    } else{
        move_x = 0;
    }

    handleAnims(move_x, move_y);
    movement(move_x, move_y);
}

void Player::handleJump(){

    if(_jumping){

        if(_jmpPos + _jy > 0){
            _jy = 0;
            _jmpPos = 0;
            _jumping = false;
        }  else {
            _jy += GRAVITY;

        }
    }
}

void Player::handleAnims(int mx, int my){
    if(mx != 0 || my != 0){
        _state = WALK;
    } else {
        _state = IDLE;
    }
}

void Player::movement(int dx, int dy){
    float mx = dx;
    float my = dy;

    mx *= _wlkSpd;
    my *= _wlkSpd;

    _dx = mx;
    _dy = my;

}

void Player::collision(){

    if(_pos.x + _dx <= PLAY_AREA.x){
        _dx = 0;
        _pos.x = PLAY_AREA.x;
    }

    if(_pos.x + _dx >= PLAY_AREA.w - TILE_SIZE){
        _dx = 0;
        _pos.x = PLAY_AREA.w - TILE_SIZE;
    }

    if(_pos.y + _dy <= PLAY_AREA.y - TILE_SIZE/2){
        _dy = 0;
        _pos.y = PLAY_AREA.y - TILE_SIZE/2;
    }

    if(_pos.y + _dy >= PLAY_AREA.h - TILE_SIZE - TILE_SIZE / 2){
        _dy = 0;
        _pos.y = PLAY_AREA.h - TILE_SIZE - TILE_SIZE / 2;
    }
}

SDL_Rect Player::getPos(){
    return _pos;
}

int Player::getDx(){
    return _dx;
}

void Player::update(){
    _animFrame = (_animFrame + 1) % GAME_FPS;
    if(_animFrame > 0){
        _idleFrame = 0;
        _wlkFrame = 0;
        _runFrame = 0;
    }
    if(_animFrame > GAME_FPS / 4){
        _wlkFrame = 1;
        _runFrame = 1;
    }
    if(_animFrame > GAME_FPS / 2 ){
        _idleFrame = 1;
        _wlkFrame = 2;
        _runFrame = 2;
    }
    if(_animFrame > GAME_FPS * 3 / 4 ){
        _wlkFrame = 3;
        _runFrame = 3;
    }

    handleJump();

    collision();

    _pos.x += _dx;
    _pos.y += _dy;
    _jmpPos = (int)(_jmpPos + _jy);
}

void Player::render(SurfaceHandler *surf, Screen *screen){
    //shadow
    surf->renderQuad(0,12, &_pos, screen);

    //relative pos
    SDL_Rect relativePos = SDL_Rect({_pos.x, _pos.y + _jmpPos, _pos.w, _pos.h});

    //sprite
    if(_state == IDLE){
        if(_facing == DER){
            surf->renderQuad(0 + _idleFrame, 8, &relativePos, screen);
        } else {
            surf->renderQuadFlip(0 + _idleFrame, 8, &relativePos, screen);
        }
    } else if(_state == WALK){
        if(_facing == DER){
            surf->renderQuad(0 + _wlkFrame, 9, &relativePos, screen);
        } else {
            surf->renderQuadFlip(0 + _wlkFrame, 9, &relativePos, screen);
        }
    }

}
