//
//  Laser.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 18.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include "Laser.h"
#include "ParametricEquations.h"
#include "Common.h"

Laser::Laser(Vector<float> position, Vector<float> direction, Vector<float> svelocity)
{
    otype = OTHER;
    shape = SPHERE;
    ISurface *surface = new Sphere(.5f);
    surface->SetVertexFlags(VertexFlagsNormals);
    initBuffer(surface);
    delete surface;

    //
    _position = position;
    _aabb._P = _position;
    _velocity = svelocity;
    _direction = direction;
    _acceleration = {1.0f, 1.0f, 0.0f};
    _mass = 0.1f;
    _r = {0.0f, 0.0f, 0.0f};
    _lifetime = 2;
    _energy = 1;
    
    float acceleration = 2.0f;

    float d = sqrt(_direction.x*_direction.x + _direction.y*_direction.y + _direction.z*_direction.z);
    if (d != 0.0f)
    {
        Vector<float> velocity = {
            _direction.x/d*acceleration,
            _direction.y/d*acceleration,
            _direction.z/d*acceleration};
        _velocity = _velocity + velocity;
    }

    _textureIndex = 0;
}

Laser::~Laser()
{
}

//void Laser::impactWith(DynamicObj *object)
//{
//    object->_energy -= _energy;
//    _isAlive = false;
//}

bool Laser::isAlive()
{
    if (_isAlive)
    {
        unsigned long dtime = _time - _ctime;
        if (dtime >= _lifetime)
        {
            _isAlive = false;
        }
    }

    return _isAlive;
}

void Laser::update()
{
    _position += _velocity;
    _aabb._P = _position;

//    if (_position.x > _glwidth || _position.x < -_glwidth || _position.y > _glheight || _position.y <= -_glheight)
//    {
//        _isAlive = false;
//    }
}
