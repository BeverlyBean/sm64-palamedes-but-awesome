#include "sm64.h"
#include "types.h"

#ifndef NEO_SHADOW_H
#define NEO_SHADOW_H

#define MAX_NEO_SHADOWS 240

typedef struct {
    u8 initialized;
    u8 type;
    struct Object * owner;
    f32 ownerLastPos[2];
    Vec3f pos;
    Vec3f posLerp;
    Vec3f normal;
} neoShadow;

void neoshadow_obj_create(struct Object * obj);
void neoshadow_reset(void);
void neoshadow_render(void);
void neoshadow_logic(void);

#endif