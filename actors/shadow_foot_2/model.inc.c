Vtx shadow_foot_2_shadow_foot_2_mesh_vtx_cull[8] = {
	{{ {-25, -16, -29}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-25, -16, 19}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-25, 30, 19}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-25, 30, -29}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {52, -16, -29}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {52, -16, 19}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {52, 30, 19}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {52, 30, -29}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx shadow_foot_2_shadow_foot_2_mesh_vtx_0[23] = {
	{{ {-20, 30, -14}, 0, {-16, -16}, {43, 119, 1, 255} }},
	{{ {-19, 30, 2}, 0, {-16, -16}, {42, 120, 0, 255} }},
	{{ {-5, 25, -26}, 0, {-16, -16}, {42, 120, 0, 255} }},
	{{ {-7, 25, 14}, 0, {-16, -16}, {42, 120, 0, 255} }},
	{{ {37, 10, -29}, 0, {-16, -16}, {42, 120, 0, 255} }},
	{{ {35, 11, 19}, 0, {-16, -16}, {42, 120, 0, 255} }},
	{{ {52, 5, -17}, 0, {-16, -16}, {42, 120, 0, 255} }},
	{{ {51, 5, 9}, 0, {-16, -16}, {43, 120, 1, 255} }},
	{{ {-19, 30, 2}, 0, {-16, -16}, {145, 25, 56, 255} }},
	{{ {-20, 30, -14}, 0, {-16, -16}, {141, 23, 206, 255} }},
	{{ {-25, 7, -5}, 0, {-16, -16}, {138, 210, 4, 255} }},
	{{ {-16, 5, -22}, 0, {-16, -16}, {180, 205, 169, 255} }},
	{{ {-5, 25, -26}, 0, {-16, -16}, {210, 0, 138, 255} }},
	{{ {20, -8, -26}, 0, {-16, -16}, {2, 175, 158, 255} }},
	{{ {37, 10, -29}, 0, {-16, -16}, {30, 212, 141, 255} }},
	{{ {52, 5, -17}, 0, {-16, -16}, {80, 173, 203, 255} }},
	{{ {38, -14, -3}, 0, {-16, -16}, {56, 143, 9, 255} }},
	{{ {51, 5, 9}, 0, {-16, -16}, {74, 173, 61, 255} }},
	{{ {21, -5, 15}, 0, {-16, -16}, {253, 183, 104, 255} }},
	{{ {35, 11, 19}, 0, {-16, -16}, {18, 212, 118, 255} }},
	{{ {-7, 25, 14}, 0, {-16, -16}, {205, 0, 116, 255} }},
	{{ {-17, 5, 9}, 0, {-16, -16}, {180, 205, 88, 255} }},
	{{ {13, -16, -5}, 0, {-16, -16}, {230, 132, 6, 255} }},
};

Gfx shadow_foot_2_shadow_foot_2_mesh_tri_0[] = {
	gsSPVertex(shadow_foot_2_shadow_foot_2_mesh_vtx_0 + 0, 23, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(3, 4, 2, 0, 3, 5, 4, 0),
	gsSP2Triangles(5, 6, 4, 0, 5, 7, 6, 0),
	gsSP2Triangles(8, 9, 10, 0, 11, 10, 9, 0),
	gsSP2Triangles(9, 12, 11, 0, 12, 13, 11, 0),
	gsSP2Triangles(12, 14, 13, 0, 13, 14, 15, 0),
	gsSP2Triangles(15, 16, 13, 0, 15, 17, 16, 0),
	gsSP2Triangles(18, 16, 17, 0, 17, 19, 18, 0),
	gsSP2Triangles(19, 20, 18, 0, 20, 21, 18, 0),
	gsSP2Triangles(21, 20, 8, 0, 10, 21, 8, 0),
	gsSP2Triangles(22, 21, 10, 0, 10, 11, 22, 0),
	gsSP2Triangles(11, 13, 22, 0, 22, 13, 16, 0),
	gsSP2Triangles(16, 18, 22, 0, 22, 18, 21, 0),
	gsSPEndDisplayList(),
};

Gfx mat_shadow_foot_2_shadow_layer1[] = {
	gsSPClearGeometryMode(G_ZBUFFER),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_shadow_foot_2_shadow_layer1[] = {
	gsSPSetGeometryMode(G_ZBUFFER),
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx shadow_foot_2_shadow_foot_2_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(shadow_foot_2_shadow_foot_2_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_shadow_foot_2_shadow_layer1),
	gsSPDisplayList(shadow_foot_2_shadow_foot_2_mesh_tri_0),
	gsSPDisplayList(mat_revert_shadow_foot_2_shadow_layer1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

