#ifndef GLOBALS_H
#define GLOBALS_H
#include <math.h>

#include "raylib.h"
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n)                          \
    if (!(n)) {                            \
        printf("%s -Failed \n", #n);       \
        printf("On %s \n", __DATE__);      \
        printf("At %s \n", __TIME__);      \
        printf("In File %s \n", __FILE__); \
        printf("At Line %d \n", __LINE__); \
        exit(1);                           \
    }
#endif
#pragma once
#define SCREENWIDTH 600
#define SCREENHEIGHT 600
const float Pi = 3.14f;
const float DELTA_T = 0.04f;
const float GRAVITY = 9.8f;
extern void Zoom();
#endif
