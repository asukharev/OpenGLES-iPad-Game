//
//  Asteroid.h
//  Asteroids
//
//  Created by Alexander Sukharev on 15.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _ASTEROID_HPP
#define _ASTEROID_HPP

#include "Entity.h"

class DynamicObj;

class Asteroid : public Entity
{
    void init(int i, float r);

public:
    float _radius;

	Asteroid(int i);
	Asteroid(const Entity &old, bool second=false);
	~Asteroid();

    void update();
};

#endif /* defined(_ASTEROID_HPP) */
