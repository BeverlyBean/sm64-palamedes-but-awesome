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
Gfx * sNeoShadowTextures[NEOSHADOW_RENDER_PASS_CT] = {
    [NEOSHADOW_TYPE_CICRLE] = dl_shadow_circle,
    [NEOSHADOW_TYPE_SQUARE] = dl_shadow_square,
};

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

        f32 baseScale = (f32)s->baseScale;
        s->scale[0] = baseScale * obj->header.gfx.scale[0];
        s->scale[1] = baseScale * obj->header.gfx.scale[2];
    }
}

void neoshadow_obj_create(struct Object * obj, s16 scale, u8 type) {
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
    sNeoShadowList[i].baseScale = scale/2;
    sNeoShadowList[i].type = type;
    sNeoShadowList[i].yaw = 0;
    sNeoShadowList[i].overridden = FALSE;
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

    for (int j = 0; j < NEOSHADOW_RENDER_PASS_CT; j++) {
        gSPDisplayList(dlh++,sNeoShadowTextures[j]);
        for (int i = 0; i < MAX_NEO_SHADOWS; i++) {
            neoShadow * s = &sNeoShadowList[i];
            if (s->type == j && s->initialized) {
                frameLerpPos(s->pos,s->posLerp);
                s->scaleLerp[0] = frameLerpFloat(s->scale[0],s->scaleLerp[0]);
                s->scaleLerp[1] = frameLerpFloat(s->scale[1],s->scaleLerp[1]);
                s->yawLerp = frameLerpShort(s->yaw,s->yawLerp);

                Mat4 shadowMat;
                Vec3f scale = {s->scaleLerp[0],s->scaleLerp[0],s->scaleLerp[1]};
                mtxf_shadow(shadowMat,s->normal,s->posLerp,scale,s->yawLerp);

                Mtx *mtx = alloc_display_list(sizeof(*mtx));
                mtxf_to_mtx(mtx, shadowMat);

                gSPMatrix(dlh++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPDisplayList(dlh++,dl_neo_shadow_mesh);
            }
        }
    }
    gSPEndDisplayList(dlh++);

    geo_append_display_list(dl, LAYER_TRANSPARENT_DECAL);
}

void neoshadow_logic(void) {
    for (int i = 0; i < MAX_NEO_SHADOWS; i++) {
        neoShadow * s = &sNeoShadowList[i];
        if (s->initialized && !s->overridden) {
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