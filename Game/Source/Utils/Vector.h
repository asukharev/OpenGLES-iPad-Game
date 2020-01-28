#pragma once

#include "GLESMath.h"

const float Pi = M_PI;
const float TwoPi = 2 * M_PI;

template <typename T>
struct Vector2
{
    Vector2() {}
    Vector2(T x, T y) : x(x), y(y) {}
    T Dot(const Vector2& v) const
    {
        return x * v.x + y * v.y;
    }
    T operator*(const Vector2 &v) const
    {
        return (x * v.x + y * v.y);
    }
    Vector2 operator+(const Vector2& v) const
    {
        return Vector2(x + v.x, y + v.y);
    }
    Vector2 operator-(const Vector2& v) const
    {
        return Vector2(x - v.x, y - v.y);
    }
    Vector2 operator/(float s) const
    {
        return Vector2(x / s, y / s);
    }
    Vector2 operator*(float s) const
    {
        return Vector2(x * s, y * s);
    }
    void Normalize()
    {
        float s = 1.0f / Length();
        x *= s;
        y *= s;
    }
    Vector2 Normalized() const 
    {
        Vector2 v = *this;
        v.Normalize();
        return v;
    }
    T LengthSquared() const
    {
        return x * x + y * y;
    }
    T Length() const
    {
        return sqrt(LengthSquared());
    }
    operator Vector2<float>() const
    {
        return Vector2<float>(x, y);
    }
    bool operator==(const Vector2& v) const
    {
        return x == v.x && y == v.y;
    }
    Vector2 Lerp(float t, const Vector2& v) const
    {
        return Vector2(x * (1 - t) + v.x * t,
                       y * (1 - t) + v.y * t);
    }
    template <typename P>
    P* Write(P* pData)
    {
        Vector2* pVector = (Vector2*) pData;
        *pVector++ = *this;
        return (P*) pVector;
    }
    // Get the angle between this vector and v in degrees.
    float angleTo(const Vector2& v) const
    {
        float rad;
        Vector2 u = *this;
        float dot = (u * v) / (u.Normalized() * v.Normalized());
        rad = acosf(dot);
        if (v.y > u.y)
            rad = 2*M_PI - rad;

        return rad * 180 / M_PI;
    }
    T x;
    T y;
};

template <typename T>
struct Vector3
{
    Vector3() {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    void Normalize()
    {
        float s = 1.0f / sqrt(x * x + y * y + z * z);
        x *= s;
        y *= s;
        z *= s;
    }
    Vector3 Normalized() const 
    {
        Vector3 v = *this;
        v.Normalize();
        return v;
    }
    Vector3 Cross(const Vector3& v) const
    {
        return Vector3(y * v.z - z * v.y,
                       z * v.x - x * v.z,
                       x * v.y - y * v.x);
    }
    T Dot(const Vector3& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }
    void rotate(const double deg)
    {
        double x, y;
        double rad;

        x = this->x;
        y = this->y;

        rad = deg * M_PI / 180;

        this->x = x * cos(rad) - y * sin(rad);
        this->y = x * sin(rad) + y * cos(rad);
    }
    T operator*(const Vector3 &v) const
    {
        return (this->x * v.x + this->y * v.y + this->z * v.z);
    }
    Vector3 operator+(const Vector3& v) const
    {
        return Vector3(x + v.x, y + v.y,  z + v.z);
    }
    void operator+=(const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    void operator-=(const Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }
    void operator/=(T s)
    {
        x /= s;
        y /= s;
        z /= s;
    }
    Vector3 operator-(const Vector3& v) const
    {
        return Vector3(x - v.x, y - v.y,  z - v.z);
    }
    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }
    Vector3 operator*(T s) const
    {
        return Vector3(x * s, y * s, z * s);
    }
    Vector3 operator/(T s) const
    {
        return Vector3(x / s, y / s, z / s);
    }
    bool operator==(const Vector3& v) const
    {
        return x == v.x && y == v.y && z == v.z;
    }
    Vector3 Lerp(float t, const Vector3& v) const
    {
        return Vector3(x * (1 - t) + v.x * t,
                       y * (1 - t) + v.y * t,
                       z * (1 - t) + v.z * t);
    }
    const T* Pointer() const
    {
        return &x;
    }
    template <typename P>
    P* Write(P* pData)
    {
        Vector3<T>* pVector = (Vector3<T>*) pData;
        *pVector++ = *this;
        return (P*) pVector;
    }
    // Get the angle between this vector and v in degrees.
    float angleTo(const Vector3& v) const
    {
        float rad;
        Vector3 u = *this;
        float dot = (u * v) / sqrt(u.Normalized() * v.Normalized());
        rad = acosf(dot);
        if (v.y > u.y)
            rad = 2*M_PI - rad;

        return rad * 180 / M_PI;
    }
    T x;
    T y;
    T z;
};

template <typename T>
struct Vector4
{
    Vector4() {}
    Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    T Dot(const Vector4& v) const
    {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }
    Vector4 Lerp(float t, const Vector4& v) const
    {
        return Vector4(x * (1 - t) + v.x * t,
                       y * (1 - t) + v.y * t,
                       z * (1 - t) + v.z * t,
                       w * (1 - t) + v.w * t);
    }
    const T* Pointer() const
    {
        return &x;
    }
    T x;
    T y;
    T z;
    T w;
};

typedef Vector2<bool> bvec2;

typedef Vector2<int> ivec2;
typedef Vector3<int> ivec3;
typedef Vector4<int> ivec4;

typedef Vector2<float> vec2;
typedef Vector3<float> vec3;
typedef Vector4<float> vec4;
