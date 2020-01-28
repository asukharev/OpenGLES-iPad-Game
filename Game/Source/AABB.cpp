//
//  AABB.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 18.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include "AABB.h"
//#include <stdio.h>

cdAABB::cdAABB()
{
}

cdAABB::~cdAABB()
{
}

cdAABB::cdAABB(float *vertices, int count, int vertexSize, Vector<float> scale)
{
    float
        min_x, max_x,
        min_y, max_y,
        min_z, max_z;
    min_x = max_x = 0.0f;
    min_y = max_y = 0.0f;
    min_z = max_z = 0.0f;

    int end = count/vertexSize;

    for (int i = 0; i < end; i += vertexSize)
    {
//        printf("%d %f, %f, %f\n", i, vertices[i], vertices[i+1], vertices[i+2]);
        if (vertices[i] < min_x) min_x = vertices[i];
        if (vertices[i] > max_x) max_x = vertices[i];
        if (vertices[i+1] < min_y) min_y = vertices[i+1];
        if (vertices[i+1] > max_y) max_y = vertices[i+1];
        if (vertices[i+2] < min_z) min_z = vertices[i+2];
        if (vertices[i+2] > max_z) max_z = vertices[i+2];
    }
    _E = {max_x-min_x, max_y-min_y, max_z-min_z};
//    _E /= 1.5f;
    _P = {min_x/2, min_y/2, min_z/2};
//    _P += _E;
}

const bool cdAABB::OverlapsAABB(const cdAABB &aabb) const
{
    bool resx, resy, resz;

    const Vector<float> T = aabb._P - _P;
    resx = fabsf(T.x) <= fabsf((_E.x + aabb._E.x));
    resy = fabsf(T.y) <= fabsf((_E.y + aabb._E.y));
    resz = fabsf(T.z) <= fabsf((_E.z + aabb._E.z));

    if (resx && resy && resz)
    {
        return true;
    }
    return false;
}

const bool cdAABB::OverlapsSphere(const cdAABB &aabb) const
{
    return false;
}
