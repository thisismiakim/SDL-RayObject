// triangle struct

// .cpp 로 빼도 되고
// bool intersect
// update
// get normal

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Vec3.h"

typedef struct triangle{
    Vec3 p1, p2, p3;
} triangle;

// Vector3 normal; 
// 미리 계산되거나 
// (vertex2 - vertex1)과 (vertex3 - vertex1)의 cross product로 계산됩니다.



bool rayTriangleIntersect()
{



    return true;
}

// -> 레이트레이싱 알고리즘

#endif