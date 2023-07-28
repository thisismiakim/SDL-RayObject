#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <SDL2/SDL.h>

/* Define a namespace for screen creation */
namespace Graphics{
    struct Screen
    {
        const int WIDTH = 1080;
        const int HEIGHT = 720;

        int center_xpos = WIDTH / 2;
        int center_ypos = HEIGHT / 2;
    };
}
#endif