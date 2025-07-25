#include "event_dialog.h"
#include "text_load.h"
#include "utf8_print.h"
#include "level_update.h"
#include "mario.h"
#include "camera.h"
#include "engine/math_util.h"
#include "ui.h"
#include "src/data/event.inc.c"
#include "game_init.h"


Vec3f gEventCameraPos;
Vec3f gEventCameraFoc;
Vec3f sEventCameraTargetPos;
Vec3f sEventCameraTargetFoc;
f32 * sEventCameraTargetPosPointer;
f32 * sEventCameraTargetFocPointer;
f32 sEventCameraTransition;
Bool8 sEventCameraTransitionDone = FALSE;

struct CutsceneSplinePoint * sEventCameraSpline[2];
s16 sEventCameraSplineSegment[2];
f32 sEventCameraSplineProgress[2];

Vec3f sEventCameraConversationPos;
Vec3f sEventCameraConversationFoc;

char * sEventOldDialogDisplay = NULL;
char * sEventDialogDisplay = NULL;
f32 sEventCameraTransition = 0.0f;

EventDialogOption sEventDialogOptionArray[5];
int sEventDialogOptionCount = 0;
int sEventDialogOptionIndex = 0;

EventData * gEventHead = NULL;
EventData * sEventStackArray[5];
EventData * sEventStartStackArray[5];
int sEventStackIndex = 0;
Bool8 sEventHalt = FALSE;

// Branch
void event_branch(EventData * branchLocation) {
    // Check if it's already in the stack to avoid infinite recursion
    for (int i = 0; i < sEventStackIndex+1; i++) {
        if (sEventStartStackArray[i] == branchLocation) {
            gEventHead = sEventStartStackArray[i];
            sEventStackIndex = i;
            return;
        }
    }

    sEventStackArray[sEventStackIndex] = gEventHead;
    sEventStackIndex++;
    sEventStartStackArray[sEventStackIndex] = branchLocation;
    gEventHead = branchLocation;
}

// Event argument getters
int event_arg_int(int num) {
    num++;
    return (*(gEventHead+num)).i;
}

f32 * event_arg_vec3f(int num) {
    num++;
    return (f32 *)((*(gEventHead+num)).v);
}

EventData * event_arg_event(int num) {
    num++;
    return (EventData *)(*(gEventHead+num)).v;
}

struct CutsceneSplinePoint * event_arg_spline(int num) {
    num++;
    return (struct CutsceneSplinePoint *)((*(gEventHead+num)).v);
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
                if (sEventDialogOptionCount > 0) {
                    event_branch(sEventDialogOptionArray[sEventDialogOptionIndex].jump);
                    sEventDialogOptionCount = 0;
                    sEventDialogOptionIndex = 0;
                }
            }
            break;
    }
}

void event_close_dialog(UNUSED int callContext) {
    sEventOldDialogDisplay = sEventDialogDisplay;
    sEventDialogDisplay = NULL;
    gEventHead++;
}

void event_follow_spline(UNUSED int callContext) {
    sEventCameraSplineSegment[0] = 0;
    sEventCameraSplineProgress[0] = 0.0f;
    sEventCameraSplineSegment[1] = 0;
    sEventCameraSplineProgress[1] = 0.0f;

    sEventCameraTransition = 0.0f;

    sEventCameraSpline[0] = event_arg_spline(0);
    sEventCameraSpline[1] = event_arg_spline(1);

    gEventHead+=3;
}

void event_return_to_conversation(UNUSED int callContext) {
    event_camera_set_target_pointer(sEventCameraConversationPos,sEventCameraConversationFoc);
    gEventHead++;
}

void event_dialog_choice(UNUSED int callContext) {
    sEventDialogOptionArray[sEventDialogOptionCount].textId = event_arg_int(0);
    sEventDialogOptionArray[sEventDialogOptionCount].jump = event_arg_event(1);
    sEventDialogOptionCount++;
    gEventHead+=3;
}

void event_branch_cmd(UNUSED int callContext) {
    gEventHead+=2;
    event_branch(event_arg_event(0));
}

void event_end_branch(UNUSED int callContext) {
    sEventStackIndex--;
    gEventHead = sEventStackArray[sEventStackIndex];
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
    sEventCameraSpline[0] = 0;

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

void event_camera_set(Vec3f pos, Vec3f foc) {
    vec3f_copy(sEventCameraTargetPos,pos);
    vec3f_copy(sEventCameraTargetFoc,foc);
    vec3f_copy(gEventCameraPos,pos);
    vec3f_copy(gEventCameraFoc,foc);
    event_camera_set_target_pointer(sEventCameraTargetPos,sEventCameraTargetFoc);
}

// Event control functions
void event_start(EventData * event) {
    if (gEventHead == NULL) {
        sEventOldDialogDisplay = NULL;
        sEventDialogDisplay = NULL;
        sEventHalt = FALSE;

        sEventCameraSpline[0] = 0;

        vec3f_copy(gEventCameraPos,gLakituState.pos);
        vec3f_copy(gEventCameraFoc,gLakituState.focus);
        event_camera_set_target_pointer(gEventCameraPos,gEventCameraFoc);
        sEventCameraTransition = 0.0f;

        gEventHead = event;

        sEventStartStackArray[0] = gEventHead;
        sEventStackIndex = 0;

        sEventDialogOptionCount = 0;
    }
}

void event_start_npc(EventData * event, struct Object * npcObj) {
    if (gEventHead == NULL) {
        gMarioState->usedObj = npcObj;
        event_start(event);

        s16 talkAngle = obj_angle_to_object(gMarioState->marioObj,npcObj);

        vec3f_set(sEventCameraConversationPos,
            gMarioState->pos[0] + sins(talkAngle)*-250.0f - coss(talkAngle)*-200.0f,
            gMarioState->pos[1] + 70.0f,
            gMarioState->pos[2] + coss(talkAngle)*-250.0f + sins(talkAngle)*-200.0f
        );
        vec3f_set(sEventCameraConversationFoc,
            npcObj->oPosX - (sins(talkAngle)*-250.0f - coss(talkAngle)*-200.0f),
            npcObj->oPosY + 70.0f,
            npcObj->oPosZ - (coss(talkAngle)*-250.0f + sins(talkAngle)*-200.0f)
        );
        event_camera_set_target_pointer(sEventCameraConversationPos,sEventCameraConversationFoc);
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

    // Choice Logic
    if (sEventDialogOptionCount > 0) {
        if (gMarioState->controller->buttonPressed & D_JPAD) {
            sEventDialogOptionIndex++;
        }
        if (gMarioState->controller->buttonPressed & U_JPAD) {
            sEventDialogOptionIndex--;
        }
        sEventDialogOptionIndex = (sEventDialogOptionCount +sEventDialogOptionIndex) % sEventDialogOptionCount;
    }

    // Camera Logic

    if (sEventCameraSpline[0]) {
        sEventCameraTargetPosPointer = sEventCameraTargetPos;
        sEventCameraTargetFocPointer = sEventCameraTargetFoc;

        if (
            move_point_along_spline(sEventCameraTargetPos, segmented_to_virtual(sEventCameraSpline[0]), &sEventCameraSplineSegment[0], &sEventCameraSplineProgress[0]) ||
            move_point_along_spline(sEventCameraTargetFoc, segmented_to_virtual(sEventCameraSpline[1]), &sEventCameraSplineSegment[1], &sEventCameraSplineProgress[1])
        ) {
            sEventCameraSpline[0] = 0;
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

    // Event ui

    Vec3f modvec = {0,sins(gGlobalTimer*0x1000)*20.0f,-120};
    ui_set_transform_pos(UI_TR_SCREENSPACE,modvec);
}

void event_system_render_loop(void) {
    if (gEventHead != NULL) {
        if (sEventDialogDisplay) {
            init_slice_render(&gNotepadSliceParams);
            render_9slice(30,90,287,24);

            int yOffset = -10;
            if (sEventDialogOptionCount == 3) {
                yOffset = 10;
            }
            for (int i = 0; i < sEventDialogOptionCount; i++) {
                char * str = get_text(sEventDialogOptionArray[i].textId);
                int x; int y; utf8_size(str,&x,&y);
                int hx = x/2;

                init_slice_render(&gStickySliceParams);
                render_4slice(150-hx,200-(i*40)+yOffset,170+hx,168-(i*40)+yOffset);
                utf8_init_print();
                utf8_print(str,160-hx,177-(i*40)+yOffset);

                if (i == sEventDialogOptionIndex) {
                    render_rgba16_texture(130-hx,180-(i*40)+yOffset,pin_rgba16);
                }
            }

            utf8_init_print();
            utf8_print(utf8_autonewline(sEventDialogDisplay,240), 40, 62);
        }
    }
}