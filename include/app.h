#ifndef APP_H_
#define APP_H_

#include <SDL2/SDL.h>
#include "graphic.h"

/* Application Structure */
struct App
{
    SDL_Window* window; // pointer to an SDL_Window
    SDL_Renderer* render; // pointer to an SDL_Renderer
    Graphics::Screen screen; // Screen object from the Graphics namespace

}app;


#endif 