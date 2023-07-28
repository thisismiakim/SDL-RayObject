#ifndef APP_H_
#define APP_H_

#include <iostream>
#include <SDL2/SDL.h>
#include "graphic.h"
#include "object.h"

// Application
struct App
{
    SDL_Window* window;
    SDL_Renderer* render;
    //SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    Graphics::Screen screen;

    square square
    {32,
     32,
     screen.center_xpos, 
     screen.center_ypos 
    };

}app;


#endif 