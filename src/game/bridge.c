#include "types.h"
#include "src/engine/surface_load.h"
#include "game_init.h"
#include "src/engine/math_util.h"
#include "src/engine/graph_node.h"
#include "vertex_iterator.h"

Collision * bridgeCollision = NULL;

void create_bridge(Collision * col) {
    bridgeCollision = col;
}

void generate_bridge_vertex(Vec3s out, Vec3s in) {
    Vec3f pos;
    vec3s_to_vec3f(pos,in);

    out[0] = in[0];
    out[1] = in[1] + sins((pos[0]*0x200)+(gGlobalTimer*0x400))* 100.0f;
    out[2] = in[2];
}

void bridge_update(void) {
    if (bridgeCollision != NULL) {
        load_collision_custom_transform(bridgeCollision,&generate_bridge_vertex);
    }
}

void vxit_update_vtx_list_bridge(Vtx * vertices, int size) {
    for (int i = 0; i < size; i++) {
        vertices[i].v.ob[1] = curr_vxit_dl->addr[vxit_vertex_index].position[1] + sins((vertices[i].v.ob[0]*0x200)+(gGlobalTimer*0x400))* 100.0f;
        vxit_vertex_index++;
    }
}

Gfx *geo_vxit_bridge(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    struct GraphNodeGenerated * self = (struct GraphNodeGenerated *)node;
    if (callContext == GEO_CONTEXT_AREA_LOAD) {
        struct GraphNodeDisplayList * dl = (struct GraphNodeDisplayList *)node->next;
        self->iteratorID = vxit_add_dl_to_iterator(dl->displayList, &vxit_update_vtx_list_bridge, node);
    }
    if (callContext == GEO_CONTEXT_RENDER) {
        vxit_iterate_dl(self->iteratorID);
    }
    return NULL;
}