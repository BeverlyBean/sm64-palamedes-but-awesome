#include "types.h"

#ifndef DEBUG_TRACKER_H
#define DEBUG_TRACKER_H

#define MAX_DEBUG_TRACKERS 10

enum {
    TRACKER_TYPE_U32,
    TRACKER_TYPE_S32,
    TRACKER_TYPE_U8,
    TRACKER_TYPE_S8,
    TRACKER_TYPE_S16,
    TRACKER_TYPE_F32,
    TRACKER_TYPE_V3F,
};

struct TrackedValue {
    u8 initialized;
    u8 type;
    char * label;
    void * value;
};

void debug_s32(s32 * value, char * label);
void debug_u32(u32 * value, char * label);
void debug_s16(s16 * value, char * label);
void debug_f32(f32 * value, char * label);
void debug_vec3f(Vec3f * value, char * label);
void debug_tracker_render(void);

#endif