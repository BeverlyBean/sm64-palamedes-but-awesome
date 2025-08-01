#include "coin.h"
#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "actors/group0.h"
#include "rendering_graph_node.h"
#include "frame_lerp.h"
#include "memory.h"
#include "camera.h"

u8 sCoinTexture[4096];
s16 sCoinAngle = 0;
Mat4 sCoinTransform;

Gfx sGfxLoadCoinTex[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, &sCoinTexture),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 2047, 128),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 124),
	gsSPEndDisplayList(),
};

#include "engine/math_util.h"

extern u8 dmaCoinTexture[];

coinObject coinList[MAX_COINS] = {
    {TRUE,{0,-1000,0}},
    {TRUE,{75,-1000,0}},
    {TRUE,{75*2,-1000,0}},
    {TRUE,{75*3,-1000,0}},
    {TRUE,{75*4,-1000,0}}
};

void coin_create(Vec3f pos) {
    int i = 0;
    while (coinList[i].initialized) {
        i++;
    }
    coinList[i].initialized = TRUE;
    vec3f_copy(coinList[i].pos,pos);
}

void coin_render(void) {
    Gfx * dlh = alloc_display_list((sizeof(Gfx)*3*10)+4);
    Gfx * dl = dlh;

    sCoinAngle += 0x800*gFrameLerpDeltaTime;

    Vec3s rotation = {0,sCoinAngle,0};
    Vec3f vz = {0,0,0};
    mtxf_rotate_zxy_and_translate(sCoinTransform,vz,rotation);

    s16 angle = abs_angle_diff(sCoinAngle,gLakituState.yaw);
    uintptr_t index = (angle/0x7FF)%32;
    dma_read(sCoinTexture,dmaCoinTexture+(index*4096),dmaCoinTexture+4096+(index*4096));


    gSPDisplayList(dlh++, sGfxLoadCoinTex);
    for (int i = 0; i < MAX_COINS; i++) {
        if (coinList[i].initialized) {
            Mtx *mtx = alloc_display_list(sizeof(*mtx));
            sCoinTransform[3][0] = coinList[i].pos[0];
            sCoinTransform[3][1] = coinList[i].pos[1];
            sCoinTransform[3][2] = coinList[i].pos[2];
            mtxf_to_mtx(mtx, sCoinTransform);

            gSPMatrix(dlh++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPDisplayList(dlh++,coin3D_Cylinder_mesh_tri_0);
        }
    }

    gSPEndDisplayList(dlh++);

    geo_append_display_list(dl, LAYER_OPAQUE);
}