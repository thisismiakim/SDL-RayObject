#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include <cmath>


#include "SDLFunctions.h"
#include "color.h"
#include "graphic.h"
#include "object.h"
#include "app.h"
#include "graphicFunctions.h"
#include "appFunctions.h"
#include "RGB.h"
#include "Vec3.h"
#include "Tracing.h"
#include "triangle.h"


int main(int argc, char *argv[])
{
    if (InitApp() == false) 
    {   
        ShutdownApp();
        return EXIT_FAILURE;
    }

    // Draw loop
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

        // Raytracing here ..

        // Draw the new content on the renderer
        //DrawSquare(app.square.xpos, app.square.ypos);
        // 여기서 데이터를 가져오면 되는거 같고..
        //TracingSphere({0, 0, 10}, 5, {255 , 250, 0} );

        // 여기서 obj.txt 데이터를 가져오면 되는거 같고..
        triangle triangle1 {
            Vec3(-1, 1,3),
            Vec3(1,-1,3),
            Vec3(0,1,3)
        };

        // win surface 대신 width/height?
        // 알고리즘은 맞는데 드로잉 방식이 틀린듯함
        for (int x=0; x < app.screenSurface->w; ++x)
        {
            for (int y=0; y < app.screenSurface->h; ++y)
            {
                Vec3 origin(0,0,0);
                Vec3 dir(float(x)/app.screenSurface->w,float(y)/app.screenSurface->h,1);
                dir = dir.normalize();

                double t, u, v;
                if (rayTriangleIntersect(origin, dir,
                                        triangle1.v0, triangle1.v1, triangle1.v2,
                                        t, u, v ))
                    {
                    ((Uint32*)app.screenSurface->pixels)[(y*app.screenSurface->w)+x] = SDL_MapRGB(app.screenSurface->format, 255, 255, 255);
                    }
            }

        }
        



        // Update the screen with the content rendered in the background buffer
        SDL_UpdateWindowSurface(app.window);
        SDL_RenderPresent(app.render);
        SDL_Delay(100);

    }

    ShutdownApp();
    return EXIT_SUCCESS;
}

