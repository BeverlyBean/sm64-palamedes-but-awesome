Vtx shadow_limb_shadow_limb_mesh_vtx_0[18] = {
	{{ {-25, -21, 22}, 0, {368, 1008}, {129, 0, 0, 255} }},
	{{ {-25, 24, 0}, 0, {624, 752}, {129, 0, 0, 255} }},
	{{ {-25, -21, -22}, 0, {368, 752}, {129, 0, 0, 255} }},
	{{ {57, -21, -22}, 0, {368, 496}, {127, 0, 0, 255} }},
	{{ {57, 24, 0}, 0, {624, 240}, {127, 0, 0, 255} }},
	{{ {57, -21, 22}, 0, {368, 240}, {127, 0, 0, 255} }},
	{{ {-25, -21, -22}, 0, {368, 752}, {0, 57, 142, 255} }},
	{{ {-25, 24, 0}, 0, {624, 752}, {0, 57, 142, 255} }},
	{{ {57, 24, 0}, 0, {624, 496}, {0, 57, 142, 255} }},
	{{ {57, -21, -22}, 0, {368, 496}, {0, 57, 142, 255} }},
	{{ {57, -21, 22}, 0, {368, 240}, {0, 57, 114, 255} }},
	{{ {57, 24, 0}, 0, {624, 240}, {0, 57, 114, 255} }},
	{{ {-25, 24, 0}, 0, {624, -16}, {0, 57, 114, 255} }},
	{{ {-25, -21, 22}, 0, {368, -16}, {0, 57, 114, 255} }},
	{{ {-25, -21, -22}, 0, {112, 496}, {0, 129, 0, 255} }},
	{{ {57, -21, -22}, 0, {368, 496}, {0, 129, 0, 255} }},
	{{ {57, -21, 22}, 0, {368, 240}, {0, 129, 0, 255} }},
	{{ {-25, -21, 22}, 0, {112, 240}, {0, 129, 0, 255} }},
};

Gfx shadow_limb_shadow_limb_mesh_tri_0[] = {
	gsSPVertex(shadow_limb_shadow_limb_mesh_vtx_0 + 0, 18, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
	gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
	gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
	gsSPEndDisplayList(),
};

Gfx mat_shadow_limb_shadow_layer1[] = {
	gsSPClearGeometryMode(G_ZBUFFER),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_shadow_limb_shadow_layer1[] = {
	gsSPSetGeometryMode(G_ZBUFFER),
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx shadow_limb_shadow_limb_mesh[] = {
	gsSPDisplayList(mat_shadow_limb_shadow_layer1),
	gsSPDisplayList(shadow_limb_shadow_limb_mesh_tri_0),
	gsSPDisplayList(mat_revert_shadow_limb_shadow_layer1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

