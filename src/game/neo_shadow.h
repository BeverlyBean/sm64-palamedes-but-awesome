#include "sm64.h"
#include "types.h"

#ifndef NEO_SHADOW_H
#define NEO_SHADOW_H

#define MAX_NEO_SHADOWS 240

enum {
    NEOSHADOW_TYPE_CICRLE,
    NEOSHADOW_TYPE_SQUARE,
    NEOSHADOW_RENDER_PASS_CT,
};

typedef struct {
    u8 initialized:1;
    u8 overridden:1;
    u8 type:6;

    struct Object * owner;
    f32 ownerLastPos[2];
    Vec3f pos;
    Vec3f posLerp;
    Vec3f normal;

    s16 baseScale;
    f32 scale[2];
    f32 scaleLerp[2];

    s16 yaw;
    s16 yawLerp;
} neoShadow;

void neoshadow_obj_create(struct Object * obj, s16 scale, u8 type);
void neoshadow_reset(void);
void neoshadow_render(void);
void neoshadow_logic(void);

void neoshadow_cast(neoShadow * s, struct Object * obj);

#endif