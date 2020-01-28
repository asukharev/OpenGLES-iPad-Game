//
//  Physics.h
//  OpenGL
//
//  Created by Alexander Sukharev on 01.07.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef __OpenGL__Physics__
#define __OpenGL__Physics__

#include "Vector.h"

typedef struct
{
    float mass;
    float E;
    float K;
    Vector3 velocity;
    Point3 position;
} PhysObject;

float Kinetic(PhysObject &o);
void Impact(PhysObject &o1, PhysObject &o2);

#endif /* defined(__OpenGL__Physics__) */
