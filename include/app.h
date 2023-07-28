#ifndef APP_H_
#define APP_H_

#include <SDL2/SDL.h>
#include "graphic.h"
#include "object.h"

/* Application Structure */
struct App
{
    SDL_Window* window; // pointer to an SDL_Window
    SDL_Renderer* render; // pointer to an SDL_Renderer
    Graphics::Screen screen; // Screen object from the Graphics namespace

    /* Defining Sample Objects */ 
    // center Square
    square square
    {50, // Length of the square side
     50, // Width of the square side
     screen.center_xpos, // x pos
     screen.center_ypos  // y pos
    };

    // center Triangle


}app;


#endif 