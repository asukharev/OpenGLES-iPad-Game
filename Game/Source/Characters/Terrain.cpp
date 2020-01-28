//
//  Terrain.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 27.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include "Terrain.h"
#include "perlin.h"

#include <stdio.h>

Terrain::Terrain() {
    float M[32][48];
    unsigned int W[32][48];
    unsigned int n = 1536;	// number of elements

    // generate map
    Perlin *perlin = new Perlin(4,4,1,94);
    int x, y;
    for (x = 0; x < 32; x++)
    {
        for (y = 0; y < 48; y++)
        {
            float value = perlin->Get((1.0/32.0)*x, (1.0/48.0)*y);
            M[x][y] = value;// * 255;
        }
    }

//    // Get vertice from surface.
//    //
//    _vertexSize = surface->GetVertexSize();
//    int vertexCount = surface->GetVertexCount();
//    int vBufSize = vertexCount * _vertexSize;
//    GLfloat * vbuf = new GLfloat[vBufSize];
//    surface->GenerateVertices(vbuf);
//
//    // Get triangle indice from surface
//    //
//    _triangleIndexCount = surface->GetTriangleIndexCount();
//    unsigned short * triangleBuf = new unsigned short[_triangleIndexCount];
//    surface->GenerateTriangleIndices(triangleBuf);
//
//    // Get line indice from surface
//    //
//    _lineIndexCount = surface->GetLineIndexCount();
//    unsigned short * lineBuf = new unsigned short[_lineIndexCount];
//    surface->GenerateLineIndices(lineBuf);
//
//    // Create the VBO for the vertice.
//    //
//    glGenBuffers(1, &_vertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, vBufSize * sizeof(GLfloat), vbuf, GL_STATIC_DRAW);
//
//    // Create the VBO for the line indice
//    //
//    glGenBuffers(1, &_lineIndexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _lineIndexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _lineIndexCount * sizeof(GLushort), lineBuf, GL_STATIC_DRAW);
//
//    // Create the VBO for the triangle indice
//    //
//    glGenBuffers(1, &_triangleIndexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _triangleIndexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _triangleIndexCount * sizeof(GLushort), triangleBuf, GL_STATIC_DRAW);
//
//    _aabb = cdAABB(vbuf, vertexCount, _vertexSize, _scale);
//
//    delete [] vbuf;
//    delete [] lineBuf;
//    delete [] triangleBuf;
//
//    otype = OTHER;
//    shape = SPHERE;
//
//    //
//    _position = {0.0f, 0.0f, -50.0f};
//    _aabb._P = _position;
//    _velocity = {0.0f, 0.0f, 0.0f};
//    _direction = {0.0f, 0.0f, 0.0f};
//    _acceleration = {1.0f, 1.0f, 1.0f};
//    _mass = 100.0f;
//    _r = {0.0f, 0.0f, 0.0f};
//    _rotate = {0.0f, 0.0f, 90.0f};
//    _energy = 3;
//
//    _textureIndex = 0;
}

void Terrain::update() {

}

bool Terrain::isAlive() {
    return true;
}
