#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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

struct TriangleOBJ
{
    Vec3 v1, v2, v3;
};

int numTriangles = 0; // this is a counter for triangles in object.txt file

std::vector<TriangleOBJ> loadTriangles(const std::string& filename)
{
    std::vector<TriangleOBJ> triangles;
    std::ifstream file("objectLite.txt");

    if (!file.is_open())
    {
        std::cout << "Failed to open the file." << std::endl;
        return triangles;
    }

        std::string line;
        int triangleCount = 0; 
        while (std::getline(file, line)) 
        {
            std::istringstream iss(line);
            TriangleOBJ triangle;
            char comma; // To discard the comma character

            // Read x, y, z for v1
            iss >> triangle.v1.x >> comma >> triangle.v1.y >> comma >> triangle.v1.z;
            
            // Read x, y, z for v2
            iss >> triangle.v2.x >> comma >> triangle.v2.y >> comma >> triangle.v2.z;
            
            // Read x, y, z for v3
            iss >> triangle.v3.x >> comma >> triangle.v3.y >> comma >> triangle.v3.z;

            triangles.push_back(triangle);
            numTriangles++;
        }


    file.close();

    return triangles;
    
}





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
        

        /* Load Object */


        // a center basic triangle
        triangle centerTriangle {
            Vec3(1.0f, 0.5f, 2.0f),
            Vec3(1.5f,1.5f,2.0f),
            Vec3(0.5f,1.5f,2.0f)
        };


        // Object.txt first triangle
        triangle newTriangle{
            Vec3(float(1.294361019e+01),float(8.954203606e+00), float(6.080653763e+01)),
            Vec3(float(1.418311119e+01),float(7.621198177e+00), float(5.931306458e+01)),
            Vec3(float(1.410698414e+0), float(6.146854401e+00), float(5.940632629e+01))
        };


        // Load Object.txt
        std::vector<TriangleOBJ> triangles = loadTriangles("triangles.txt");
        
        // numTriangles
        for (int i=0; i < numTriangles; i++){
            triangle Object{
            Vec3(triangles[i].v1.x,triangles[i].v1.y, triangles[i].v1.z),
            Vec3(triangles[i].v2.x,triangles[i].v2.y, triangles[i].v2.z),
            Vec3(triangles[i].v3.x, triangles[i].v3.y, triangles[i].v3.z)
             };
            TracingTriangle(Object);
        }


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

