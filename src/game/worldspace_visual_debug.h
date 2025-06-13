#include "types.h"

#ifndef WORLDSPACE_VISUAL_DEBUG_H
#define WORLDSPACE_VISUAL_DEBUG_H

typedef struct {
    Mat4 transform;
    u8 flags;
} debugTransform;

#define WSVD_ACTIVE  (1<<0)
#define WSVD_THREAD5 (1<<1)
#define WSVD_CUBE    (1<<2)

#define MAX_DEBUG_TRANSFORMS 30

void render_worldspace_visual_debug(void);

debugTransform * debug_pos(Vec3f pos);
debugTransform * debug_mtxf(Mat4 mat);

#endif