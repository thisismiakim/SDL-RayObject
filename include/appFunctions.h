#ifndef APP_FUNCTIONS_H_
#define APP_FUNCTIONS_H_

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "SDLFunctions.h"
#include "app.h"
#include "graphicFunctions.h"


/* Function to safely shut down the application */ 
void ShutdownApp(){

    // If the application window is not null
    if (app.window != nullptr){
        SDL_DestroyWindow(app.window); // Destroy the SDL window
        app.window = nullptr; // Reset the window pointer to null
    }

    // If the application renderer is not null
    if (app.render != nullptr){
        SDL_DestroyRenderer(app.render); // Destroy the SDL renderer
        app.render = nullptr; // Reset the renederer pointer to null
    }

    SDL_Quit(); // Quit SDL
}


/* Function to initialise the application */ 
static bool InitApp(){

    // Check if SDL is initialised
    if (InitSDL() == false){
        ShutdownApp(); // If SDL failed to initialise, shut down the app
        return false; // Return failure
    }

    // create a SDL window
    app.window = SDL_CreateWindow(
        "Ray Triangle", // window title
        SDL_WINDOWPOS_CENTERED, // window x position
        SDL_WINDOWPOS_CENTERED, // window y position
        app.screen.WIDTH, // window width
        app.screen.HEIGHT, // window height
        SDL_WINDOW_OPENGL  // Flags, in this case, window with OpenGL context
    );

    // Get Error if the window creation failed
    if(app.window == nullptr){
        std::cout << "Unable to create the main window. Error: " << SDL_GetError() << std::endl;
        ShutdownApp();
        return false;
    }

    // create a SDL renderer
    app.render = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_PRESENTVSYNC);

    // Return true, if everything succeeded
    return true;
}

#endif