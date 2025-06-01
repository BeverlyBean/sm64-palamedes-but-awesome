#include "sm64.h"
#include "types.h"
#include "src/engine/graph_node.h"

#ifndef BRIDGE_H
#define BRIDGE_H

#define ROPE_GRAVITY 10.0f
#define ROPE_STRENGTH 0.9f
#define ROPE_DAMPING 0.49f

typedef struct {
    f32 y;
    f32 yCol;
    f32 yGfx;
    f32 yVel;
    u8 pinned;
    Vec3f worldPos;
} BridgeJoint;

typedef struct {
    int startJointIndex;
    int size;
    Collision * collision;
} Bridge;

void create_bridge(Collision * col, Vec3f start, Vec3f end, int size);
void bridge_update(void);
Gfx *geo_vxit_bridge(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx);
void bridge_update_joint_gfx_positions(void);
void bridge_reset(void);

#endif