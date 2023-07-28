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

        // 여기서 obj.txt 데이터를 가져오면 되는거 같고..
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

        // triangle dataTri{
        //     data[0],
        //     data[1],
        //     data[2]
        // };



        // triangle
        triangle triangle1 {
            Vec3(-1, 1,3),
            Vec3(1,-1,3),
            Vec3(0,1,3)

            // for each 3번 반복해서 v를 넣으면 됨
            // array로 데이터?
        };

        triangle triangle2{
            Vec3(1.294361019e+01, 954203606e+00, 080653763e+01),
            Vec3(1.418311119e+01,-621198177e+00, 5.931306458e+01),
            Vec3(1.410698414e+01,6.146854401e+00, 940632629e+01)
        };
        // 삼각형 로드에 실패


        TracingTriangle(triangle2);


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

