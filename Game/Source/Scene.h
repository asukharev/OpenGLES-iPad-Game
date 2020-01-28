//
//  Scene.h
//  Asteroids
//
//  Created by Alexander Sukharev on 15.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _SCENE_HPP
#define _SCENE_HPP

#include "GLESMath.h"

class Game;

class Scene
{
protected:
    KSMatrix4 _projectionMatrix;

public:
	Scene(Game *game);
	virtual ~Scene() {}

    void render();
    void rotate(KSVec3 dir);
    void move(KSVec3 dir);
};

#endif /* defined(_SCENE_HPP) */
