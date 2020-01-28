//
//  Ship.h
//  Asteroids
//
//  Created by Alexander Sukharev on 16.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _SHIP_HPP
#define _SHIP_HPP

#include "Entity.h"

class Ship : public Entity
{
public:
	Ship();
	~Ship();

    void update();
//    void impactWith(DynamicObj *object);
};

#endif /* defined(_SHIP_HPP) */
