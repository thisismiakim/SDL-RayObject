#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Vec3.h"
#include "ray.h"

/* Defining a structure for a triangle */
typedef struct triangle{
    Vec3 v0, v1, v2; // three vertices of the trianlge
} triangle;


/* Ray Intersect */
// Implementating Möller–Trumbore ray-triangle intersection algorithm
// This function checks whether a ray intersects a given triangle
bool rayTriangleIntersect(
    const Vec3 &origin, const Vec3 &dir, // Ray's origin and direction
    const Vec3 &v0, const Vec3 &v1, const Vec3 &v2, // three vertices of the triangle
    double &t, double &u, double &v) // Variables to store the barycentric coordinates of the intersection point
{
    // Calculate vectors along two edges of the triangle
    Vec3 v0v1 = v1 - v0;
    Vec3 v0v2 = v2 - v0;

    // Caculate determinant using the ray's direction and triangle's one side vector
    Vec3 rayDir = dir;
    Vec3 pvec = rayDir.cross(v0v2);
    double det = dot(v0v1, pvec); // determinant

    // If determinant is near zero, ray lies in plane of triangle
    if (fabs(det) < EPSILON)
        return false; // prevent if determinant is lower than epsilon
    
    double invDet = 1.0 / det; // caculate the inverse of the determinant

    Vec3 tvec = origin - v0; // calculate distance from v0 to ray origin


    // Caculate u parameter
    u = dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) // in this case,
        return false; // the intersection lies outside of the triangle

    
    // qvec is for testing v parameter
    Vec3 qvec = tvec.cross(v0v1);
    v = dot(rayDir, qvec) * invDet; // calculate v parameter
    if (v < 0 || u + v > 1) // in this case,
        return false; // the intersection lies outside of the triangle

    
    // Calculate t, ray intersects triangle
    t = dot(v0v2, qvec) * invDet;

    // Ray intersects the triangle, returns true
    return true;
}

#endif