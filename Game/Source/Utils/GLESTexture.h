//
//  GLESTexture.h
//  Asteroids
//
//  Created by Alexander Sukharev on 26.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _GLESTEXTURE_H
#define _GLESTEXTURE_H

#include <OpenGLES/ES2/gl.h>

typedef enum TextureFormat {
    TextureFormatGray,
    TextureFormatGrayAlpha,
    TextureFormatRGB,
    TextureFormatRGBA,
    TextureFormatPvrtcRgb2,
    TextureFormatPvrtcRgba2,
    TextureFormatPvrtcRgb4,
    TextureFormatPvrtcRgba4,
    TextureFormat565,
    TextureFormat5551,
} TextureFormat;

GLuint createTexture(const char *filepath);
void deleteTexture(GLuint *textureHandle);

#endif /* defined(_GLESTEXTURE_H) */
