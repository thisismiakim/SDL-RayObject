#ifndef RAY_H_
#define RAY_H_

#include "Vec3.h"

struct Ray {
    Vec3 origin, dir;
    Ray(const Vec3& origin, const Vec3& dir) : origin(origin), dir(dir) {}
};

#endif