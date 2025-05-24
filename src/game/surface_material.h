#ifndef SURFACE_MATERIAL_H
#define SURFACE_MATERIAL_H

#include <PR/ultratypes.h>
#include "types.h"

#define SURFMAT_STONE (0 << 12)
#define SURFMAT_GRASS (1 << 12)
#define SURFMAT_SAND (2 << 12)
#define SURFMAT_SNOW (3 << 12)
#define SURFMAT_WOOD (4 << 12)

typedef struct {
    u32 sound;
} SurfaceMaterial;

extern SurfaceMaterial * surfaceMaterialList[];

#endif