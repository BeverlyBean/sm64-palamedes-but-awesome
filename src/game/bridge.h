#include "sm64.h"
#include "types.h"
#include "src/engine/graph_node.h"

#ifndef BRIDGE_H
#define BRIDGE_H

void create_bridge(Collision * col);
void bridge_update(void);
Gfx *geo_vxit_bridge(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx);

#endif