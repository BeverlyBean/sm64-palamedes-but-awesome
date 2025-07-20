#include "event_dialog.h"
#include "text_load.h"
#include "utf8_print.h"
#include "level_update.h"
#include "mario.h"
#include "camera.h"
#include "engine/math_util.h"

#include "src/data/event.inc.c"

Vec3f gEventCameraPos;
Vec3f gEventCameraFoc;
Vec3f sEventCameraTargetPos;
Vec3f sEventCameraTargetFoc;
f32 * sEventCameraTargetPosPointer;
f32 * sEventCameraTargetFocPointer;
f32 sEventCameraTransition;
Bool8 sEventCameraTransitionDone = FALSE;

char * sEventOldDialogDisplay = NULL;
char * sEventDialogDisplay = NULL;
f32 sEventCameraTransition = 0.0f;

EventData * gEventHead = NULL;
Bool8 sEventHalt = FALSE;

// Event argument getters
char * event_arg_string(int num) {
    num++;
    return (*(gEventHead+num)).v;
}

int event_arg_int(int num) {
    num++;
    return (*(gEventHead+num)).i;
}

// Commands
void event_set_dialog(int callContext) {
    switch(callContext) {
        case EVENT_CALL_CONTEXT_EXECUTE:
            sEventOldDialogDisplay = sEventDialogDisplay;
            sEventDialogDisplay = get_text(event_arg_int(0));
            sEventHalt = TRUE;
            break;
        case EVENT_CALL_CONTEXT_HALTED:
            if (gMarioState->controller->buttonPressed & A_BUTTON) {
                gEventHead+=2;
                sEventHalt = FALSE;
            }
            break;
    }
}

void event_end(UNUSED int callContext) {
    switch(callContext) {
        case EVENT_CALL_CONTEXT_EXECUTE:
            sEventHalt = TRUE;
            sEventDialogDisplay = NULL;
            event_camera_set_target_pointer(gCamera->pos,gCamera->focus);
            break;
        case EVENT_CALL_CONTEXT_HALTED:
            if (sEventCameraTransitionDone) {
                if (gMarioState->action == ACT_READING_NPC_DIALOG) {
                    set_mario_action(gMarioState, ACT_IDLE, 0);
                }
                gEventHead = NULL;
            }
            break;
    }
}

// Event camera functions

void event_camera_set_target_pointer(Vec3f pos, Vec3f foc) {
    sEventCameraTargetPosPointer = pos;
    sEventCameraTargetFocPointer = foc;
    sEventCameraTransitionDone = FALSE;
    sEventCameraTransition = 0.0f;
}

void event_camera_set_target(Vec3f pos, Vec3f foc) {
    vec3f_copy(sEventCameraTargetPos,pos);
    vec3f_copy(sEventCameraTargetFoc,foc);
    event_camera_set_target_pointer(sEventCameraTargetPos,sEventCameraTargetFoc);
}

// Event control functions
void event_start(EventData * event) {
    if (gEventHead == NULL) {
        sEventOldDialogDisplay = NULL;
        sEventDialogDisplay = NULL;
        sEventHalt = FALSE;

        vec3f_copy(gEventCameraPos,gLakituState.pos);
        vec3f_copy(gEventCameraFoc,gLakituState.focus);
        event_camera_set_target_pointer(gEventCameraPos,gEventCameraFoc);
        sEventCameraTransition = 0.0f;

        gEventHead = event;
    }
}

void event_start_npc(EventData * event, struct Object * npcObj) {
    if (gEventHead == NULL) {
        gMarioState->usedObj = npcObj;
        set_mario_action(gMarioState, ACT_READING_NPC_DIALOG, 0);
        event_start(event);

        s16 talkAngle = obj_angle_to_object(gMarioState->marioObj,npcObj);

        Vec3f pos = {
            gMarioState->pos[0] + sins(talkAngle)*-250.0f - coss(talkAngle)*-200.0f,
            gMarioState->pos[1] + 70.0f,
            gMarioState->pos[2] + coss(talkAngle)*-250.0f + sins(talkAngle)*-200.0f,
        };
        Vec3f foc = {
            npcObj->oPosX - (sins(talkAngle)*-250.0f - coss(talkAngle)*-200.0f),
            npcObj->oPosY + 70.0f,
            npcObj->oPosZ - (coss(talkAngle)*-250.0f + sins(talkAngle)*-200.0f),
        };
        event_camera_set_target(pos,foc);
    }
}

// Event hooks
void event_system_logic_loop(void) {
    if (gEventHead != NULL) {
        if (sEventHalt) {
            gEventHead->func(EVENT_CALL_CONTEXT_HALTED);
        } else {
            while(gEventHead && !sEventHalt) {
               gEventHead->func(EVENT_CALL_CONTEXT_EXECUTE);
            }
        }
    }

    if (sEventCameraTargetPosPointer) {
        sEventCameraTransition+=.04f;
        if (sEventCameraTransition >= 1.0f) {
            sEventCameraTransition = 1.0f;
            sEventCameraTransitionDone = TRUE;
        }
        for (int i = 0; i < 3; i++) {
            gEventCameraPos[i] = approach_f32_asymptotic(gEventCameraPos[i],sEventCameraTargetPosPointer[i],smoothstep2(sEventCameraTransition));
            gEventCameraFoc[i] = approach_f32_asymptotic(gEventCameraFoc[i],sEventCameraTargetFocPointer[i],smoothstep2(sEventCameraTransition));
        }
    }
}

void event_system_render_loop(void) {
    if (gEventHead != NULL) {
        if (sEventDialogDisplay) {
            init_slice_render(&gNotepadSliceParams);
            render_9slice(30,90,287,24);

            utf8_init_print();
            utf8_print(utf8_autonewline(sEventDialogDisplay,240), 40, 62);
        }
    }
}