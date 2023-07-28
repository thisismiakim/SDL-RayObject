#include <iostream>

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
#include "RGB.h"
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

        // 여기서 obj.txt 데이터를 가져오면 되는거 같고..


        triangle triangle1 {
            Vec3(-1, 1,3),
            Vec3(1,-1,3),
            Vec3(0,1,3)
        };

        TracingTriangle(triangle1,{255 , 250, 0} );



        // Update the screen with the content rendered in the background buffer
        SDL_RenderPresent(app.render);
        SDL_Delay(100);

    }

    ShutdownApp();
    return EXIT_SUCCESS;
}

