#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../globales.h"

class Screen
{
    public:
        Screen(SDL_Window *window, SDL_Surface *windowSurface, SDL_Surface *scaledSurface);
        ~Screen();

        void renderQuad(SDL_Surface *surf, SDL_Rect *quad, SDL_Rect *pos);
        //render sprite quad size

        void renderFull(SDL_Surface *surf, SDL_Rect *pos);
        //render sprite full size

        void scaledQuad(SDL_Surface *surf, SDL_Rect *quad, SDL_Rect *pos);
        //render sprite quad size (Pixel Scaled Surface)

        void scaledFull(SDL_Surface *surf, SDL_Rect *pos);
        //render sprite full size (Pixel Scaled Surface)

        void scaledDebugRect(SDL_Rect *renderRect);
        //render rect (Pixel Scaled Surface)

        void scale();
        //scale pixel graphics surface to window surface

        void flip();
        //flip buffer

        void cls();
        //clear screen

    private:

        SDL_Window* _currentWindow;
        SDL_Surface* _currentWindowSurface;
        SDL_Surface* _currentScaledSurface;

        SDL_Rect _rectWindowSurface;
        SDL_Rect _rectScaledSurface;

        Uint32 _paintColorBlack;
};

#endif // SCREEN_H
