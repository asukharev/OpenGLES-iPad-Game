//
//  Common.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 15.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include <stdlib.h>
#include "Common.h"
#include "Game.h"
#include "Scene.h"
#include "Vector.h"
#include "GLESMath.h"

float _waspect;
GLsizei _wwidth;
GLsizei _wheight;
double _wscale;

GLsizei _glwidth;
GLsizei _glheight;

time_t _time;

static Scene *scene;
static Game *game;

void initGame() {
    if (game == NULL)
    {
        srand((unsigned)time(0));
        game = new Game(1, 0, 0);
        scene = new Scene(game);
    }
}

void timerCallback() {
    game->timer(0);
}

void render() {
    scene->render();
    game->display();
}

#pragma mark - Joystick

void leftStick(float x, float y) {
    KSVec3 dir = {x, y};
    scene->move(dir);
//    Vector2<float> dir = {x, y};
//    game->setDirection(dir);
}

void rightStick(float x, float y) {
    KSVec3 dir = {x, y};
    scene->rotate(dir);
//    Vector2<float> dir = {x, y};
//    game->fire(dir);
}
