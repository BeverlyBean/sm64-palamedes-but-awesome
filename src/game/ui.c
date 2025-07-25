#include "sm64.h"
#include "game_init.h"
#include "ui.h"
#include "event_dialog.h"
#include "ingame_menu.h"
#include "utf8_print.h"
#include <PR/gbi.h>
#include "engine/math_util.h"
#include "frame_lerp.h"
#include "print.h"
#include "data/text_enums.h"
#include "text_load.h"

Mat4 sUiMatStack[5];
int sUiMatStackIndex = 0;

uiTrans sUiTransList[UI_TRANS_COUNT];
uiObject sUiObjectList[UI_OBJECT_COUNT];

void ui_mtx_inc(Mat4 mat) {
    mtxf_mul(sUiMatStack[sUiMatStackIndex],mat,sUiMatStack[sUiMatStackIndex-1]);

    Mtx *mtx = (Mtx *) alloc_display_list(sizeof(Mtx));
    mtxf_to_mtx(mtx,sUiMatStack[sUiMatStackIndex]);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    sUiMatStackIndex++;
}

void ui_mtx_pop(void) {
    sUiMatStackIndex--;
}

void ui_init_transform(u8 myId, s8 parentId) {
    uiTrans * self = &sUiTransList[myId];
    uiTrans * parent = NULL;

    self->initialized = TRUE;

    self->uiTransChild = -1;
    self->uiTransSibling = -1;

    self->uiObjectChild = -1;

    self->base = (parentId == UI_NONE);

    if (parentId != UI_NONE) {
        parent = &sUiTransList[parentId];

        if (parent->uiTransChild == -1) {
            parent->uiTransChild = myId;
        } else {
            // Navigate parent transform list
            uiTrans * sibling = &sUiTransList[parent->uiTransChild];
            while(sibling){
                if (sibling->uiTransSibling == UI_NONE) {
                    sibling->uiTransSibling = myId;
                    sibling = NULL;
                } else {
                    sibling = &sUiTransList[sibling->uiTransSibling];
                }
            }
        }
    }
}

void ui_init_object(u8 myId, s8 parentTransId) {
    uiObject * self = &sUiObjectList[myId];
    uiTrans * parent = NULL;

    self->initialized = TRUE;
    self->uiObjectSibling = -1;

    if (parentTransId != UI_NONE) {
        parent = &sUiTransList[parentTransId];

        if (parent->uiObjectChild == -1) {
            parent->uiObjectChild = myId;
        } else {
            // Navigate parent transform list
            uiObject * sibling = &sUiObjectList[parent->uiObjectChild];
            while(sibling){
                if (sibling->uiObjectSibling == UI_NONE) {
                    sibling->uiObjectSibling = myId;
                    sibling = NULL;
                } else {
                    sibling = &sUiObjectList[sibling->uiObjectSibling];
                }
            }
        }
    }
}

void ui_init_text(u8 myId, s8 parentTransId, s16 textId) {
    ui_init_object(myId, parentTransId);
    uiObject * self = &sUiObjectList[myId];

    self->type = UI_CLASS_TEXT;
    self->text = textId;

}

void ui_set_transform_pos(u8 myId, Vec3f pos) {
    uiTrans * self = &sUiTransList[myId];
    vec3f_copy(self->pos,pos);
}

void ui_init_mtx_stack(void) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));
    create_dl_identity_matrix();
    //guOrtho(matrix, 0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -10.0f, 10.0f, 1.0f);

    u16 perspNorm;
    guPerspective(matrix, &perspNorm, 90.0f, 1.333333333333333f, 10.0f, 1000.0f, 1.0f);
    gSPPerspNormalize(gDisplayListHead++, perspNorm);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);


    mtxf_identity(sUiMatStack[0]);
    sUiMatStackIndex = 1;
}

void ui_mat4_screenspace(Mat4 mat) {
    mtxf_identity(mat);
    mat[3][0] = -160.0f;
    mat[3][1] = -120.0f;
    mat[3][2] = -120.0f;
}

void ui_init(void) {
    ui_init_transform(UI_TR_SCREENSPACE, UI_NONE);
    Vec3f screenCorner = {-160.0f,-120.0f,-120.0f};
    ui_set_transform_pos(UI_TR_SCREENSPACE, screenCorner);

    ui_init_text(UI_OB_TX_RAM,UI_TR_SCREENSPACE,TEXT_TEST_2);
}

int sUiDebugRecursion = 0;
int sUiDebugY = 0;

void ui_process_ui_object(uiObject * self) {
    switch(self->type) {
        case UI_CLASS_TEXT:
            utf8_print(get_text(self->text),10,10);
            break;
    }
}

void ui_transform_process_children(s8 transId) {
    sUiDebugY++;
    uiTrans * child = &sUiTransList[transId];

    while(child) {
        frameLerpPos(child->pos,child->posLerp);
        frameLerpPos(child->rot,child->rotLerp);
        Vec3s rot; vec3f_to_vec3s(rot,child->rotLerp);
        Mat4 transform; mtxf_rotate_zxy_and_translate(transform,child->posLerp,rot);
        ui_mtx_inc(transform);

        uiObject * object = &sUiObjectList[child->uiObjectChild];
        while(object) {

            ui_process_ui_object(object);

            if (object->uiObjectSibling != UI_NONE) {
                object = &sUiObjectList[object->uiObjectSibling];
            } else {
                object = NULL;
            }
        }

        if (child->uiTransChild != UI_NONE) {
            sUiDebugRecursion ++;
            ui_transform_process_children(child->uiTransChild);
            sUiDebugRecursion --;
        }

        if (child->uiTransSibling != UI_NONE) {
            transId = child->uiTransSibling;
            child = &sUiTransList[child->uiTransSibling];
            sUiDebugY++;
        } else {
            child = NULL;
        }

        ui_mtx_pop();
    }
}

void ui_render(void) {

    //Mat4 rotmat;
    //Vec3f vz = {0,0,0};
    //Vec3s vr = {0,0,0};
    //mtxf_rotate_zxy_and_translate(rotmat,vz,vr);
    //ui_mtx_inc(rotmat);

    //Mat4 screenSpace;
    //ui_mat4_screenspace(screenSpace);
    //ui_mtx_inc(screenSpace);

    sUiDebugRecursion = 0;
    sUiDebugY = 0;

    utf8_init_print();
    utf8_set_font(FONT_SM64DS);

    ui_init_mtx_stack();
    for (int i = 0; i < UI_TRANS_COUNT; i++) {
        uiTrans * self = &sUiTransList[i];
        if (self->initialized && self->base == TRUE) {
            //I am a root
            ui_transform_process_children(i);
        }
    }

    /*
    utf8_init_print();
    utf8_set_font(FONT_SM64DS);
    event_system_render_loop();

    #ifdef ENABLE_DEBUG_FREE_MOVE
        char debugBuffer[100];
        sprintf(debugBuffer,"RAM Remaining: %d*", main_pool_available()/80000);
        utf8_print(debugBuffer,10,220);
        //utf8_print("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",10,220);
    #endif
    */
}