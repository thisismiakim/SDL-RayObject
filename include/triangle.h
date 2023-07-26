#ifndef TRIANGLE_H_
#define TRIANGLE_H_


#include "Vec3.h"
#include "ray.h"

typedef struct triangle{
    Vec3 v0, v1, v2;
} triangle;


// Möller–Trumbore algorithm
bool rayTriangleIntersect(
    const Vec3 &origin, const Vec3 &dir, // Ray origin position vector and a direction vector
    const Vec3 &v0, const Vec3 &v1, const Vec3 &v2, // three vertices of a triangle
    float &t, float &u, float &v) // temp vectors
{
    // 삼각형의 두 변을 계산
    Vec3 v0v1 = v1 - v0;
    Vec3 v0v2 = v2 - v0;

    // 레이의 방향과 삼각형의 한 변의 벡터곱을 계산
    Vec3 rayDir = dir;
    Vec3 pvec = rayDir.cross(v0v2);
    double det = dot(v0v1, pvec);
    






    return true;
}

#endif