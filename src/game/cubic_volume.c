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

s32 point_inside_volume(Vec3f p, CubicVolume * v) {
    Vec3f rp;
    vec3f_diff(rp,p,v->pos);

    Mat4 rotMat;
    Quat invR;
    quat_inverse(invR,v->rot);
    mtxf_from_quat(invR,rotMat);

    Vec3f rpr;
    linear_mtxf_mul_vec3(rotMat, rpr, rp);

    for (int i = 0; i < 3; i++) {
        if (rpr[i] > (v->scale[i]*100.0f)) {return FALSE;}
        if (rpr[i] < (v->scale[i]*-100.0f)) {return FALSE;}
    }

    return TRUE;
}