//
//  Utils.h
//  Asteroids
//
//  Created by Alexander Sukharev on 26.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _UTILS_H
#define _UTILS_H

float rando(float lo, float hi);
void errlog(const char* description, const char *info = "");
char * filePath(const char *filename);
char * readFile(const char *fileName);

#endif /* defined(_UTILS_H) */
