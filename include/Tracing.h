#ifndef TRACING_H_
#define TRACING_H_

#include <iostream>
#include <cmath>
#include "color.h"
#include "object.h"
#include "RGB.h"
#include "Vec3.h"


/* Function for tracing a sphere*/
// This function traces the path of a ray onto a sphere and returns the color of the point hit by the ray
RGB trace_obj(point src, point dir, sphere sphere){
    
    // Initializing hitColor to BLACK
    RGB hitColor = {Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b}; // no hit by default
    // Flag to indicate whether a hit occurred
    int hit = 0; 

    // Vector from the source of the ray to the center of the sphere
    point L;
    L.x = sphere.centre.x - src.x;
    L.y = sphere.centre.y - src.y;
    L.z = sphere.centre.z - src.z;

    // Normalize the direction vector
    float len = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    dir.x /= len;
    dir.y /= len;
    dir.z /= len;

    // Calculate the projection of L onto dir
    float tca = L.x * dir.x + L.y * dir.y + L.z * dir.z;
    // Calculate the shortest distance from the sphere center to the ray
    float d = sqrt((L.x * L.x + L.y * L.y + L.z * L.z) - tca * tca);

    // If the shortest distance is less than the sphere's radius, the ray hits the sphere
    if (d < sphere.radius) {
        hit = 1;

        // Calculate the distance from the ray source to the hit point
        float thc = sqrt(sphere.radius * sphere.radius - d * d);
        float th = tca - thc;

        // Calculate the hit point coordinates
        point ph;
        ph.x = src.x + th * dir.x;
        ph.y = src.y + th * dir.y;
        ph.z = src.z + th * dir.z;

        // Calculate the normal at the hit point
        point N;
        N.x = ph.x - sphere.centre.x;
        N.y = ph.y - sphere.centre.y;
        N.z = ph.z - sphere.centre.z;

        // Normalize the normal
        float N_len = sqrt(N.x * N.x + N.y * N.y + N.z * N.z);
        N.x /= N_len;
        N.y /= N_len;
        N.z /= N_len;

        // Calculate the intensity of the light at the hit point
        float NI = N.x * dir.x + N.y * dir.y + N.z * dir.z;
        if (NI < 0)
            NI *= -1;

        // Calculate the color of the hit point
        hitColor.r = sphere.color.r * NI;
        hitColor.g = sphere.color.g * NI;
        hitColor.b = sphere.color.b * NI;
    }

    // Return the color of the hit point (or BLACK if no hit)
    return hitColor;

}


#endif