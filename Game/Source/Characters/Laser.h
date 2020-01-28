//
//  Laser.h
//  Asteroids
//
//  Created by Alexander Sukharev on 18.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _LASER_HPP
#define _LASER_HPP

#include "Entity.h"

class Laser : public Entity
{
public:
    int _lifetime;

    Laser(Vector<float> position, Vector<float> direction, Vector<float> svelocity);
	~Laser();

    void update();
    bool isAlive();
//    void impactWith(DynamicObj *object);
};

#endif /* defined(_LASER_HPP) */
