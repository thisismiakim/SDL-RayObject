#ifndef TRACING_H_
#define TRACING_H_

#include <iostream>
#include <cmath>
#include "color.h"
#include "object.h"
#include "RGB.h"
#include "Vec3.h"







RGB trace_obj(point src, point dir, sphere sphere){
    
    RGB hitColor = {Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b};
    int hit = 0;

    point L;
    L.x = sphere.centre.x - src.x;
    L.y = sphere.centre.y - src.y;
    L.z = sphere.centre.z - src.z;

    float len = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    dir.x /= len;
    dir.y /= len;
    dir.z /= len;

    float tca = L.x * dir.x + L.y * dir.y + L.z * dir.z;
    float d = sqrt((L.x * L.x + L.y * L.y + L.z * L.z) - tca * tca);

    if (d < sphere.radius) {
        hit = 1;
        float thc = sqrt(sphere.radius * sphere.radius - d * d);
        float th = tca - thc;

        point ph;
        ph.x = src.x + th * dir.x;
        ph.y = src.y + th * dir.y;
        ph.z = src.z + th * dir.z;

        point N;
        N.x = ph.x - sphere.centre.x;
        N.y = ph.y - sphere.centre.y;
        N.z = ph.z - sphere.centre.z;

        float N_len = sqrt(N.x * N.x + N.y * N.y + N.z * N.z);
        N.x /= N_len;
        N.y /= N_len;
        N.z /= N_len;

        float NI = N.x * dir.x + N.y * dir.y + N.z * dir.z;
        if (NI < 0)
            NI *= -1;
        hitColor.r = sphere.color.r * NI;
        hitColor.g = sphere.color.g * NI;
        hitColor.b = sphere.color.b * NI;
    }
    return hitColor;

}


#endif