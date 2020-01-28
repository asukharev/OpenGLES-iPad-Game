#ifndef _COMMON_H
#define _COMMON_H

#include <time.h>

#include "GLESUtils.h"

// Window
extern float _waspect;
extern GLsizei _wwidth;
extern GLsizei _wheight;
extern double _wscale;

extern GLsizei _glwidth;
extern GLsizei _glheight;

// Global time
extern time_t _time;

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

    void initGame();
    void timerCallback();
    void render();

    void leftStick(float x, float y);
    void rightStick(float x, float y);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif
