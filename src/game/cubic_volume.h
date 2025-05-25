#ifndef CUBIC_VOLUME_H
#define CUBIC_VOLUME_H

#include "sm64.h"
#include "types.h"

typedef struct {
    Vec3f pos;
    Vec3f scale;
    Quat rot;
} CubicVolume;

extern CubicVolume testVolume;

s32 point_inside_volume(Vec3f p, CubicVolume * v);

#endif