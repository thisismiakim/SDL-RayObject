#ifndef SDL_FUNCTIONS_H_
#define SDL_FUNCTIONS_H_

#include <iostream>
#include <SDL2/SDL.h>

/* Initialising SDL Library */
bool InitSDL()
{    
    // Initialising the SDL's subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0 ){
        std::cout << "SDL_Init failed with error: "<< SDL_GetError() << std::endl; // Print error if there's an error
        return false;
    }
    return true; //  // If the SDL was initialized successfully, the function returns true
    
}

#endif