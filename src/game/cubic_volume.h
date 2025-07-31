#ifndef CUBIC_VOLUME_H
#define CUBIC_VOLUME_H

#include "sm64.h"
#include "types.h"

#define CUBIC_VOLUME_MAX 30

typedef struct {
    Vec3f pos;
    Vec3f scale;
    Quat rot;
} CubicVolume;

enum {
    VOLUME_TYPE_REGION,
    VOLUME_TYPE_SHADOW,
    VOLUME_TYPE_MUSIC,
    VOLUME_TYPE_BRIDGE
};

CubicVolume * cubic_volume_add(void);

#endif