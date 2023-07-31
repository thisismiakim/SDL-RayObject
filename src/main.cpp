#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include <cmath>

#include "SDLFunctions.h"
#include "color.h"
#include "graphic.h"
#include "app.h"
#include "graphicFunctions.h"
#include "appFunctions.h"
#include "Vec3.h"
#include "triangle.h"



int main(int argc, char *argv[])
{
    if (InitApp() == false) 
    {   
        ShutdownApp();
        return EXIT_FAILURE;
    }

    // Drawing loop
    SDL_Event event;
    bool running = true;

    while(running){
        ClearScreen(app.render);


        // Check and process I/O events
        // key events
        if (SDL_PollEvent(&event))
        {
            switch (event.type)// 
            {
                case SDL_KEYDOWN:
                {
                    running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
                    break;
                }
                case SDL_QUIT:
                {
                    running = false;
                    break;
                }
                default: 
                    break;
            }
        }
        
        // Draw the new content on the renderer

        std::vector<Vec3> data;
        std::ifstream file("object.txt");

        if (file.is_open()){
            std::string line;
            while (std::getline(file, line)){
                std::istringstream iss(line);
                Vec3 v;
                if (iss >> v.x >> v.y >>v.z){
                    data.push_back(v);
                }
            }
            file.close();
        }
        else{
            std::cout << "failed";
        }


        // triangle
        triangle centerTriangle {
            Vec3(1.0f, 0.5f, 2.0f),
            Vec3(1.5f,1.5f,2.0f),
            Vec3(0.5f,1.5f,2.0f)
        };


        TracingTriangle(centerTriangle);

        // Update the screen with the content rendered in the background buffer
        SDL_RenderPresent(app.render);
        SDL_Delay(100);


        SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, app.screen.WIDTH, app.screen.HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);
        if (surface == NULL) {
            std::cout << "Surface creation failed with error:  "<< SDL_GetError() << std::endl; // Print error if there's an error
            return EXIT_FAILURE;
        }

        // Copy renderer to surface
        if (SDL_RenderReadPixels(app.render, NULL, SDL_PIXELFORMAT_RGBA32, surface->pixels, surface->pitch) != 0) {
            std::cout << "Reading pixels from renderer failed with error:  "<< SDL_GetError() << std::endl; // Print error if there's an error
            return EXIT_FAILURE;
        }

        // Save Surface image
        if (IMG_SavePNG(surface, "./img/output.png") != 0) {
            std::cout << "Saving surface to file failed with error:  "<< SDL_GetError() << std::endl; // Print error if there's an error
            return EXIT_FAILURE;  
        }

        SDL_FreeSurface(surface);
    }

    ShutdownApp();
    return EXIT_SUCCESS;
}

