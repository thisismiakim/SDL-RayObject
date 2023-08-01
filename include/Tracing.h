#ifndef TRACING_H_
#define TRACING_H_

#include <iostream>
#include <cmath>
#include "color.h"
#include "object.h"
#include "RGB.h"
#include "Vec3.h"
#include "graphicFunctions.h"


/* a structure for a ray hit */
typedef struct hit {
    int hit; // Flag indicating if there was a hit
    RGB color; // Color of the hit point
    float dist;  // Distance to the hit point
    sphere* sph; // Sphere that was hit
} hit;

/* a structure for a light */
typedef struct light {
    point pos; // Position of the light
    RGB color; // Color of the light
    float brightness; // Brightness of the light
} light;

// Initialize a light
light Light = { {10, 15, 0}, {1, 1, 1}, 1000 };

// sphere variable
sphere scene[2];


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

/* The trace function calculates if a ray hits a sphere, how far the hit point is, and which sphere was hit */
hit trace(point src, Vec3 dir, sphere *sph) {

    hit result = { 0, {0, 0, 0}, 99999, NULL };

    point L;
    L.x = sph->centre.x - src.x;
    L.y = sph->centre.y - src.y;
    L.z = sph->centre.z - src.z;

    float tca = L.x * dir.x + L.y * dir.y + L.z * dir.z;
    float d = sqrt((L.x * L.x + L.y * L.y + L.z * L.z) - tca * tca);

    if (d < sph->radius) {
        result.hit = 1;
        result.sph = sph;
        float thc = sqrt(sph->radius * sph->radius - d * d);
        result.dist = tca - thc;
        if (result.dist < 0.01)
            result.hit = 0;
    }
    return result;
}


/* The traceScene function traces the path of a ray through the entire scene, checking if it hits any of the spheres in the scene
   If the ray hits multiple spheres, it determines which one is the closest */
hit traceScene(point src, Vec3 dir) {

    hit bestHit = { 0, {0, 0, 0}, 99999, NULL };
    int obj;
    for (obj = 0; obj < 1; obj++) {
        hit h = trace(src, dir, &scene[obj]);
        if (h.hit) {
            if (h.dist < bestHit.dist) {
                bestHit = h;
            }
        }
    }
    return bestHit; // The closest hit is returned
}

/* The shade function calculates the color of a hit point, considering the light source and possible reflections from other spheres */
RGB shade(point src, Vec3 dir, hit Hit) {
    
    point ph;
    ph.x = src.x + Hit.dist * dir.x;
    ph.y = src.y + Hit.dist * dir.y;
    ph.z = src.z + Hit.dist * dir.z;

    Vec3 N;
    N.x = ph.x - Hit.sph->centre.x;
    N.y = ph.y - Hit.sph->centre.y;
    N.z = ph.z - Hit.sph->centre.z;
    N.normalize();


    /* Light Source Vector*/
    Vec3 L;
    L.x = ph.x - Light.pos.x;
    L.y = ph.y - Light.pos.y;
    L.z = ph.z - Light.pos.z;

    float lLen2 = L.x * L.x + L.y * L.y + L.z * L.z;
    L.normalize(); 

    L.x = -L.x; 
    L.y = -L.y;
    L.z = -L.z;

    Vec3 V;
    V.x = -dir.x;
    V.y = -dir.y;
    V.z = -dir.z;
    V.normalize();

    /* Half Vector */
    Vec3 H;
    H.x = V.x + L.x;
    H.y = V.y + L.y;
    H.z = V.z + L.z;
    H.normalize(); 

    float cLen;
    cLen = dir.x * N.x + dir.y * N.y + dir.z * N.z;
    cLen *=-1;

    /* Reflection Vector*/
    Vec3 R; 
    R.x = 2 * cLen * N.x + dir.x;
    R.y = 2 * cLen * N.y + dir.y;
    R.z = 2 * cLen * N.z + dir.z;
    R.normalize();

    RGB result;

    /* Specular Highlight */
    float NH = N.x * H.x + N.y * H.y + N.z * H.z; 

    if (NH < 0) {
        result.r = 0;
        result.g = 0;
        result.b = 0;
    }
    else {
        float scale = Light.brightness / lLen2;
        NH = powf(NH, 2);
        result.r = Hit.sph->color.r * NH * Light.color.r * scale;
        result.g = Hit.sph->color.g * NH * Light.color.g * scale;
        result.b = Hit.sph->color.b * NH * Light.color.b * scale;
    }

    hit newH = traceScene(ph, R);
    if (newH.hit) {
        RGB col = shade(ph, R, newH);
        result.r += Hit.sph->color.r * col.r;
        result.g += Hit.sph->color.g * col.g;
        result.b += Hit.sph->color.b * col.b;
    }

    return result; // The final color is returned

}


#endif