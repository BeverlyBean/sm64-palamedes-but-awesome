#include "sm64.h"
#include "game_init.h"
#include "level_region.h"
#include "src/engine/graph_node.h"
#include "cubic_volume.h"
#include "level_update.h"


u32 gRegionFlags = 0;
struct Object * sRegionObject = NULL;

void region_flag_volume(CubicVolume * v) {
    gRegionFlags |= (1 << v->param);
}

void region_flag_object(CubicVolume * v) {
    sRegionObject->regionFlags |= (1 << v->param);
}

void region_init_object(struct Object * obj) {
    sRegionObject = obj;

    obj->regionFlags = 0;
    cubic_volume_check_all(&obj->oPosVec,VOLUME_TYPE_REGION,region_flag_object);
}

void region_logic(void) {
    gRegionFlags = 0;
    cubic_volume_check_all(gMarioState->pos,VOLUME_TYPE_REGION,region_flag_volume);

    debug_u32(&gRegionFlags,"Region flags");
}

Gfx *geo_region(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    struct GraphNodeGenerated * self = (struct GraphNodeGenerated *)node;
    struct GraphNodeDisplayList * dl = (struct GraphNodeDisplayList *)node->next;

    if (callContext == GEO_CONTEXT_AREA_LOAD) {
        self->dlCopy = dl->displayList;
    }
    if (callContext == GEO_CONTEXT_RENDER) {
        if (gRegionFlags & (1 << self->parameter)) {
            dl->displayList = self->dlCopy;
        } else {
            dl->displayList = NULL;
        }
    }
    return NULL;
}

Gfx *geo_region_lod(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    struct GraphNodeGenerated * self = (struct GraphNodeGenerated *)node;
    struct GraphNodeDisplayList * dl = (struct GraphNodeDisplayList *)node->next;

    if (callContext == GEO_CONTEXT_AREA_LOAD) {
        self->dlCopy = dl->displayList;
    }
    if (callContext == GEO_CONTEXT_RENDER) {
        if (gRegionFlags & (1 << self->parameter)) {
            dl->displayList = NULL;
        } else {
            dl->displayList = self->dlCopy;
        }
    }
    return NULL;
}