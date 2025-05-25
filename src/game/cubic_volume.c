#include "cubic_volume.h"
#include "engine/math_util.h"

#include "sm64.h"
#include "area.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "main.h"
#include "mario.h"
#include "mario_actions_airborne.h"
#include "mario_actions_automatic.h"
#include "mario_actions_cutscene.h"
#include "mario_actions_moving.h"
#include "mario_actions_object.h"
#include "mario_actions_stationary.h"
#include "mario_actions_submerged.h"
#include "mario_misc.h"
#include "mario_step.h"
#include "memory.h"
#include "object_fields.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "print.h"
#include "save_file.h"
#include "sound_init.h"
#include "rumble_init.h"

CubicVolume testVolume;

u8 spawndebug = FALSE;
struct Object * debugbox;

s32 point_inside_volume(Vec3f p, CubicVolume * v) {
    Vec3f rp;
    vec3f_diff(rp,p,v->pos);

    Mat4 rotMat;
    Quat invR;
    quat_inverse(invR,v->rot);
    mtxf_from_quat(invR,rotMat);

    Vec3f rpr;
    linear_mtxf_mul_vec3(rotMat, rpr, rp);

    struct Object * debug = spawn_object(gMarioObject,MODEL_STAR,bhvCoinSparkles);
    vec3f_copy(&debug->oPosVec, rpr);

    if (spawndebug == FALSE) {
        spawndebug = TRUE;

        debugbox = spawn_object(o,MODEL_TEST_CUBE,bhvStaticObject);
        quat_copy(debugbox->header.gfx.throwRotation, v->rot);
        vec3f_copy(debugbox->header.gfx.scale, v->scale);
        vec3f_copy(&debugbox->oPosVec, v->pos);

        o->prevObj = NULL;
    }

    debugbox->oFlags = OBJ_FLAG_THROW_ROTATION | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE;

    print_text_fmt_int(210, 72, "%d", (s32)v->pos[0]);
    print_text_fmt_int(210, 52, "%d", (s32)v->pos[1]);
    print_text_fmt_int(210, 42, "%d", (s32)v->pos[2]);

    for (int i = 0; i < 3; i++) {
        if (rpr[i] > (v->scale[i]*100.0f)) {return FALSE;}
        if (rpr[i] < (v->scale[i]*-100.0f)) {return FALSE;}
    }

    return TRUE;
}