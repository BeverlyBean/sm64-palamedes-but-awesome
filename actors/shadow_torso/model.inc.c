Vtx shadow_torso_shadow_torso_mesh_vtx_cull[8] = {
	{{ {-34, -24, -39}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-34, -24, 39}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-34, 24, 39}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-34, 24, -39}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {27, -24, -39}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {27, -24, 39}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {27, 24, 39}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {27, 24, -39}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx shadow_torso_shadow_torso_mesh_vtx_0[24] = {
	{{ {-34, -24, 39}, 0, {368, 1008}, {129, 0, 0, 255} }},
	{{ {-34, 24, 39}, 0, {624, 1008}, {129, 0, 0, 255} }},
	{{ {-34, 24, -39}, 0, {624, 752}, {129, 0, 0, 255} }},
	{{ {-34, -24, -39}, 0, {368, 752}, {129, 0, 0, 255} }},
	{{ {-34, -24, -39}, 0, {368, 752}, {0, 0, 129, 255} }},
	{{ {-34, 24, -39}, 0, {624, 752}, {0, 0, 129, 255} }},
	{{ {27, 24, -39}, 0, {624, 496}, {0, 0, 129, 255} }},
	{{ {27, -24, -39}, 0, {368, 496}, {0, 0, 129, 255} }},
	{{ {27, -24, -39}, 0, {368, 496}, {127, 0, 0, 255} }},
	{{ {27, 24, -39}, 0, {624, 496}, {127, 0, 0, 255} }},
	{{ {27, 24, 39}, 0, {624, 240}, {127, 0, 0, 255} }},
	{{ {27, -24, 39}, 0, {368, 240}, {127, 0, 0, 255} }},
	{{ {27, -24, 39}, 0, {368, 240}, {0, 0, 127, 255} }},
	{{ {27, 24, 39}, 0, {624, 240}, {0, 0, 127, 255} }},
	{{ {-34, 24, 39}, 0, {624, -16}, {0, 0, 127, 255} }},
	{{ {-34, -24, 39}, 0, {368, -16}, {0, 0, 127, 255} }},
	{{ {-34, -24, -39}, 0, {112, 496}, {0, 129, 0, 255} }},
	{{ {27, -24, -39}, 0, {368, 496}, {0, 129, 0, 255} }},
	{{ {27, -24, 39}, 0, {368, 240}, {0, 129, 0, 255} }},
	{{ {-34, -24, 39}, 0, {112, 240}, {0, 129, 0, 255} }},
	{{ {27, 24, -39}, 0, {624, 496}, {0, 127, 0, 255} }},
	{{ {-34, 24, -39}, 0, {880, 496}, {0, 127, 0, 255} }},
	{{ {-34, 24, 39}, 0, {880, 240}, {0, 127, 0, 255} }},
	{{ {27, 24, 39}, 0, {624, 240}, {0, 127, 0, 255} }},
};

Gfx shadow_torso_shadow_torso_mesh_tri_0[] = {
	gsSPVertex(shadow_torso_shadow_torso_mesh_vtx_0 + 0, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Gfx mat_shadow_torso_shadow_layer1[] = {
	gsSPClearGeometryMode(G_ZBUFFER),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_shadow_torso_shadow_layer1[] = {
	gsSPSetGeometryMode(G_ZBUFFER),
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx shadow_torso_shadow_torso_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(shadow_torso_shadow_torso_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_shadow_torso_shadow_layer1),
	gsSPDisplayList(shadow_torso_shadow_torso_mesh_tri_0),
	gsSPDisplayList(mat_revert_shadow_torso_shadow_layer1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

