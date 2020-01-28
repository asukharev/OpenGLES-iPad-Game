//
//  Entity.h
//  Asteroids
//
//  Created by Alexander Sukharev on 15.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include "DynamicObj.h"
#include "GLESMath.h"

class ISurface;

class Entity : public DynamicObj
{
private:
    int _vertexSize;
    int _triangleIndexCount;
    int _lineIndexCount;
    GLuint _vertexBuffer;
    GLuint _triangleIndexBuffer;
    GLuint _lineIndexBuffer;

    void draw();

protected:
    GLuint _textureIndex;
    KSMatrix4 _modelViewMatrix;
    void initBuffer(ISurface *surface);

public:
    Entity();
    virtual ~Entity();

    /* Apply the transformations for this entity. */
    virtual void transform();

    /* Draw a solid version of this entity. */
    void solid();

    /* Draw a wire version of this entity. */
    void wire();

    void point();
};

#endif /* defined(_ENTITY_HPP) */
