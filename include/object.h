#ifndef OBJECT_H_
#define OBJECT_H_

#include <SDL2/SDL.h>
#include <cmath>
#include "RGB.h"
#include "Vec3.h"

// these are structures for sample objects and point

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