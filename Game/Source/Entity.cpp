//
//  Entity.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 15.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include "Common.h"
#include "Entity.h"
#include "ParametricEquations.h"
#include "Vector.h"
#include "AABB.h"

void updateTextureParameter()
{
    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
}

void Entity::initBuffer(ISurface *surface)
{
    // Get vertice from surface.
    //
    _vertexSize = surface->GetVertexSize();
    int vertexCount = surface->GetVertexCount();
    int vBufSize = vertexCount * _vertexSize;
    GLfloat * vbuf = new GLfloat[vBufSize];
    surface->GenerateVertices(vbuf);

    // Get triangle indice from surface
    //
    _triangleIndexCount = surface->GetTriangleIndexCount();
    unsigned short * triangleBuf = new unsigned short[_triangleIndexCount];
    surface->GenerateTriangleIndices(triangleBuf);

    // Get line indice from surface
    //
    _lineIndexCount = surface->GetLineIndexCount();
    unsigned short * lineBuf = new unsigned short[_lineIndexCount];
    surface->GenerateLineIndices(lineBuf);

    // Create the VBO for the vertice.
    //
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vBufSize * sizeof(GLfloat), vbuf, GL_STATIC_DRAW);

    // Create the VBO for the line indice
    //
    glGenBuffers(1, &_lineIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _lineIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _lineIndexCount * sizeof(GLushort), lineBuf, GL_STATIC_DRAW);

    // Create the VBO for the triangle indice
    //
    glGenBuffers(1, &_triangleIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _triangleIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _triangleIndexCount * sizeof(GLushort), triangleBuf, GL_STATIC_DRAW);

    _aabb = cdAABB(vbuf, vertexCount, _vertexSize, _scale);

    delete [] vbuf;
    delete [] lineBuf;
    delete [] triangleBuf;
}

Entity::Entity()
{
}

Entity::~Entity()
{
    if (_vertexBuffer != 0)
    {
        glDeleteBuffers(1, &_vertexBuffer);
        _vertexBuffer = 0;
    }

    if (_lineIndexBuffer != 0)
    {
        glDeleteBuffers(1, &_lineIndexBuffer);
        _lineIndexBuffer = 0;
    }

    if (_triangleIndexBuffer)
    {
        glDeleteBuffers(1, &_triangleIndexBuffer);
        _triangleIndexBuffer = 0;
    }
}

void Entity::draw()
{
    int stride = _vertexSize * sizeof(GLfloat);
    const GLvoid* normalOffset = (const GLvoid*)(3 * sizeof(GLfloat));
    const GLvoid* texCoordOffset = (const GLvoid*)(6 * sizeof(GLfloat));

    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, GL_FALSE, stride, 0);
    glVertexAttribPointer(_normalSlot, 3, GL_FLOAT, GL_FALSE, stride, normalOffset);
    glVertexAttribPointer(_textureCoordSlot, 2, GL_FLOAT, GL_FALSE, stride, texCoordOffset);

    glEnableVertexAttribArray(_positionSlot);
}

void Entity::wire()
{
    draw();

    // Draw the black lines.
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _lineIndexBuffer);
    glDrawElements(GL_LINES, _lineIndexCount, GL_UNSIGNED_SHORT, 0);
    glDisableVertexAttribArray(_positionSlot);
}

void Entity::solid()
{
    draw();

    // Draw the red triangles.
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _triangleIndexBuffer);
    glDrawElements(GL_TRIANGLES, _triangleIndexCount, GL_UNSIGNED_SHORT, 0);
    glDisableVertexAttribArray(_positionSlot);
}

void Entity::point()
{
    draw();

    // Draw the black lines.
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _lineIndexBuffer);
    glDrawElements(GL_POINTS, _lineIndexCount, GL_UNSIGNED_SHORT, 0);
    glDisableVertexAttribArray(_positionSlot);
}

void Entity::transform()
{
    KSMatrix4 shouldModelViewMatrix;
    ksMatrixLoadIdentity(&shouldModelViewMatrix);

    ksTranslate(&shouldModelViewMatrix, _position.x, _position.y, _position.z);

    // Rotate
    //
    ksRotate(&shouldModelViewMatrix, _rotate.x, 0.1, 0.0, 0.0);
    ksRotate(&shouldModelViewMatrix, _rotate.y, 0.0, 1.0, 0.0);
    ksRotate(&shouldModelViewMatrix, _rotate.z, 0.0, 0.0, 1.0);

    // Scale the cube to be a shoulder
    //
    ksCopyMatrix4(&_modelViewMatrix, &shouldModelViewMatrix);
    ksScale(&_modelViewMatrix, 1, 1, 1);

    // Load the model-view matrix
    glUniformMatrix4fv(_modelViewSlot, 1, GL_FALSE, (GLfloat*)&_modelViewMatrix.m[0][0]);

    // Load the normal matrix.
    KSMatrix3 normalMatrix3;
    ksMatrix4ToMatrix3(&normalMatrix3, &_modelViewMatrix);
    glUniformMatrix3fv(_normalMatrixSlot, 1, GL_FALSE, (GLfloat*)&normalMatrix3.m[0][0]);

    // Update textures for stage 0
    //
    if (_textures != NULL)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _textures[_textureIndex]);
        updateTextureParameter();
    }
}
