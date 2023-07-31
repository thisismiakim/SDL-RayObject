#ifndef GRAPHIC_FUNCTIONS_H_
#define GRAPHIC_FUNCTIONS_H_

#include <SDL2/SDL.h>
#include "SDLFunctions.h"
#include "color.h"
#include "graphic.h"
#include "app.h"
#include "graphicFunctions.h"
#include "appFunctions.h"
#include "Vec3.h"
#include "triangle.h"


/* Clear the screen */
// This function clears the renderer by erasing everything on the render and painting all the pixels with a predefined color (black in this case)
// It runs every frame before a new state is drawn to the renderer
static void ClearScreen(SDL_Renderer* renderer){
    // set the drawing colour to black
    SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b,Colors::BLACK.a);
    // clear the entire rendering target with the drawing colour
    SDL_RenderClear(renderer);
}


/* Drawing Function */

// Tracing a triangle
// This function traces a triangle and draws it on the screen
void TracingTriangle(triangle triangle1)
{
    // Set the render draw colour
    SDL_SetRenderDrawColor(app.render, Colors::BLUE.r, Colors::BLUE.g, Colors::BLUE.b, Colors::BLUE.a);
    // loop over the entire screen and trace the triangle
    for (int x=0; x < app.screen.WIDTH; ++x)
    {
        for (int y=0; y < app.screen.HEIGHT; ++y)
        {
            Vec3 origin(0,0,0);
            Vec3 dir(float(x)/app.screen.WIDTH,float(y)/app.screen.HEIGHT,1);
            dir = dir.normalize();
            double t, u, v;

            // If the ray intersects with the trianlge, draw a point at the corresponding pixel
            if (rayTriangleIntersect(origin, dir,
                                    triangle1.v0, triangle1.v1, triangle1.v2,
                                    t, u, v ))
                {
                    SDL_RenderDrawPoint(app.render, x, y);
                }
        }

    }
}


#endif