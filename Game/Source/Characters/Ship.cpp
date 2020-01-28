//
//  Ship.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 16.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include "Ship.h"
#import "ParametricEquations.h"
#include "Common.h"

Ship::Ship()
{
    otype = OTHER;
    shape = SPHERE;
    ISurface *surface = new Sphere(1.5f);
    surface->SetVertexFlags(VertexFlagsNormals);
    initBuffer(surface);
    delete surface;

    //
    _position = {0.0f, 0.0f, -50.0f};
    _aabb._P = _position;
    _velocity = {0.0f, 0.0f, 0.0f};
    _direction = {0.0f, 0.0f, 0.0f};
    _acceleration = {1.0f, 1.0f, 1.0f};
    _mass = 100.0f;
    _r = {0.0f, 0.0f, 0.0f};
    _rotate = {0.0f, 0.0f, 90.0f};
    _energy = 3;

    _textureIndex = 0;
}

Ship::~Ship()
{
}

//void Ship::impactWith(DynamicObj *object)
//{
//}

void Ship::update()
{
    Vector<float> one = {1.0f, 0.0f, 0.0f};
    float dotProduct = one * _direction.Normalized();
    if (!isnan(dotProduct))
    {
        float angle = acosf(dotProduct) * 180 / M_PI;
        if (_direction.y > 0)
        {
            angle = 360.0f - angle;
        }
        _rotate = {0.0f, 0.0f, angle};
    }

    float d = sqrt(_direction.x*_direction.x + _direction.y*_direction.y + _direction.z*_direction.z);
    if (d != 0.0f)
    {
        Vector<float> velocity = {
            _direction.x/d,
            _direction.y/d,
            _direction.z/d};
        _velocity = _velocity + velocity/_mass;
    }
    else
    {
        _velocity = _velocity - _velocity/_mass;
    }

    _position += _velocity;

//    // Wrap around the edges of the screen ("toroid space")
//    if (_position.x > _glwidth)
//        _position.x = -_glwidth;
//    else if (_position.x < -_glwidth)
//        _position.x = _glwidth;
//    if (_position.y > _glheight)
//        _position.y = -_glheight;
//    else if (_position.y < -_glheight)
//        _position.y = _glheight;

    _aabb._P = _position;
}
