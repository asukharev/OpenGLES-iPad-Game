//
//  GLESMath1.h
//  OpenGL
//
//  Created by Alexander Sukharev on 01.07.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>

template <typename T>
struct Point
{
    Point() : x(0), y(0), z(0) {}
    Point(T x, T y, T z) : x(x), y(y), z(z) {}
    Point<T> operator-(const Point& p) const
    {
        return Vector(this->x - p.x, this->y - p.y,  this->z - p.z);
    }

    T x;
    T y;
    T z;
};

template <typename T>
struct Vertex : public Point<T>
{
    Vertex(T x, T y, T z) : Point<T>(x, y, z) {}
};

template<typename T>
struct Vector : public Point<T>
{
    Vector() : Point<T>(0, 0, 0) {}
    Vector(T x, T y, T z = 0) : Point<T>(x, y, z) {}
    Vector(Point<T> o, Point<T> a)
    {
        this->x = o.x - a.x;
        this->y = o.y - a.y;
        this->z = o.z - a.z;
    }

    T Length() const
    {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }
    void Normalize()
    {
        T s = 1 / this->Length();
        this->x *= s;
        this->y *= s;
        this->z *= s;
    }
    Vector Normalized() const
    {
        Vector v = *this;
        v.Normalize();
        return v;
    }

    // Addition
    Vector operator+(const Vector& v) const
    {
        return Vector(this->x + v.x, this->y + v.y, this->z + v.z);
    }
    void operator+=(const Vector& v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
    }
    // Subtraction
    Vector operator-(const Vector& v) const
    {
        return Vector(this->x - v.x, this->y - v.y,  this->z - v.z);
    }
    void operator-=(const Vector& v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
    }
    // Reverse
    Vector operator-() const
    {
        return Vector(-this->x, -this->y, -this->z);
    }
    // Multiplication
    Vector operator*(T s) const
    {
        return Vector(this->x * s, this->y * s, this->z * s);
    }
    T Dot(const Vector& v) const
    {
        return (this->x * v.x + this->y * v.y + this->z * v.z);
    }
    T operator*(const Vector &v) const
    {
        return this->Dot(v);
    }
    Vector Cross(const Vector& v) const
    {
        return Vector(this->y * v.z - this->z * v.y,
                      this->z * v.x - this->x * v.z,
                      this->x * v.y - this->y * v.x);
    }
    // Division
    Vector operator/(T s) const
    {
        return Vector(this->x / s, this->y / s, this->z / s);
    }
    void operator/=(T s)
    {
        this->x /= s;
        this->y /= s;
        this->z /= s;
    }
};

typedef Vector<float> Vector3;
typedef Point<float> Point3;


typedef Vector<float> vec2;
typedef Vector<float> vec3;
typedef Vector<float> vec4;

typedef Vector<int> ivec2;
typedef Vector<int> ivec3;
typedef Vector<int> ivec4;


#endif /* defined(_VECTOR_H_) */
