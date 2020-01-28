//
//  DynamicObj.h
//  Asteroids
//
//  Created by Alexander Sukharev on 19.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _DynamicObj_H
#define _DynamicObj_H

#include "Vector.h"
#include "AABB.h"
#include "Common.h"

class DynamicObj
{
private:

protected:
    bool _isAlive = true;

    // Shape used for collision detection
	enum Shape {
		NONE = 0,
        POINT,
        SPHERE,
        POLYGON
	} shape;

public:
    enum Type {
		AST = 0,
        ROCK = 1,
        OTHER
	} otype;

    int _id;

    unsigned long _energy;
    time_t _ctime;
    float _mass = 0.0f;
    Vector<float> _position;
    Vector<float> _direction;
    Vector<float> _r; /* rotational velocity */
    Vector<float> _rotate;
    Vector<float> _velocity;
    Vector<float> _acceleration;

    cdAABB _aabb;
    Vector<float> _scale;

    DynamicObj();
    virtual ~DynamicObj();

    virtual void update() = 0;
    virtual void impactWith(DynamicObj *object);
    virtual void drainEnergy(unsigned long e);
    virtual bool isAlive();
};

#endif /* defined(_DynamicObj_H) */
