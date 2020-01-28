//
//  GLESUtils.cpp
//
//  Created by Alexander Sukharev on 25.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include <stdlib.h>
#include "GLESUtils.h"
#include "Utils.h"

GLuint _colorRenderBuffer;
GLuint _frameBuffer;
GLuint _depthRenderBuffer;

// Attribute and uniform slots
//
GLuint _programHandle;
GLuint _positionSlot;
GLuint _modelViewSlot;
GLuint _projectionSlot;

// For light
//
GLuint _normalMatrixSlot;
GLuint _lightPositionSlot;
GLint _normalSlot;
GLint _ambientSlot;
GLint _diffuseSlot;
GLint _specularSlot;
GLint _shininessSlot;

// For texture
//
unsigned int _textureCount;
GLuint *_textures;
GLint _textureCoordSlot;
GLint _samplerSlot;
GLint _wrapMode;
GLint _filterMode;

GLuint glLoadShader(GLenum type, const char *name) {
    // Create the shader object
    GLuint shader = glCreateShader(type);
    if (shader == 0) {
        errlog("Error: failed to create shader", "");
        return 0;
    }

    const char *code = readFile(name);
    // Load the shader source
    //const char * shaderStringUTF8 = [shaderString UTF8String];
    //glShaderSource(shader, 1, &shaderStringUTF8, NULL);
    glShaderSource(shader, 1, &code, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char *infoLog = (char *)malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            errlog("Error compiling shader", infoLog);
            free(infoLog);
        }

        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

GLuint glLoadProgram(GLuint vertexShader, GLuint fragmentShader) {
    // Create the program object
    GLuint programHandle = glCreateProgram();
    if (programHandle == 0)
        return 0;

    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);

    // Link the program
    glLinkProgram(programHandle);

    // Check the link status
    GLint linked;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linked);

    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char *infoLog = (char *)malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(programHandle, infoLen, NULL, infoLog);
            errlog("Error linking program", infoLog);
            free(infoLog);
        }

        glDeleteProgram(programHandle );
        return 0;
    }

    // Free up no longer needed shader resources
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return programHandle;
}

void glSetupProgram() {
    const char *vertexShaderFilename = "VertexShader.glsl";
    GLuint vertexShader = glLoadShader(GL_VERTEX_SHADER, vertexShaderFilename);
    if (vertexShader == 0)
        return;

    const char *fragmentShaderFilename = "FragmentShader.glsl";
    GLuint fragmentShader = glLoadShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);
    if (fragmentShader == 0) {
        glDeleteShader(vertexShader);
        return;
    }

    _programHandle = glLoadProgram(vertexShader, fragmentShader);

    if (_programHandle == 0)
    {
        errlog("Error load program", "");
        return;
    }

    glUseProgram(_programHandle);

    // Get the attribute and uniform slot from program
    //
    _projectionSlot = glGetUniformLocation(_programHandle, "projection");
    _modelViewSlot = glGetUniformLocation(_programHandle, "modelView");
    _normalMatrixSlot = glGetUniformLocation(_programHandle, "normalMatrix");
    _lightPositionSlot = glGetUniformLocation(_programHandle, "vLightPosition");
    _ambientSlot = glGetUniformLocation(_programHandle, "vAmbientMaterial");
    _specularSlot = glGetUniformLocation(_programHandle, "vSpecularMaterial");
    _shininessSlot = glGetUniformLocation(_programHandle, "shininess");
    _positionSlot = glGetAttribLocation(_programHandle, "vPosition");
    _normalSlot = glGetAttribLocation(_programHandle, "vNormal");
    _diffuseSlot = glGetAttribLocation(_programHandle, "vDiffuseMaterial");
    _textureCoordSlot = glGetAttribLocation(_programHandle, "vTextureCoord");
    _samplerSlot = glGetUniformLocation(_programHandle, "Sampler");
}

void glSetupBuffers() {
    // Setup color render buffer
    //
//    glGenRenderbuffers(1, &_colorRenderBuffer);
//    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, _wwidth, _wheight);

    // Setup depth render buffer
    //
    int width, height;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height);

    // Create a depth buffer that has the same size as the color buffer.
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);

    // Setup frame buffer
    //
    glGenFramebuffers(1, &_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

    // Attach color render buffer and depth render buffer to frameBuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER, _colorRenderBuffer);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, _depthRenderBuffer);

    // Set color render buffer as current render buffer
    //
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
}

void glDestoryBuffer(GLuint *buffer) {
    if (buffer && *buffer != 0) {
        glDeleteRenderbuffers(1, buffer);
        *buffer = 0;
    }
}

void glDestoryBuffers() {
    glDestoryBuffer(&_depthRenderBuffer);
    glDestoryBuffer(&_colorRenderBuffer);
    glDestoryBuffer(&_frameBuffer);
}

void glCleanup() {
    glDestoryTextures();
    glDestoryBuffers();

    if (_programHandle != 0)
    {
        glDeleteProgram(_programHandle);
        _programHandle = 0;
    }

//    if (_context && [EAGLContext currentContext] == _context)
//    {
//        [EAGLContext setCurrentContext:nil];
//    }
//
//    _context = nil;
}

void glSetupTextures() {
    const char *textureFiles[] = {"gray256.png", "test256.png", "test320.png"};

    _textureCount = 2;
    _textures = new GLuint[_textureCount];

    // Set the active sampler to stage 0.
    // Not really necessary since the uniform defaults to zero anyway, but good practice.
    //
	glActiveTexture(GL_TEXTURE0);

    for (int i = 0; i < _textureCount; i++) {
        const char *filename = textureFiles[i];
        const char *filepath = filePath(filename);
        _textures[i] = createTexture(filepath);
    }

    glEnableVertexAttribArray(_textureCoordSlot);
    glUniform1i(_samplerSlot, 0);
}

void glDestoryTextures() {
    if (_textures != NULL)
    {
        for (int i = 0; i < _textureCount; i++)
        {
            deleteTexture(&_textures[i]);
        }
        delete [] _textures;
        _textures = NULL;
    }
}
