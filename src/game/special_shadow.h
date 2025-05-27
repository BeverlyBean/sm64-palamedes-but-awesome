#include "types.h"
#include <PR/gbi.h>

#ifndef SPECIAL_SHADOW_H
#define SPECIAL_SHADOW_H

extern const Gfx dl_shadow_special[];
extern const Gfx dl_shadow_special_tri[];

typedef struct {
    Mat4 transform;
    Gfx * dl;
} SpecialShadowPart;

enum {
    SSP_HEAD,
    SSP_LEFT_FOOT,
    SSP_RIGHT_FOOT,

    SSP_LEFT_HAND,
    SSP_RIGHT_HAND,

    SSP_LEG_1_R,
    SSP_LEG_2_R,
    SSP_LEG_1_L,
    SSP_LEG_2_L,

    SSP_ARM_1_R,
    SSP_ARM_2_R,
    SSP_ARM_1_L,
    SSP_ARM_2_L,

    SSP_TORSO,

    SSP_COUNT,
};

extern u8 special_shadow_texture_rgba16[4096];
extern SpecialShadowPart gSpecialShadowPartList[SSP_COUNT];

void special_shadow_generate(void);
void special_shadow_update_part(int index, Mat4 partTransform);

#endif