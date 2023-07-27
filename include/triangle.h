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
    double &t, double &u, double &v) // temp vectors
{
    // 삼각형의 두 변을 계산
    Vec3 v0v1 = v1 - v0;
    Vec3 v0v2 = v2 - v0;

    // 레이의 방향과 삼각형의 한 변의 벡터곱을 계산
    Vec3 rayDir = dir;
    Vec3 pvec = rayDir.cross(v0v2);
    double det = dot(v0v1, pvec);

    if (fabs(det) < EPSILON)
        return false;
    
    // invert det
    double invDet = 1.0 / det;



    // 레이의 원점에서 삼각형의 한 꼭짓점까지의 벡터를 연산
    Vec3 tvec = origin - v0;
    // u 값을 계산 (u 는 삼각형 내부의 상대적인 위치를 나타냄)
    u = dot(tvec, pvec) * invDet;
    // u 가 0보다 작거나 1보다 크면 레이는 삼각형과 교차하지 않음
    if (u < 0 || u > 1) 
        return false;


    
    // qvec 을 계산 (tvec 와 삼각형의 한 변의 벡터곱)
    Vec3 qvec = tvec.cross(v0v1);
    // v 값을 계산 (v 는 삼각형 내부의 상대적인 위치를 나타냄)
    v = dot(rayDir, qvec) * invDet;
    // v 가 0보다 작거나 u+v 가 1보다 크면 레이는 삼각형과 교차하지 않음
    if (v < 0 || u + v > 1) 
        return false;
    

    // t 값을 계산 (t 는 레이의 원점에서 교점까지의 거리)
    t = dot(v0v2, qvec) * invDet;

    // 레이와 삼각형이 교차하므로 true 를 반환
    return true;
}

#endif