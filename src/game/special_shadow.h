#include "types.h"

#ifndef SPECIAL_SHADOW_H
#define SPECIAL_SHADOW_H

extern RGBA16 special_shadow_texture_rgba16[1024];

void special_shadow_generate(void);
void special_shadow_texture(Gfx * dlHead);

#endif