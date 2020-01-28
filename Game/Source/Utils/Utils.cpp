//
//  Utils.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 26.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
//#include <dirent.h>
#include <math.h>

#include "Utils.h"

char * filePath(const char *filename) {
    const char *home = getenv("HOME");
    const char *subdir;

#ifdef __IPHONE_5_0
    subdir = "/OpenGL.app/";
#endif

    char *filepath = (char *)malloc(strlen(home)+strlen(subdir)+strlen(filename)+1);
    strcpy(filepath, home);
    strcat(filepath, subdir);
    strcat(filepath, filename);

    return filepath;
}

char * readFile(const char *filename)
{
    //    DIR *dir;
    //    struct dirent *ent;
    //    if ((dir = opendir(fullpath)) != NULL) {
    //        /* print all the files and directories within directory */
    //        while ((ent = readdir (dir)) != NULL) {
    //            printf ("%s\n", ent->d_name);
    //        }
    //        closedir (dir);
    //    } else {
    //        /* could not open directory */
    //        perror ("");
    ////        return EXIT_FAILURE;
    //    }

    char *filepath = filePath(filename);

    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        errlog(filepath);
        free(filepath);
        return NULL; //could not open file
    }

    struct stat filestat;
    if (stat(filepath, &filestat) != 0)
    {
        free(filepath);
        return NULL;
    }
    free(filepath);

    char *code = (char *)malloc(filestat.st_size);

    size_t n = 0;
    int c;
    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
    }

    // don't forget to terminate with the null character
    code[n] = '\0';

    return code;
}

float rando(float lo, float hi) {
	float r = fabs(hi - lo);
	float s = (lo < hi) ? lo : hi;
	return (((float)rand() / (float)RAND_MAX) * r + s);
}

void errlog(const char* description, const char *info)
{
    perror(description);
    printf("%s", info);
}
