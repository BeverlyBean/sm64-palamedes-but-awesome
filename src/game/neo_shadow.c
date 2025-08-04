#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "actors/group0.h"
#include "rendering_graph_node.h"
#include "frame_lerp.h"
#include "memory.h"
#include "camera.h"
#include "object_list_processor.h"
#include "emutest.h"
#include "engine/surface_collision.h"
#include "neo_shadow.h"
#include "worldspace_visual_debug.h"
#include "segment2.h"

static const Vtx vertex_neo_shadow[] = {
    {{{    -1,      0,     -1}, 0, { -2048,  -2048}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     1,      0,     -1}, 0, {  2048,  -2048}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    -1,      0,      1}, 0, { -2048,   2048}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     1,      0,      1}, 0, {  2048,   2048}, {0xff, 0xff, 0xff, 0xff}}},
};

const Gfx dl_neo_shadow_mesh[] = {
    gsSPVertex(vertex_neo_shadow, 4, 0),
    gsSP2Triangles( 0,  2,  1, 0x0,  1,  2,  3, 0x0),
    gsSPEndDisplayList(),
};


#include "engine/math_util.h"

neoShadow sNeoShadowList[MAX_NEO_SHADOWS];

void neoshadow_cast(neoShadow * s, struct Object * obj) {
    struct Surface * floor;
    f32 h = find_floor(obj->oPosX,obj->oPosY+10.0f,obj->oPosZ,&floor);
    if (floor) {
        s->pos[0] = obj->oPosX;
        s->pos[1] = h;
        s->pos[2] = obj->oPosZ;
        s->normal[0] = floor->normal.x;
        s->normal[1] = floor->normal.y;
        s->normal[2] = floor->normal.z;
    }
}

void neoshadow_obj_create(struct Object * obj) {
    int i = 0;
    while (sNeoShadowList[i].initialized) {
        i++;
    }
    if (i >= MAX_NEO_SHADOWS) {
        return;
    }
    sNeoShadowList[i].owner = obj;
    neoshadow_cast(&sNeoShadowList[i],obj);
    vec3f_copy(sNeoShadowList[i].posLerp,sNeoShadowList[i].pos);
    sNeoShadowList[i].initialized = TRUE;
    obj->shadow = &sNeoShadowList[i];
}

void neoshadow_reset(void) {
    for (int i = 0; i < MAX_NEO_SHADOWS; i++) {
        sNeoShadowList[i].initialized = FALSE;
    }
}

int neoshadow_count(void) {
    int ct = 0;
    for (int i = 0; i < MAX_NEO_SHADOWS; i++) {
        if (sNeoShadowList[i].initialized) {
            ct++;
        }
    }
    return ct;
}

void neoshadow_render(void) {
    Gfx * dlh = alloc_display_list(sizeof(Gfx)* ((10*neoshadow_count())+10) );
    Gfx * dl = dlh;

    gSPDisplayList(dlh++,dl_shadow_circle);
    for (int i = 0; i < MAX_NEO_SHADOWS; i++) {
        neoShadow * s = &sNeoShadowList[i];
        if (s->initialized) {
            frameLerpPos(s->pos,s->posLerp);

            Mat4 shadowMat;
            Vec3f scale = {100.0f,100.0f,100.0f};
            mtxf_shadow(shadowMat,s->normal,s->posLerp,scale,0);

            Mtx *mtx = alloc_display_list(sizeof(*mtx));
            mtxf_to_mtx(mtx, shadowMat);

            gSPMatrix(dlh++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPDisplayList(dlh++,dl_neo_shadow_mesh);
        }
    }
    gSPEndDisplayList(dlh++);

    geo_append_display_list(dl, LAYER_TRANSPARENT_DECAL);
}

void neoshadow_logic(void) {
    for (int i = 0; i < MAX_NEO_SHADOWS; i++) {
        neoShadow * s = &sNeoShadowList[i];
        if (s->initialized) {
            struct Object * obj = s->owner;
            f32 dsqrd = sqr(obj->oPosX - s->pos[0]) + sqr(obj->oPosY - s->pos[1]) + sqr(obj->oPosZ - s->pos[2]);
            if (dsqrd <= 4000000.0f) {
                neoshadow_cast(s,obj);
            } else {
                if (s->ownerLastPos[0] != obj->oPosX || s->ownerLastPos[1] != obj->oPosZ) {
                    s->ownerLastPos[0] = obj->oPosX;
                    s->ownerLastPos[1] = obj->oPosZ;

                    neoshadow_cast(s,obj);
                }
            }
        }
    }
}