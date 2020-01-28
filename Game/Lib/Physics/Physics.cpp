//
//  Physics.cpp
//  OpenGL
//
//  Created by Alexander Sukharev on 01.07.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include "Physics.h"

float Kinetic(PhysObject &o)
{
    return ((o.velocity * o.velocity) * o.mass) / 2;;
}

void Impact(PhysObject &o1, PhysObject &o2)
{
    float k1 = Kinetic(o1);
    float k2 = Kinetic(o2);
    if (k1 > k2)
    {
        Vector3 x_axis = Vector<float>(o1.position, o2.position);
        x_axis.Normalize();

        float v_add = 0.01f;
        float p = x_axis * o2.velocity * o2.mass - x_axis * o1.velocity * o1.mass; // impulse
        if (p < 0.0f)
        {
            p -= v_add * (o1.mass + o2.mass);
            float odm = o1.mass / (o1.mass + o2.mass);
            Vector<float> dp = x_axis * p;

            o1.velocity += dp / o1.mass * (1-odm);
            o2.velocity -= dp / o2.mass * odm;
        }
    }
    else if (k2 > 0)
    {
        Impact(o2, o1);
    }
}