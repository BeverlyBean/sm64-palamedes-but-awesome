#include "sm64.h"

#ifndef COIN_H
#define COIN_H

#define MAX_COINS 300

typedef struct {
    u8 initialized;
    u8 type;
    struct Object * obj;
} coinObject;

void coin_render(void);
void coin_logic(void);
void coin_reset(void);

void coin_obj_create(int type);
void coin_obj_destroy(struct Object * owner);

#endif