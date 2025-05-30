#include "types.h"
#include "src/engine/surface_load.h"
#include "game_init.h"
#include "src/engine/math_util.h"
#include "src/engine/graph_node.h"
#include "vertex_iterator.h"
#include "bridge.h"
#include "level_update.h"
#include "frame_lerp.h"

Bridge bridgePool[5];
int sBridgeCount = 0;
BridgeJoint bridgeJointPool[40];
int sBridgeJointCount = 0;

void create_bridge(Collision * col, Vec3f start, Vec3f end, int size) {
    Bridge * b = &bridgePool[sBridgeCount];
    b->startJointIndex = sBridgeJointCount;
    b->collision = col;
    b->size = size;

    for (int i = 0; i < b->size; i++) {
        BridgeJoint * joint = &bridgeJointPool[sBridgeJointCount];

        if (i==0 || i ==b->size-1) {
            joint->pinned = TRUE;
        } else {
            joint->pinned = FALSE;
        }
        joint->y = 0.0f;
        joint->yCol = 0.0f;
        joint->yVel = 0.0f;
        f32 f = (f32)i/(f32)(b->size-1);
        for (int j = 0; j < 3; j++) {
            joint->worldPos[j] = approach_f32_asymptotic(start[j],end[j],f);
        }

        sBridgeJointCount++;
    }

    sBridgeCount++;
}

int spawnedcounter = 0;

BridgeJoint * bridge_nearest_joint(Vec3f checkPos) {
    BridgeJoint * nearestJoint = NULL;
    f32 sd = 99999999999.0f;

    spawnedcounter++;

    for (int i = 0; i < sBridgeJointCount; i++) {
        BridgeJoint * joint = &bridgeJointPool[i];

        f32 d = sqr(checkPos[0] - joint->worldPos[0]) + sqr(checkPos[2] - joint->worldPos[2]);
        if (d < sd) {
            sd = d;
            nearestJoint = joint;
        }
    }
    return nearestJoint;
}

void bridge_update_joint_gfx_positions(void) {
    for (int i = 0; i < sBridgeJointCount; i++) {
        BridgeJoint * joint = &bridgeJointPool[i];
        joint->yGfx = frameLerpFloat(joint->y, joint->yGfx);
    }
}

void generate_bridge_vertex(Vec3s out, Vec3s in) {
    Vec3f pos;
    vec3s_to_vec3f(pos,in);

    BridgeJoint * myJoint = bridge_nearest_joint(pos);

    out[0] = in[0];
    out[1] = in[1] + myJoint->yCol;
    out[2] = in[2];
}

void bridge_update(void) {

    for (int i = 0; i < sBridgeCount; i++) {
        Bridge * b = &bridgePool[i];

        Vec3f point1; vec3f_copy(point1, bridgeJointPool[b->startJointIndex].worldPos); 
        Vec3f point2; vec3f_copy(point2, bridgeJointPool[b->startJointIndex+b->size-1].worldPos); 

        Vec3f pointProjection;
        f32 bridgeProgress = vec3f_project_to_line(pointProjection,gMarioState->pos,point1,point2);

        int bridgeProgressIndex = (int)(bridgeProgress*(f32)b->size);
        f32 weightRight = (bridgeProgress*(f32)b->size) - (int)(bridgeProgress*(f32)b->size);
        f32 weightLeft = 1.0f - weightRight;

        if ((gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_STATIONARY || (gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_MOVING) {
            if (gMarioState->action == ACT_GROUND_POUND_LAND) {
                weightRight *= 2.0f;
                weightLeft *= 2.0f;
            }
            bridgeJointPool[b->startJointIndex+bridgeProgressIndex].yVel -= 100.0f*weightLeft;
            bridgeJointPool[b->startJointIndex+bridgeProgressIndex+1].yVel -= 100.0f*weightRight;
        }

        for (int j = 0; j < b->size; j++) {
            BridgeJoint * joint = &bridgeJointPool[b->startJointIndex+j];
            joint->yCol = joint->y; //frame of delay for collision for better syncing with the GFX

            if (!joint->pinned) {
                BridgeJoint * prev = &bridgeJointPool[b->startJointIndex+j-1];
                BridgeJoint * next = &bridgeJointPool[b->startJointIndex+j+1];

                // Gravity
                joint->yVel -= ROPE_GRAVITY;

                f32 offset;
                // Solving joints in a random order allegedly stabilizes a physics simulation,
                // or so I've been told.
                if (random_u16()%2==0) {
                    // Constraint next
                    offset = prev->y - joint->y;
                    joint->yVel += offset * ROPE_STRENGTH;

                    // Constraint previous
                    offset = next->y - joint->y;
                    joint->yVel += offset * ROPE_STRENGTH;
                } else {
                    // Constraint previous
                    offset = next->y - joint->y;
                    joint->yVel += offset * ROPE_STRENGTH;

                    // Constraint next
                    offset = prev->y - joint->y;
                    joint->yVel += offset * ROPE_STRENGTH;
                }

                joint->yVel -= (joint->yVel * ROPE_DAMPING); // Damping
                joint->y += CLAMP(joint->yVel,-40.0f,40.0f);

                // I hate to castrate the fun bridge physics, but if it goes too fast mario will clip through
            }
        }

        load_collision_custom_transform(b->collision,&generate_bridge_vertex);
    }
}

void vxit_update_vtx_list_bridge(Vtx * vertices, int size) {
    for (int i = 0; i < size; i++) {
        BridgeJoint * myJoint = curr_vxit_dl->addr[vxit_vertex_index].pointer;
        if (myJoint == NULL) {
            curr_vxit_dl->addr[vxit_vertex_index].pointer = bridge_nearest_joint(curr_vxit_dl->addr[vxit_vertex_index].position);
            myJoint = curr_vxit_dl->addr[vxit_vertex_index].pointer;
        }

        vertices[i].v.ob[1] = curr_vxit_dl->addr[vxit_vertex_index].position[1] + myJoint->yGfx;
        vxit_vertex_index++;
    }
}

Gfx *geo_vxit_bridge(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    struct GraphNodeGenerated * nodeGen = (struct GraphNodeGenerated *)node;
    struct GraphNodeDisplayList * dl = (struct GraphNodeDisplayList *)node->next;

    if (callContext == GEO_CONTEXT_AREA_LOAD) {
        nodeGen->iteratorID = vxit_add_dl_to_iterator(dl->displayList, &vxit_update_vtx_list_bridge, node);
    }
    if (callContext == GEO_CONTEXT_RENDER) {
        dl->displayList = vxit_iterate_dl(nodeGen->iteratorID);
    }
    return NULL;
}