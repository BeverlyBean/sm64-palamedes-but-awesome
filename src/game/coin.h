#include "sm64.h"

#ifndef COIN_H
#define COIN_H

#define MAX_COINS 100

typedef struct {
    u8 initialized;
    u8 type;
    Vec3f pos;
} coinObject;

void coin_render(void);
void coin_reset(void);

void coin_obj_update(void);
void coin_obj_create(void);
void coin_obj_destroy(void);

#endif