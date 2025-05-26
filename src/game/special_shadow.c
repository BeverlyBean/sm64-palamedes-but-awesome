#include "types.h"
#include "engine/math_util.h"
#include "special_shadow.h"
#include "segment2.h"
#include <PR/gbi.h>
#include "game_init.h"

RGBA16 special_shadow_texture_rgba16[1024];

void special_shadow_texture(Gfx * dlHead) {
    gDPPipeSync(dlHead++);
    gDPSetTextureFilter(dlHead++,G_TF_POINT);
    gDPSetCombineLERP(dlHead++,0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0);
    gSPTexture(dlHead++,65535, 65535, 0, 0, 1);
    gDPSetTextureImage(dlHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, segmented_to_virtual(special_shadow_texture_rgba16));
    gDPSetTile(dlHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0);
    gDPLoadBlock(dlHead++,7, 0, 0, 1023, 256);
    gDPSetTile(dlHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0);
    gDPSetTileSize(dlHead++,0, 0, 0, 124, 124);
}

void special_shadow_generate(void) {
    for (int i = 0; i < 1024; i++) {
        special_shadow_texture_rgba16[i] = random_u16();
    }
}