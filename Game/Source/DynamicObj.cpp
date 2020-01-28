//
//  DynamicObj.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 19.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include "DynamicObj.h"
#include "Vector.h"

DynamicObj::DynamicObj()
{
    time(&_ctime);
}

DynamicObj::~DynamicObj()
{
}

void DynamicObj::impactWith(DynamicObj *object)
{
    float k1 =  ((_velocity * _velocity) * _mass) / 2;
    float k2 =  ((object->_velocity * object->_velocity) * object->_mass) / 2;
    if (k1 > k2)
    {
        Vector<float> x_axis = object->_position - _position;
        x_axis.Normalize();
        float v_add = 0.01f;
        float p = x_axis * object->_velocity * object->_mass - x_axis * _velocity * _mass; // impulse
        if (p < 0.0f)
        {
            p -= v_add * (_mass + object->_mass);
            float odm = _mass / (_mass + object->_mass);
            Vector<float> dp = x_axis * p;
            _velocity += dp / _mass * (1-odm);
            object->_velocity -= dp / object->_mass * odm;
        }
    }
    else if (k2 > 0.0f)
    {
        object->impactWith(this);
    }
}

void DynamicObj::drainEnergy(unsigned long e)
{
//    if (_energy < e)
//    {
//        _energy = 0;
//    }
//    else
//    {
//        _energy -= e;
//    }
}

bool DynamicObj::isAlive()
{
	return (_energy > 0);
}
