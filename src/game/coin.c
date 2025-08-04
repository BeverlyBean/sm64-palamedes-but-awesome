#include "coin.h"
#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "actors/group0.h"
#include "rendering_graph_node.h"
#include "frame_lerp.h"
#include "memory.h"
#include "camera.h"
#include "object_list_processor.h"
#include "emutest.h"
#include "neo_shadow.h"

u8 sCoinTexture[4096];
s16 sCoinAngle = 0;
Mat4 sCoinTransform;

Gfx sGfxLoadCoinTex[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT, ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 1, &sCoinTexture),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 2047, 256),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 252),
	gsSPEndDisplayList(),
};

#include "engine/math_util.h"

extern u8 dmaCoinTexture[];

coinObject coinList[MAX_COINS];

void coin_obj_create(int type) {
    int i = 0;
    while (coinList[i].initialized) {
        i++;
    }
    if (i >= MAX_COINS) {
        return;
    }
    coinList[i].obj = o;
    coinList[i].type = type;
    o->oCoinObjectPtr = &coinList[i];
    coinList[i].initialized = TRUE;

    if (o->shadow == NULL) {
        neoshadow_obj_create(o);
    }
}

void coin_obj_destroy(struct Object * owner) {
    coinObject * myCoin = owner->oCoinObjectPtr;
    if (myCoin != NULL) {
        myCoin->initialized = FALSE;
        owner->oCoinObjectPtr = NULL;
    }
}

void coin_reset(void) {
    for (int i = 0; i < MAX_COINS; i++) {
        coinList[i].initialized = FALSE;
    }
}

int coin_count(void) {
    int ct = 0;
    for (int i = 0; i < MAX_COINS; i++) {
        if (coinList[i].initialized) {
            ct++;
        }
    }
    return ct;
}

void coin_render(void) {
    Gfx * dlh = alloc_display_list(sizeof(Gfx)* ((10*coin_count())+10) );
    Gfx * dl = dlh;

    sCoinAngle += 0x800*gFrameLerpDeltaTime;
    if (sCoinAngle > 0x4000) {
        sCoinAngle -= 0x8000;
    }

    Vec3s rotation = {0,sCoinAngle+gLakituState.yaw,0};
    Vec3f vz = {0,0,0};
    mtxf_rotate_zxy_and_translate(sCoinTransform,vz,rotation);

    u16 angle = sCoinAngle+0x2000;
    uintptr_t size = 4096;
    uintptr_t index = (angle/(0x7FF))%32;
    dma_read(sCoinTexture,dmaCoinTexture+(index*size),dmaCoinTexture+size+(index*size));

    gSPDisplayList(dlh++, sGfxLoadCoinTex);
    for (int j = 0; j < 3; j++) {
        switch(j) {
            case 0:
                gDPSetEnvColor(dlh++,255,220,15,255);
                break;
            case 1:
                gDPSetEnvColor(dlh++,255,40,40,255);
                break;
            case 2:
                gDPSetEnvColor(dlh++,60,30,255,255);
                //scale
                for (int i = 0; i < 9; i++) {
                    u8 r = i%3;
                    u8 c = i/3;
                    sCoinTransform[c][r] *= 1.5f;
                }
                break;
        }
        for (int i = 0; i < MAX_COINS; i++) {
            if (coinList[i].type == j && coinList[i].initialized && (!(coinList[i].obj->header.gfx.node.flags & GRAPH_RENDER_INVISIBLE)) ) {
                Vec3f pos; vec3f_copy(pos,coinList[i].obj->header.gfx.posLerp);
                f32 dsqrd = sqr(gLakituState.pos[0] - pos[0]) + sqr(gLakituState.pos[1] - pos[1]) + sqr(gLakituState.pos[2] - pos[2]);
                Gfx * mesh = coin3Dhi_CylinderHi_mesh_tri_0;
                if ((gEmulator & (EMU_CONSOLE|EMU_ARES)) && dsqrd >= 4000000.0f) { // farther than 2000.0f
                    mesh = coin3D_Cylinder_mesh_tri_0;
                }

                Mtx *mtx = alloc_display_list(sizeof(*mtx));
                sCoinTransform[3][0] = pos[0];
                sCoinTransform[3][1] = pos[1];
                sCoinTransform[3][2] = pos[2];
                mtxf_to_mtx(mtx, sCoinTransform);

                gSPMatrix(dlh++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPDisplayList(dlh++,mesh);
            }
        }
    }
    gSPEndDisplayList(dlh++);

    geo_append_display_list(dl, LAYER_OPAQUE);
}