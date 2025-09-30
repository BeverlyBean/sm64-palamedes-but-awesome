#include "types.h"

#ifndef LEVEL_REGION_H
#define LEVEL_REGION_H

enum regionIds {
    REGION_COUNT
};

extern u32 gRegionFlags;
void region_logic(void);
void region_init_object(struct Object * obj);
Gfx *geo_region(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx);

#endif