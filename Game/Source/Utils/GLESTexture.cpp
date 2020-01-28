//
//  GLESTexture.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 26.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include <stdlib.h>
#include "GLESTexture.h"
#include "Utils.h"

#define PNG_DEBUG 3
#define PNG_BYTES_TO_CHECK 8
#include "png.h"

struct Texture {
    GLsizei width;
    GLsizei height;
    GLubyte color_type;
    GLubyte bit_depth;
    png_bytep *row_pointers;
};

struct Texture * loadTexture(const char *filepath) {
    png_byte pngsig[PNG_BYTES_TO_CHECK];

    /* open file and test for it being a png */
    FILE *fp = fopen(filepath, "rb");
    if (!fp)
    {
        errlog("File could not be opened for reading", filepath);
    }
    fread(&pngsig, 1, PNG_BYTES_TO_CHECK, fp);
    if (png_sig_cmp(pngsig, (png_size_t)0, PNG_BYTES_TO_CHECK))
    {
        errlog("File is not recognized as a PNG file", filepath);
    }

    /* initialize stuff */
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr;

    if (!png_ptr)
        errlog("png_create_read_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        errlog("png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        errlog("Error during init_io");

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    Texture *texture = (struct Texture *)malloc(sizeof(struct Texture));
    texture->width = png_get_image_width(png_ptr, info_ptr);
    texture->height = png_get_image_height(png_ptr, info_ptr);
    texture->color_type = png_get_color_type(png_ptr, info_ptr);
    texture->bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    png_read_update_info(png_ptr, info_ptr);

    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
        errlog("Error during read_image");

    texture->row_pointers = (png_bytep *)malloc(sizeof(png_bytep)*texture->height);
    int y;
    for (y = 0; y < texture->height; y++)
        texture->row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));

    png_read_image(png_ptr, texture->row_pointers);

    fclose(fp);

    return texture;
}

void unloadTexture(struct Texture *texture) {
    free(texture->row_pointers);
    free(texture);
}

void setTextureParameter() {
    // It can be GL_NICEST or GL_FASTEST or GL_DONT_CARE. GL_DONT_CARE by default.
    //
    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void setImageTexture(Texture *texture)
{
    GLenum format = 0;
    switch (texture->color_type) {
        case PNG_COLOR_TYPE_GRAY:
            format = GL_LUMINANCE;
            break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            format = GL_LUMINANCE_ALPHA;
            break;
        case PNG_COLOR_TYPE_RGB:
            format = GL_RGB;
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            format = GL_RGBA;
            break;

        default:
            errlog("Invalid texture format!");
            break;
    }

    GLenum type = 0;
    int bitsPerComponent = texture->bit_depth;
    switch (bitsPerComponent) {
        case 8:
            type = GL_UNSIGNED_BYTE;
            break;
        case 4:
            if (format == GL_RGBA) {
                type = GL_UNSIGNED_SHORT_4_4_4_4;
                break;
            }
            // fall through
        default:
            errlog("Invalid texture format!");
            break;
    }

    void *pixels = texture->row_pointers;
    GLsizei width = texture->width;
    GLsizei height = texture->height;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
}

GLuint createTexture(const char *filepath) {
    Texture *texture = loadTexture(filepath);
    GLuint textureHandle = 0;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    setTextureParameter();
    setImageTexture(texture);
    unloadTexture(texture);
    return textureHandle;
}

void deleteTexture(GLuint *textureHandle) {
    if (*textureHandle != 0) {
        glDeleteTextures(1, textureHandle);
        *textureHandle = 0;
    }
}
