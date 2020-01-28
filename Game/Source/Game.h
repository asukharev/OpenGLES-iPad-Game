//
//  Game.h
//  Asteroids
//
//  Created by Alexander Sukharev on 15.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _GAME_HPP
#define _GAME_HPP

#include "Vector.h"

class Entity;

class Game
{
private:
    bool active;

    Entity **entity;

    /* entity ranges */
	static const int ship_slot = 0; /* just one ship */
	static const int laser = 1; /* maximum of (aLaser - laser) lasers... 4 in this case */
	static const int aLaser = 5;
	static const int ast = 6; /* maximum of (end - ast) asteroids */
	int end;	 /* end of entities... one past the last entity */
	int n_ast; /* number of initial asteroids */
	int level;
	long score;

    static const int RECHARGE = 7;
	int _recharge;

    void collision(int i, int j);

public:
	Game(int level, int lives, long score);
	~Game();

    virtual void display();
    virtual void timer(int value);

    void fire(ivec2 dir);
    void setDirection(ivec2 dir);
};

#endif /* defined(_GAME_HPP) */
