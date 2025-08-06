#include "sm64.h"
#include "debug_tracker.h"
#include "utf8_print.h"
#include "ingame_menu.h"
#include "game_init.h"

struct TrackedValue sDebugTrackerList[MAX_DEBUG_TRACKERS];
char sDebugTrackerCharBuffer[100];

void debug_tracker_track(void * value, char * label, u8 type) {
    for (int i = 0; i < MAX_DEBUG_TRACKERS; i++) {
        if (sDebugTrackerList[i].label == label) {
            // Found my tracker, do nothing
            return;
        }
    }
    // None of my trackers found, add it
    for (int i = 0; i < MAX_DEBUG_TRACKERS; i++) {
        if (!sDebugTrackerList[i].initialized) {
            sDebugTrackerList[i].initialized = TRUE;
            sDebugTrackerList[i].type = type;
            sDebugTrackerList[i].value = value;
            sDebugTrackerList[i].label = label;
            return;
        }
    }
}

void debug_s32(s32 * value, char * label) {
    debug_tracker_track(value,label,TRACKER_TYPE_S32);
}

void debug_u32(u32 * value, char * label) {
    debug_tracker_track(value,label,TRACKER_TYPE_S32);
}

void debug_s16(s16 * value, char * label) {
    debug_tracker_track(value,label,TRACKER_TYPE_S16);
}

void debug_f32(f32 * value, char * label) {
    debug_tracker_track(value,label,TRACKER_TYPE_F32);
}

void debug_vec3f(Vec3f * value, char * label) {
    debug_tracker_track(value,label,TRACKER_TYPE_V3F);
}

void debug_tracker_render(void) {
    create_dl_ortho_matrix();
    utf8_init_print();
    utf8_set_font(FONT_SM64DS);
    gDPSetEnvColor(gDisplayListHead++,255,255,255,255);

    for (int i = 0; i < MAX_DEBUG_TRACKERS; i++) {
        if (sDebugTrackerList[i].initialized) {
            switch(sDebugTrackerList[i].type) {
                case TRACKER_TYPE_F32:;
                    f32 f32value = *((f32*)sDebugTrackerList[i].value);
                    int fxpt = (int)(f32value*100.f);
                    int frac = fxpt%100;
                    int whole = fxpt/100;
                    sprintf(sDebugTrackerCharBuffer,"%s: %d.%d",sDebugTrackerList[i].label,whole,frac);
                    break;
                case TRACKER_TYPE_S32:;
                    s32 s32value = *((s32*)sDebugTrackerList[i].value);
                    sprintf(sDebugTrackerCharBuffer,"%s: %d",sDebugTrackerList[i].label,s32value);
                    break;
                case TRACKER_TYPE_U32:;
                    u32 u32value = *((u32*)sDebugTrackerList[i].value);
                    sprintf(sDebugTrackerCharBuffer,"%s: %d",sDebugTrackerList[i].label,u32value);
                    break;
                case TRACKER_TYPE_V3F:;
                    int x = ((f32*)sDebugTrackerList[i].value)[0];
                    int y = ((f32*)sDebugTrackerList[i].value)[1];
                    int z = ((f32*)sDebugTrackerList[i].value)[2];
                    sprintf(sDebugTrackerCharBuffer,"%s: %d, %d, %d",sDebugTrackerList[i].label,x,y,z);
                    break;
                
            }
            utf8_print(sDebugTrackerCharBuffer,0,220-(i*16));
        }
    }
}