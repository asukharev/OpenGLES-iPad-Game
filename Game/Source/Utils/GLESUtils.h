//
//  GLESUtils.h
//
//  Created by Alexander Sukharev on 25.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _GLESU_H
#define _GLESU_H

#include <OpenGLES/ES2/gl.h>
#include "GLESTexture.h"

extern GLuint _colorRenderBuffer;
extern GLuint _frameBuffer;
extern GLuint _depthRenderBuffer;

// Attribute and uniform slots
//
extern GLuint _programHandle;
extern GLuint _positionSlot;
extern GLuint _modelViewSlot;
extern GLuint _projectionSlot;

// For light
//
extern GLuint _normalMatrixSlot;
extern GLuint _lightPositionSlot;
extern GLint _normalSlot;
extern GLint _ambientSlot;
extern GLint _diffuseSlot;
extern GLint _specularSlot;
extern GLint _shininessSlot;

// For texture
//
extern unsigned int _textureCount;
extern GLuint *_textures;
extern GLint _textureCoordSlot;
extern GLint _samplerSlot;
extern GLint _wrapMode;
extern GLint _filterMode;

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */
    
    void glSetupBuffers();
    void glDestoryBuffers();
    void glCleanup();

    void glSetupTextures();
//    void setImageTexture(struct Texture *texture);
//    void deleteTexture(GLuint *textureHandle);
    void glDestoryTextures();
    
    void glSetupProgram();

//    GLuint glLoadShader(GLenum type, const char *name);
//    GLuint glLoadProgram(GLuint vertexShader, GLuint fragmentShader);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* defined(_GLESU_H) */
