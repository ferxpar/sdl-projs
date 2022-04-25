#include "Screen.h"

Screen::Screen(SDL_Window *window, SDL_Surface *windowSurface, SDL_Surface *scaledSurface) : _currentWindow(window),
                                                                                             _currentWindowSurface(windowSurface),
                                                                                             _currentScaledSurface(scaledSurface){

    _rectWindowSurface = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    _rectScaledSurface = {0, 0, GAME_WIDTH, GAME_HEIGHT};
    _paintColorBlack = SDL_MapRGB(_currentWindowSurface->format, 0, 0 ,0);

}

Screen::~Screen(){
    //dtor
}

void Screen::renderQuad(SDL_Surface *surf, SDL_Rect *quad, SDL_Rect *pos){
    SDL_BlitSurface(surf, quad, _currentWindowSurface, pos);
}

void Screen::renderFull(SDL_Surface *surf, SDL_Rect *pos){
    SDL_BlitSurface(surf, NULL, _currentWindowSurface, pos);
}

void Screen::scaledQuad(SDL_Surface *surf, SDL_Rect *quad, SDL_Rect *pos){
    SDL_BlitSurface(surf, quad, _currentScaledSurface, pos);
}

void Screen::scaledFull(SDL_Surface *surf, SDL_Rect *pos){
    SDL_BlitSurface(surf, NULL, _currentScaledSurface, pos);
}

void Screen::scaledDebugRect(SDL_Rect *renderRect){
    Uint32 paintRed = SDL_MapRGB(_currentWindowSurface->format, 255, 0 ,0);
    SDL_FillRect(_currentScaledSurface, renderRect, paintRed);
}

void Screen::scale(){
    //render scaled
    SDL_BlitScaled(_currentScaledSurface, NULL, _currentWindowSurface, &_rectWindowSurface);
}

void Screen::flip(){
    //flip
    SDL_UpdateWindowSurface(_currentWindow);
}

void Screen::cls(){
    SDL_FillRect(_currentScaledSurface, &_rectScaledSurface, _paintColorBlack);
}

