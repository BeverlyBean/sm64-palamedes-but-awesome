Vtx shadow_foot_shadow_foot_mesh_vtx_cull[8] = {
	{{ {-25, -16, -19}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-25, -16, 29}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-25, 31, 29}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-25, 31, -19}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {52, -16, -19}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {52, -16, 29}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {52, 31, 29}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {52, 31, -19}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx shadow_foot_shadow_foot_mesh_vtx_0[23] = {
	{{ {52, 4, 16}, 0, {-16, -16}, {43, 119, 254, 255} }},
	{{ {52, 4, -9}, 0, {-16, -16}, {43, 119, 254, 255} }},
	{{ {36, 9, -19}, 0, {-16, -16}, {44, 119, 254, 255} }},
	{{ {37, 10, 29}, 0, {-16, -16}, {44, 119, 254, 255} }},
	{{ {-6, 25, -15}, 0, {-16, -16}, {45, 119, 254, 255} }},
	{{ {-5, 25, 25}, 0, {-16, -16}, {45, 119, 254, 255} }},
	{{ {-18, 30, -4}, 0, {-16, -16}, {46, 118, 254, 255} }},
	{{ {-19, 31, 12}, 0, {-16, -16}, {44, 119, 255, 255} }},
	{{ {20, -8, 25}, 0, {-16, -16}, {0, 176, 99, 255} }},
	{{ {37, 10, 29}, 0, {-16, -16}, {28, 210, 115, 255} }},
	{{ {-5, 25, 25}, 0, {-16, -16}, {209, 3, 118, 255} }},
	{{ {52, 4, 16}, 0, {-16, -16}, {78, 172, 55, 255} }},
	{{ {38, -15, 3}, 0, {-16, -16}, {54, 141, 249, 255} }},
	{{ {13, -16, 5}, 0, {-16, -16}, {228, 132, 252, 255} }},
	{{ {-16, 6, 21}, 0, {-16, -16}, {179, 207, 88, 255} }},
	{{ {-19, 31, 12}, 0, {-16, -16}, {142, 26, 49, 255} }},
	{{ {-25, 7, 4}, 0, {-16, -16}, {137, 211, 252, 255} }},
	{{ {-18, 30, -4}, 0, {-16, -16}, {145, 25, 199, 255} }},
	{{ {-16, 5, -10}, 0, {-16, -16}, {181, 203, 168, 255} }},
	{{ {-6, 25, -15}, 0, {-16, -16}, {207, 254, 139, 255} }},
	{{ {21, -6, -16}, 0, {-16, -16}, {251, 181, 153, 255} }},
	{{ {36, 9, -19}, 0, {-16, -16}, {19, 208, 140, 255} }},
	{{ {52, 4, -9}, 0, {-16, -16}, {73, 170, 198, 255} }},
};

Gfx shadow_foot_shadow_foot_mesh_tri_0[] = {
	gsSPVertex(shadow_foot_shadow_foot_mesh_vtx_0 + 0, 23, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
	gsSP2Triangles(3, 2, 4, 0, 5, 3, 4, 0),
	gsSP2Triangles(5, 4, 6, 0, 5, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 11, 9, 8, 0),
	gsSP2Triangles(8, 12, 11, 0, 12, 8, 13, 0),
	gsSP2Triangles(13, 8, 14, 0, 14, 8, 10, 0),
	gsSP2Triangles(14, 10, 15, 0, 15, 16, 14, 0),
	gsSP2Triangles(16, 15, 17, 0, 17, 18, 16, 0),
	gsSP2Triangles(17, 19, 18, 0, 20, 18, 19, 0),
	gsSP2Triangles(20, 19, 21, 0, 20, 21, 22, 0),
	gsSP2Triangles(22, 12, 20, 0, 12, 22, 11, 0),
	gsSP2Triangles(13, 20, 12, 0, 18, 20, 13, 0),
	gsSP2Triangles(16, 18, 13, 0, 13, 14, 16, 0),
	gsSPEndDisplayList(),
};

Gfx mat_shadow_foot_shadow_layer1[] = {
	gsSPClearGeometryMode(G_ZBUFFER),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_shadow_foot_shadow_layer1[] = {
	gsSPSetGeometryMode(G_ZBUFFER),
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx shadow_foot_shadow_foot_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(shadow_foot_shadow_foot_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_shadow_foot_shadow_layer1),
	gsSPDisplayList(shadow_foot_shadow_foot_mesh_tri_0),
	gsSPDisplayList(mat_revert_shadow_foot_shadow_layer1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

