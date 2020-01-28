//
//  Scene.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 26.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include "Scene.h"
#include "Common.h"
#include "Game.h"

KSMatrix4 _projectionMatrix;

Scene::Scene(Game *game) {
    // Load projection matrix
    ksMatrixLoadIdentity(&_projectionMatrix);
//    ksPerspective(&_projectionMatrix, 45.0, _waspect, 0.1f, 600.0f);
    ksFrustum(&_projectionMatrix, -5, 5, -5/_waspect, 5/_waspect, 5.0f, 6000.0f);
    glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, (GLfloat*)&_projectionMatrix.m[0][0]);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // Set up some default material parameters.
    //
    glUniform3f(_ambientSlot, 0.04f, 0.04f, 0.04f);
    glUniform3f(_specularSlot, 0.5f, 0.5f, 0.5f);
    glUniform1f(_shininessSlot, 50.0f);
    glEnableVertexAttribArray(_positionSlot);
    glEnableVertexAttribArray(_normalSlot);
    glUniform3f(_lightPositionSlot, 1.0f, 1.0f, 5.0f);
    glVertexAttrib3f(_diffuseSlot, 0.8f, 0.8f, 0.8f);

    // Setup viewport
    //
    glViewport(0, 0, _wwidth, _wheight);
}

void Scene::render() {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::rotate(KSVec3 dir) {
    ksRotate(&_projectionMatrix, dir.x/10.0f, 0, -1, 0);
    ksRotate(&_projectionMatrix, dir.y/10.0f, -1, 0, 0);
//    ksRotate(&_projectionMatrix, dir.z, 0, 0, 1);
    glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, (GLfloat*)&_projectionMatrix.m[0][0]);
}

void Scene::move(KSVec3 dir) {
    ksTranslate(&_projectionMatrix, -dir.x/10.0f, 0.0f, -dir.y/10.0f);
    glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, (GLfloat*)&_projectionMatrix.m[0][0]);
    glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, (GLfloat*)&_projectionMatrix.m[0][0]);
}
