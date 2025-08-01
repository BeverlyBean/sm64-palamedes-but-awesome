#include "sm64.h"

#ifndef COIN_H
#define COIN_H

#define MAX_COINS 100

typedef struct {
    u8 initialized;
    Vec3f pos;
} coinObject;

void coin_render(void);
void coin_create(Vec3f pos);

#endif