#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <PR/os_thread.h>

#include "engine/math_util.h"
#include "worldspace_visual_debug.h"
#include "game_init.h"
#include "rendering_graph_node.h"
#include "main.h"

Vtx transform_gimbal_mesh_vtx_0[30] = {
	{{ {0, 0, 101}, 0, {533, 75}, {0, 0, 127, 255} }},
	{{ {0, 10, 81}, 0, {624, -16}, {0, 116, 205, 255} }},
	{{ {-10, 0, 81}, 0, {368, -16}, {140, 0, 205, 255} }},
	{{ {0, 0, 101}, 0, {459, 75}, {0, 0, 127, 255} }},
	{{ {0, -10, 81}, 0, {368, 240}, {0, 140, 205, 255} }},
	{{ {0, 0, 101}, 0, {533, 149}, {0, 0, 127, 255} }},
	{{ {10, 0, 81}, 0, {624, 240}, {116, 0, 205, 255} }},
	{{ {-4, 0, 81}, 0, {368, 960}, {129, 0, 0, 255} }},
	{{ {0, 4, 81}, 0, {624, 960}, {0, 127, 0, 255} }},
	{{ {0, 4, 8}, 0, {624, 752}, {0, 127, 0, 255} }},
	{{ {-4, 0, 8}, 0, {368, 752}, {129, 0, 0, 255} }},
	{{ {-4, 0, 8}, 0, {112, 496}, {129, 0, 0, 255} }},
	{{ {0, -4, 81}, 0, {368, 288}, {0, 129, 0, 255} }},
	{{ {-4, 0, 81}, 0, {112, 288}, {129, 0, 0, 255} }},
	{{ {0, -4, 8}, 0, {368, 496}, {0, 129, 0, 255} }},
	{{ {4, 0, 81}, 0, {624, 288}, {127, 0, 0, 255} }},
	{{ {4, 0, 8}, 0, {624, 496}, {127, 0, 0, 255} }},
	{{ {0, 4, 81}, 0, {880, 288}, {0, 127, 0, 255} }},
	{{ {0, 4, 8}, 0, {880, 496}, {0, 127, 0, 255} }},
	{{ {-4, 0, 81}, 0, {112, 288}, {0, 0, 129, 255} }},
	{{ {-10, 0, 81}, 0, {112, 240}, {140, 0, 205, 255} }},
	{{ {0, -4, 81}, 0, {368, 288}, {0, 0, 129, 255} }},
	{{ {4, 0, 81}, 0, {624, 288}, {0, 0, 129, 255} }},
	{{ {0, 10, 81}, 0, {880, 240}, {0, 116, 205, 255} }},
	{{ {0, 4, 81}, 0, {880, 288}, {0, 0, 129, 255} }},
	{{ {0, 0, 101}, 0, {459, 149}, {0, 0, 127, 255} }},
	{{ {-10, 0, 81}, 0, {368, 1008}, {140, 0, 205, 255} }},
	{{ {0, 10, 81}, 0, {624, 1008}, {0, 116, 205, 255} }},
	{{ {0, 4, 81}, 0, {624, 960}, {0, 0, 129, 255} }},
	{{ {-4, 0, 81}, 0, {368, 960}, {0, 0, 129, 255} }},
};

Gfx transform_gimbal_mesh_tri_0[] = {
	gsSPVertex(transform_gimbal_mesh_vtx_0 + 0, 30, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 2, 4, 0),
	gsSP2Triangles(5, 6, 1, 0, 7, 8, 9, 0),
	gsSP2Triangles(7, 9, 10, 0, 11, 12, 13, 0),
	gsSP2Triangles(11, 14, 12, 0, 14, 15, 12, 0),
	gsSP2Triangles(14, 16, 15, 0, 16, 17, 15, 0),
	gsSP2Triangles(16, 18, 17, 0, 19, 4, 20, 0),
	gsSP2Triangles(19, 21, 4, 0, 21, 6, 4, 0),
	gsSP2Triangles(21, 22, 6, 0, 22, 23, 6, 0),
	gsSP2Triangles(22, 24, 23, 0, 25, 4, 6, 0),
	gsSP2Triangles(26, 27, 28, 0, 26, 28, 29, 0),
	gsSPEndDisplayList(),
};

Vtx transform_gimbal_mesh_vtx_1[30] = {
	{{ {101, 0, 0}, 0, {533, 75}, {127, 0, 0, 255} }},
	{{ {81, 10, 0}, 0, {624, -16}, {205, 116, 0, 255} }},
	{{ {81, 0, 10}, 0, {368, -16}, {205, 0, 116, 255} }},
	{{ {101, 0, 0}, 0, {459, 75}, {127, 0, 0, 255} }},
	{{ {81, -10, 0}, 0, {368, 240}, {205, 140, 0, 255} }},
	{{ {101, 0, 0}, 0, {533, 149}, {127, 0, 0, 255} }},
	{{ {81, 0, -10}, 0, {624, 240}, {205, 0, 140, 255} }},
	{{ {81, 0, 4}, 0, {368, 960}, {0, 0, 127, 255} }},
	{{ {81, 4, 0}, 0, {624, 960}, {0, 127, 0, 255} }},
	{{ {8, 4, 0}, 0, {624, 752}, {0, 127, 0, 255} }},
	{{ {8, 0, 4}, 0, {368, 752}, {0, 0, 127, 255} }},
	{{ {8, 0, 4}, 0, {112, 496}, {0, 0, 127, 255} }},
	{{ {81, -4, 0}, 0, {368, 288}, {0, 129, 0, 255} }},
	{{ {81, 0, 4}, 0, {112, 288}, {0, 0, 127, 255} }},
	{{ {8, -4, 0}, 0, {368, 496}, {0, 129, 0, 255} }},
	{{ {81, 0, -4}, 0, {624, 288}, {0, 0, 129, 255} }},
	{{ {8, 0, -4}, 0, {624, 496}, {0, 0, 129, 255} }},
	{{ {81, 4, 0}, 0, {880, 288}, {0, 127, 0, 255} }},
	{{ {8, 4, 0}, 0, {880, 496}, {0, 127, 0, 255} }},
	{{ {81, 0, 4}, 0, {112, 288}, {129, 0, 0, 255} }},
	{{ {81, 0, 10}, 0, {112, 240}, {205, 0, 116, 255} }},
	{{ {81, -4, 0}, 0, {368, 288}, {129, 0, 0, 255} }},
	{{ {81, 0, -4}, 0, {624, 288}, {129, 0, 0, 255} }},
	{{ {81, 10, 0}, 0, {880, 240}, {205, 116, 0, 255} }},
	{{ {81, 4, 0}, 0, {880, 288}, {129, 0, 0, 255} }},
	{{ {101, 0, 0}, 0, {459, 149}, {127, 0, 0, 255} }},
	{{ {81, 0, 10}, 0, {368, 1008}, {205, 0, 116, 255} }},
	{{ {81, 10, 0}, 0, {624, 1008}, {205, 116, 0, 255} }},
	{{ {81, 4, 0}, 0, {624, 960}, {129, 0, 0, 255} }},
	{{ {81, 0, 4}, 0, {368, 960}, {129, 0, 0, 255} }},
};

Gfx transform_gimbal_mesh_tri_1[] = {
	gsSPVertex(transform_gimbal_mesh_vtx_1 + 0, 30, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 2, 4, 0),
	gsSP2Triangles(5, 6, 1, 0, 7, 8, 9, 0),
	gsSP2Triangles(7, 9, 10, 0, 11, 12, 13, 0),
	gsSP2Triangles(11, 14, 12, 0, 14, 15, 12, 0),
	gsSP2Triangles(14, 16, 15, 0, 16, 17, 15, 0),
	gsSP2Triangles(16, 18, 17, 0, 19, 4, 20, 0),
	gsSP2Triangles(19, 21, 4, 0, 21, 6, 4, 0),
	gsSP2Triangles(21, 22, 6, 0, 22, 23, 6, 0),
	gsSP2Triangles(22, 24, 23, 0, 25, 4, 6, 0),
	gsSP2Triangles(26, 27, 28, 0, 26, 28, 29, 0),
	gsSPEndDisplayList(),
};

Vtx transform_gimbal_mesh_vtx_2[30] = {
	{{ {0, 101, 0}, 0, {533, 75}, {0, 127, 0, 255} }},
	{{ {-10, 81, 0}, 0, {624, -16}, {140, 205, 0, 255} }},
	{{ {0, 81, 10}, 0, {368, -16}, {0, 205, 116, 255} }},
	{{ {0, 101, 0}, 0, {459, 75}, {0, 127, 0, 255} }},
	{{ {10, 81, 0}, 0, {368, 240}, {116, 205, 0, 255} }},
	{{ {0, 101, 0}, 0, {533, 149}, {0, 127, 0, 255} }},
	{{ {0, 81, -10}, 0, {624, 240}, {0, 205, 140, 255} }},
	{{ {0, 81, 4}, 0, {368, 960}, {0, 0, 127, 255} }},
	{{ {-4, 81, 0}, 0, {624, 960}, {129, 0, 0, 255} }},
	{{ {-4, 8, 0}, 0, {624, 752}, {129, 0, 0, 255} }},
	{{ {0, 8, 4}, 0, {368, 752}, {0, 0, 127, 255} }},
	{{ {0, 8, 4}, 0, {112, 496}, {0, 0, 127, 255} }},
	{{ {4, 81, 0}, 0, {368, 288}, {127, 0, 0, 255} }},
	{{ {0, 81, 4}, 0, {112, 288}, {0, 0, 127, 255} }},
	{{ {4, 8, 0}, 0, {368, 496}, {127, 0, 0, 255} }},
	{{ {0, 81, -4}, 0, {624, 288}, {0, 0, 129, 255} }},
	{{ {0, 8, -4}, 0, {624, 496}, {0, 0, 129, 255} }},
	{{ {-4, 81, 0}, 0, {880, 288}, {129, 0, 0, 255} }},
	{{ {-4, 8, 0}, 0, {880, 496}, {129, 0, 0, 255} }},
	{{ {0, 81, 4}, 0, {112, 288}, {0, 129, 0, 255} }},
	{{ {0, 81, 10}, 0, {112, 240}, {0, 205, 116, 255} }},
	{{ {4, 81, 0}, 0, {368, 288}, {0, 129, 0, 255} }},
	{{ {0, 81, -4}, 0, {624, 288}, {0, 129, 0, 255} }},
	{{ {-10, 81, 0}, 0, {880, 240}, {140, 205, 0, 255} }},
	{{ {-4, 81, 0}, 0, {880, 288}, {0, 129, 0, 255} }},
	{{ {0, 101, 0}, 0, {459, 149}, {0, 127, 0, 255} }},
	{{ {0, 81, 10}, 0, {368, 1008}, {0, 205, 116, 255} }},
	{{ {-10, 81, 0}, 0, {624, 1008}, {140, 205, 0, 255} }},
	{{ {-4, 81, 0}, 0, {624, 960}, {0, 129, 0, 255} }},
	{{ {0, 81, 4}, 0, {368, 960}, {0, 129, 0, 255} }},
};

Gfx transform_gimbal_mesh_tri_2[] = {
	gsSPVertex(transform_gimbal_mesh_vtx_2 + 0, 30, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 2, 4, 0),
	gsSP2Triangles(5, 6, 1, 0, 7, 8, 9, 0),
	gsSP2Triangles(7, 9, 10, 0, 11, 12, 13, 0),
	gsSP2Triangles(11, 14, 12, 0, 14, 15, 12, 0),
	gsSP2Triangles(14, 16, 15, 0, 16, 17, 15, 0),
	gsSP2Triangles(16, 18, 17, 0, 19, 4, 20, 0),
	gsSP2Triangles(19, 21, 4, 0, 21, 6, 4, 0),
	gsSP2Triangles(21, 22, 6, 0, 22, 23, 6, 0),
	gsSP2Triangles(22, 24, 23, 0, 25, 4, 6, 0),
	gsSP2Triangles(26, 27, 28, 0, 26, 28, 29, 0),
	gsSPEndDisplayList(),
};

Vtx transform_gimbal_mesh_vtx_3[24] = {
	{{ {-8, -8, 8}, 0, {368, 1008}, {129, 0, 0, 255} }},
	{{ {-8, 8, 8}, 0, {624, 1008}, {129, 0, 0, 255} }},
	{{ {-8, 8, -8}, 0, {624, 752}, {129, 0, 0, 255} }},
	{{ {-8, -8, -8}, 0, {368, 752}, {129, 0, 0, 255} }},
	{{ {-8, -8, -8}, 0, {368, 752}, {0, 0, 129, 255} }},
	{{ {-8, 8, -8}, 0, {624, 752}, {0, 0, 129, 255} }},
	{{ {8, 8, -8}, 0, {624, 496}, {0, 0, 129, 255} }},
	{{ {8, -8, -8}, 0, {368, 496}, {0, 0, 129, 255} }},
	{{ {8, -8, -8}, 0, {368, 496}, {127, 0, 0, 255} }},
	{{ {8, 8, -8}, 0, {624, 496}, {127, 0, 0, 255} }},
	{{ {8, 8, 8}, 0, {624, 240}, {127, 0, 0, 255} }},
	{{ {8, -8, 8}, 0, {368, 240}, {127, 0, 0, 255} }},
	{{ {8, -8, 8}, 0, {368, 240}, {0, 0, 127, 255} }},
	{{ {8, 8, 8}, 0, {624, 240}, {0, 0, 127, 255} }},
	{{ {-8, 8, 8}, 0, {624, -16}, {0, 0, 127, 255} }},
	{{ {-8, -8, 8}, 0, {368, -16}, {0, 0, 127, 255} }},
	{{ {-8, -8, -8}, 0, {112, 496}, {0, 129, 0, 255} }},
	{{ {8, -8, -8}, 0, {368, 496}, {0, 129, 0, 255} }},
	{{ {8, -8, 8}, 0, {368, 240}, {0, 129, 0, 255} }},
	{{ {-8, -8, 8}, 0, {112, 240}, {0, 129, 0, 255} }},
	{{ {8, 8, -8}, 0, {624, 496}, {0, 127, 0, 255} }},
	{{ {-8, 8, -8}, 0, {880, 496}, {0, 127, 0, 255} }},
	{{ {-8, 8, 8}, 0, {880, 240}, {0, 127, 0, 255} }},
	{{ {8, 8, 8}, 0, {624, 240}, {0, 127, 0, 255} }},
};

Gfx transform_gimbal_mesh_tri_3[] = {
	gsSPVertex(transform_gimbal_mesh_vtx_3 + 0, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Gfx mat_transform_z[] = {
	gsSPLightColor(LIGHT_1, 0xFFFFFFFF),
	gsSPLightColor(LIGHT_2, 0x7F7F7FFF),
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 36, 0, 255, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_transform_z[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

Gfx mat_transform_x[] = {
	gsSPLightColor(LIGHT_1, 0xFFFFFFFF),
	gsSPLightColor(LIGHT_2, 0x7F7F7FFF),
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 9, 0, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_transform_x[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

Gfx mat_transform_y[] = {
	gsSPLightColor(LIGHT_1, 0xFFFFFFFF),
	gsSPLightColor(LIGHT_2, 0x7F7F7FFF),
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 17, 255, 0, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_transform_y[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

Gfx mat_transform_center[] = {
	gsSPLightColor(LIGHT_1, 0xFFFFFFFF),
	gsSPLightColor(LIGHT_2, 0x7F7F7FFF),
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_transform_center[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

Gfx transform_gimbal_mesh[] = {
	gsSPDisplayList(mat_transform_z),
	gsSPDisplayList(transform_gimbal_mesh_tri_0),
	gsSPDisplayList(mat_revert_transform_z),
	gsSPDisplayList(mat_transform_x),
	gsSPDisplayList(transform_gimbal_mesh_tri_1),
	gsSPDisplayList(mat_revert_transform_x),
	gsSPDisplayList(mat_transform_y),
	gsSPDisplayList(transform_gimbal_mesh_tri_2),
	gsSPDisplayList(mat_revert_transform_y),
	gsSPDisplayList(mat_transform_center),
	gsSPDisplayList(transform_gimbal_mesh_tri_3),
	gsSPDisplayList(mat_revert_transform_center),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

Vtx unitcube_Cube_mesh_vtx_cull[8] = {
	{{ {-100, -100, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, -100, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 100, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 100, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, -100, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, -100, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 100, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 100, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx unitcube_Cube_mesh_vtx_0[24] = {
	{{ {-100, -100, 100}, 0, {368, 1008}, {129, 0, 0, 255} }},
	{{ {-100, 100, 100}, 0, {624, 1008}, {129, 0, 0, 255} }},
	{{ {-100, 100, -100}, 0, {624, 752}, {129, 0, 0, 255} }},
	{{ {-100, -100, -100}, 0, {368, 752}, {129, 0, 0, 255} }},
	{{ {-100, -100, -100}, 0, {368, 752}, {0, 0, 129, 255} }},
	{{ {-100, 100, -100}, 0, {624, 752}, {0, 0, 129, 255} }},
	{{ {100, 100, -100}, 0, {624, 496}, {0, 0, 129, 255} }},
	{{ {100, -100, -100}, 0, {368, 496}, {0, 0, 129, 255} }},
	{{ {100, -100, -100}, 0, {368, 496}, {127, 0, 0, 255} }},
	{{ {100, 100, -100}, 0, {624, 496}, {127, 0, 0, 255} }},
	{{ {100, 100, 100}, 0, {624, 240}, {127, 0, 0, 255} }},
	{{ {100, -100, 100}, 0, {368, 240}, {127, 0, 0, 255} }},
	{{ {100, -100, 100}, 0, {368, 240}, {0, 0, 127, 255} }},
	{{ {100, 100, 100}, 0, {624, 240}, {0, 0, 127, 255} }},
	{{ {-100, 100, 100}, 0, {624, -16}, {0, 0, 127, 255} }},
	{{ {-100, -100, 100}, 0, {368, -16}, {0, 0, 127, 255} }},
	{{ {-100, -100, -100}, 0, {112, 496}, {0, 129, 0, 255} }},
	{{ {100, -100, -100}, 0, {368, 496}, {0, 129, 0, 255} }},
	{{ {100, -100, 100}, 0, {368, 240}, {0, 129, 0, 255} }},
	{{ {-100, -100, 100}, 0, {112, 240}, {0, 129, 0, 255} }},
	{{ {100, 100, -100}, 0, {624, 496}, {0, 127, 0, 255} }},
	{{ {-100, 100, -100}, 0, {880, 496}, {0, 127, 0, 255} }},
	{{ {-100, 100, 100}, 0, {880, 240}, {0, 127, 0, 255} }},
	{{ {100, 100, 100}, 0, {624, 240}, {0, 127, 0, 255} }},
};

Gfx unitcube_Cube_mesh_tri_0[] = {
	gsSPVertex(unitcube_Cube_mesh_vtx_0 + 0, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Gfx mat_unitcube_unitcube_layer1[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 128),
	gsSPEndDisplayList(),
};

Gfx mat_revert_unitcube_unitcube_layer1[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx unitcube_Cube_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(unitcube_Cube_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_unitcube_unitcube_layer1),
	gsSPDisplayList(unitcube_Cube_mesh_tri_0),
	gsSPDisplayList(mat_revert_unitcube_unitcube_layer1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

debugTransform sDebugTransformArray[MAX_DEBUG_TRANSFORMS];

void debug_transform_set_flags(debugTransform * dt) {
    if (gGameLoopThread.state == OS_STATE_RUNNING) {
        dt->flags |= WSVD_THREAD5;
    }
}

debugTransform * debug_pos(Vec3f pos) {
    for (int i = 0; i < MAX_DEBUG_TRANSFORMS; i++) {
        if (!(sDebugTransformArray[i].flags & WSVD_ACTIVE)) {
            sDebugTransformArray[i].flags |= WSVD_ACTIVE;
            mtxf_identity(sDebugTransformArray[i].transform);
            vec3f_copy(sDebugTransformArray[i].transform[3],pos);
            debug_transform_set_flags(&sDebugTransformArray[i]);
            return &sDebugTransformArray[i];
        }
    }
    return NULL;
}

debugTransform * debug_mtxf(Mat4 mat) {
    for (int i = 0; i < MAX_DEBUG_TRANSFORMS; i++) {
        if (!(sDebugTransformArray[i].flags & WSVD_ACTIVE)) {
            sDebugTransformArray[i].flags |= WSVD_ACTIVE;
            mtxf_copy(sDebugTransformArray[i].transform,mat);
            debug_transform_set_flags(&sDebugTransformArray[i]);
            return &sDebugTransformArray[i];
        }
    }
    return NULL;
}

void render_worldspace_visual_debug(void) {
    Gfx * dlh = alloc_display_list((sizeof(Gfx)*3*MAX_DEBUG_TRANSFORMS)+4);
    Gfx * dl = dlh;

    gDPPipeSync(dlh++);
    gSPClearGeometryMode(dlh++, G_ZBUFFER);
    for (int i = 0; i < MAX_DEBUG_TRANSFORMS; i++) {
        if (sDebugTransformArray[i].flags & WSVD_ACTIVE) {
            Mtx *mtx = alloc_display_list(sizeof(*mtx));
            mtxf_to_mtx(mtx, sDebugTransformArray[i].transform);

            gSPMatrix(dlh++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPDisplayList(dlh++,transform_gimbal_mesh);
            if (sDebugTransformArray[i].flags & WSVD_CUBE) {
                gSPDisplayList(dlh++,unitcube_Cube_mesh);
            }
        }
    }

    for (int i = 0; i < MAX_DEBUG_TRANSFORMS; i++) {
        if (sDebugTransformArray[i].flags & WSVD_THREAD5) {
            //let it appear for an extra frame to prevent blinking.
            sDebugTransformArray[i].flags &= ~WSVD_THREAD5;
        } else {
            sDebugTransformArray[i].flags = 0;
        }
    }

    gDPPipeSync(dlh++);
    gSPSetGeometryMode(dlh++, G_ZBUFFER);
    gSPEndDisplayList(dlh++);

    geo_append_display_list(dl, LAYER_OPAQUE);
}