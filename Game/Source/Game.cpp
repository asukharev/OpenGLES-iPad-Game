//
//  Game.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 15.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include "Game.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Laser.h"
#include "AABB.h"
#include "Terrain.h"

unsigned int _score;
unsigned int _lives;

Game::Game(int level, int lives, long score)
{
    _glwidth = 40.0f;
    _glheight = _glwidth / _waspect;
	_recharge = 0;
    _score = score;
    _lives = lives;

	n_ast = 6; /* 6 maximum asteroids */
	end = ast + n_ast * 5; /* a large asteroid can break into 4 small, plus explosion */
	entity = new Entity *[end];

    Terrain *terra = new Terrain();

    entity[ship_slot] = new Ship();

    int i;
	for (i = laser; i < ast; i++)
    {
		entity[i] = NULL;
	}
	for (i = ast; i < ast + n_ast; i++)
    {
		entity[i] = new Asteroid(i);
	}
	for (i = ast + n_ast; i < end; i++)
    {
		entity[i] = NULL;
	}

    active = true;
}

Game::~Game()
{
    int i;
	for (i = 0; i < end; i++)
    {
		if (entity[i])
        {
			delete entity[i];
        }
    }
	delete [] entity;

	active = false;
}

void Game::display()
{
    int i;
	for (i = 0; i < end; i++)
    {
		if (entity[i])
        {
			entity[i]->transform();
			entity[i]->solid();
			//entity[i]->wire();
            //entity[i]->point();
		}
	}
}

void Game::collision(int i, int j)
{
    Entity *a = entity[i], *b = entity[j];

    // Prevent laser and ship to collide
    //
    if ((i == ship_slot && (j >= laser && j < laser+aLaser)) ||
        (j == ship_slot && (i >= laser && j < laser+aLaser)))
    {
        return;
    }

    if (a->isAlive() && b->isAlive())
    {
        bool overlapse = a->_aabb.OverlapsAABB(b->_aabb);
        if (overlapse)
        {
            // Physics behaviour
            //
            a->impactWith(b);

            // Collision behaviours
            //
            if (i >= laser && i < aLaser && j >= ast && j < end)
            {
                b->drainEnergy(a->_energy); // laser effect on ast

                if (b->otype == 0 && !b->isAlive()) // explode
                {
                    int slot;
                    for (slot = 0; slot < 2; slot++)
                    {
                        int k;
                        for (k = ast; k < end; k++)
                        {
                            if (entity[k] == NULL)
                            {
                                break;
                            }
                        }
                        bool second = (slot > 0);
                        entity[k] = new Asteroid(*b, second);
                    }
                }

                if (!b->isAlive())
                {
                    delete b;
                    entity[j] = NULL;
                    _score++;
                }
                if (!a->isAlive())
                {
                    delete a;
                    entity[i] = NULL;
                }
            }
            else if (i == ship_slot && j >= ast && j < end)
            {
                float ae = a->_energy;
                float be = b->_energy;
                b->drainEnergy(ae); // ast effect on ship
                a->drainEnergy(be); // ship effect on ast

                if (b->otype == 0 && !b->isAlive()) // collide with big ast
                {
                    int slot;
                    for (slot = 0; slot < 2; slot++)
                    {
                        int k;
                        for (k = ast; k < end; k++)
                        {
                            if (entity[k] == NULL)
                            {
                                break;
                            }
                        }
                        bool second = (slot > 0);
                        entity[k] = new Asteroid(*b, second);
                    }
                }

                if (!b->isAlive())
                {
                    delete b;
                    entity[j] = NULL;
                    _score++;
                }

                if (!a->isAlive())
                {
                    delete a;
                    entity[i] = NULL;
                    _lives++;
                }
            }
            else if (i == ship_slot && j == aLaser)
            {
            }
        }
    }
}

void Game::timer(int value)
{
    if (active == false)
    {
        return;
    }

    time(&_time);

    int i;

    /* garbage collect dead entities */
//	gc = true;
	for (i = 0; i < end; i++)
    {
		if (entity[i])
        {
			if (!entity[i]->isAlive())
            {
				delete entity[i];
				entity[i] = NULL;
//				j++;
			}
		}
        else
        {
//			j++;
		}
	}
//	gc = false;

    for (i = 0; i < end; i++)
    {
		if (entity[i])
        {
            entity[i]->update();
			int k;
			for (k = i+1; k < end; k++)
            {
				if (entity[k] && entity[i])
                {
                    collision(i, k);
				}
			}
		}
	}

    // Recreate ship
    if (entity[ship_slot] == NULL)
    {
        delete entity[ship_slot];
        entity[ship_slot] = new Ship();
    }
}

void Game::fire(ivec2 dir)
{
    Entity *ship = entity[ship_slot];
    if (ship == NULL)
    {
        return;
    }

    int i, ok = 0;

	if (_recharge <= 0)
    {
		_recharge = RECHARGE;
		for (i = laser; i < ast; i++)
        {
			if (entity[i])
            {
				if (!entity[i]->isAlive())
                {
					delete entity[i];
					entity[i] = NULL;
					ok = 1;
					break;
				}
			}
            else
            {
				ok = 1;
				break;
			}
		}
		if (ok)
        {
            Vector<float> dir3 = {dir.x, -dir.y, 0.0f};
            entity[i] = new Laser(ship->_position, dir3, ship->_velocity);
		}
	}
    else
    {
		_recharge--;
    }
}

void Game::setDirection(ivec2 dir)
{
    Entity *ship = entity[ship_slot];
    if (ship != NULL)
    {
        ship->_direction = {dir.x, -dir.y, 0.0f};
    }
}
