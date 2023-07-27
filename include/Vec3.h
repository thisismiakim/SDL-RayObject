#ifndef VEC3_H_
#define VEC3_H_

#include <stdexcept>
#include <cmath>
#include <array>

#define PI 3.14159265359
#define EPSILON 1e-9

// Define a Vec3 struct
struct Vec3{
    double x;
    double y;
    double z;

    // Constructor that takes three double values as parameters and initializes the data members
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    // Overload the + (addition),- (subtraction) operators
    // v1 is other vector
    Vec3 operator + (const Vec3& v1) const {
        return Vec3(x + v1.x, y + v1.y, z + v1.z);
    }

    Vec3 operator - (const Vec3& v1) const {
        return Vec3(x - v1.x, y - v1.y, z - v1.z);
    }

    // Overload the * (scalar multiplication), / (scalar division) operators
    // s is scalar
    Vec3 operator * (double s) const {
        return Vec3(x * s, y * s, z * s);
    }

    Vec3 operator / (double s) const {
        if (s != 0.0){
            return Vec3(x/s, y/s, z/s);
        }
        else{
            throw std::runtime_error("Vector division by zero");
        }
    }


    // normalize
    Vec3 normalize() const {
        // divide vector by its magnitude
        double mag = sqrt(x*x + y*y + z*z);
        return Vec3(x/mag, y/mag, z/mag);
    }

    // cross product
    Vec3 cross (const Vec3& v)
    {    
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

};

// calculate dot product of two vectors
inline double dot(const Vec3& v1, const Vec3& v2){
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}





#endif