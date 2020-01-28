//
//  Terrain.h
//  Asteroids
//
//  Created by Alexander Sukharev on 27.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "Entity.h"

class Terrain : public Entity {
public:
    Terrain();

    void update();
    bool isAlive();
};

#endif /* defined(__Asteroids__Terrain__) */
