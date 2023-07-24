#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
#include <SDL2/SDL.h>
#include "RGB.h"

typedef struct point {
    float x;
    float y;
    float z;
} point;


typedef struct square
{
    int HEIGHT;
    int WIDTH;
    int xpos;
    int ypos;
}square;


typedef struct sphere {
    point centre;
    float radius;
    RGB color;
} sphere;






#endif