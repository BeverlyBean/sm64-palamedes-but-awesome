#include "sm64.h"

#ifndef DAY_NIGHT_CYCLE_H
#define DAY_NIGHT_CYCLE_H

void day_night_set_light(void);
void day_night_restore_object_light(void);

void day_night_logic(void);
Gfx *geo_day_night_light(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 *mtx);
u8 day_night_get_color_channel(int colorIndex);

s32 day_night_get_day_or_night(void);
u8 day_night_get_hour(void);

#endif