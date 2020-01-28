//
//  Asteroid.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 15.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include "Asteroid.h"
#import "ParametricEquations.h"
#include "Common.h"
#include "Utils.h"

void Asteroid::init(int i, float r)
{
    _radius = r; //rando(3.0f, 4.0f);
    shape = SPHERE;
    otype = AST;
    ISurface *surface = new Sphere(_radius);
    surface->SetVertexFlags(VertexFlagsNormals);
    initBuffer(surface);
    delete surface;

    _id = i;

    //
    _position = {-_glwidth + i*8, rando(-_glheight, _glheight), -10.0f};
    _aabb._P = _position;
    _velocity = {rando(-.5f, .5f), 0.0f, rando(-.5f, 0.0f)};
    _direction = {0.0f, 0.0f, 0.0f};
    _acceleration = {1.0f, 1.0f, 0.0f};
    _mass = _radius * 100.0f;
    _r = {rando(-1.0f, 1.0f), rando(-1.0f, 1.0f), 0.0f};
    _energy = 4;
    
    _textureIndex = 1;
}

Asteroid::Asteroid(int i)
{
    init(i, 5.0f);
}

Asteroid::Asteroid(const Entity &old, bool second)
{
    init(old._id, 1.5f);
    otype = ROCK;
    _energy = 2.0f;
    _position = old._position;
    update();
}

Asteroid::~Asteroid()
{
}

void Asteroid::update()
{
    _rotate += _r;
    if (_rotate.x >= MAX_DEGREE)
        _rotate.x -= MAX_DEGREE;
    if (_rotate.y >= MAX_DEGREE)
        _rotate.y -= MAX_DEGREE;
    if (_rotate.z >= MAX_DEGREE)
        _rotate.z -= MAX_DEGREE;

//    _velocity = _velocity - _velocity/_mass;

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
