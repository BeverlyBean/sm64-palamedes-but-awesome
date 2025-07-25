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

uiid gUiidScreen;

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

uiid ui_create_transform(s8 parentId) {
    s8 myId = 0;
    while (sUiTransList[myId].initialized == TRUE) {
        myId++;
    }

    uiTrans * self = &sUiTransList[myId];
    uiTrans * parent = NULL;

    self->initialized = TRUE;

    vec3f_set(self->pos,0,0,0);
    vec3f_set(self->rot,0,0,0);

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
    return myId;
}

uiid ui_create_object(s8 parentTransId) {
    s8 myId = 0;
    while (sUiObjectList[myId].initialized == TRUE) {
        myId++;
    }
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
    return myId;
}

void ui_destroy_trans(uiid * idPtr) {
    sUiTransList[*idPtr].initialized = FALSE;
    *idPtr = UI_NONE; 
}

void ui_destroy_object(uiid * idPtr) {
    sUiObjectList[*idPtr].initialized = FALSE;
    *idPtr = UI_NONE; 
}

uiid ui_create_text(s8 parentTransId, s16 textId) {
    s8 myId = ui_create_object(parentTransId);
    uiObject * self = &sUiObjectList[myId];

    self->type = UI_CLASS_TEXT;
    self->text = textId;

    return myId;
}

uiid ui_create_slice(s8 parentTransId, nineSliceParams * p, s16 x1, s16 y1, s16 x2, s16 y2) {
    s8 myId = ui_create_object(parentTransId);
    uiObject * self = &sUiObjectList[myId];

    self->type = UI_CLASS_SLICE;
    
    self->x1 = x1;
    self->y1 = y1;
    self->x2 = x2;
    self->y2 = y2;

    self->ptr = p;

    return myId;
}

void ui_set_trans_pos(s8 myId, Vec3f pos) {
    uiTrans * self = &sUiTransList[myId];
    vec3f_copy(self->pos,pos);
}

void ui_set_trans_xy(s8 myId, s16 x, s16 y) {
    uiTrans * self = &sUiTransList[myId];
    self->pos[0] = (f32)x;
    self->pos[1] = (f32)y;
    self->pos[2] = 0.0f;
}

void ui_set_text(s8 myId, s16 textId) {
    uiObject * self = &sUiObjectList[myId];
    self->text = textId;
}

void ui_init_mtx_stack(void) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));
    create_dl_identity_matrix();
    //guOrtho(matrix, 0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -10.0f, 10.0f, 1.0f);

    u16 perspNorm;
    guPerspective(matrix, &perspNorm, 90.0f, 4.0f/3.0f, 10.0f, 1000.0f, 1.0f);
    gSPPerspNormalize(gDisplayListHead++, perspNorm);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);


    mtxf_identity(sUiMatStack[0]);
    sUiMatStackIndex = 1;
}

void ui_mat4_screenspace(Mat4 mat) {
    mtxf_identity(mat);
    mat[3][0] = -160.0f;
    mat[3][1] = -90.0f;
    mat[3][2] = -90.0f;
}

int sUiDebugRecursion = 0;
int sUiDebugY = 0;

void ui_process_ui_object(uiObject * self) {
    switch(self->type) {
        case UI_CLASS_TEXT:
            utf8_init_print();
            utf8_set_font(FONT_SM64DS);
            utf8_print(get_text(self->text),0,0);
            break;
        case UI_CLASS_SLICE:
            init_slice_render(self->ptr);
            render_slice(self->x1,self->y1, self->x2, self->y2);
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
        if (child->uiObjectChild == UI_NONE) {
            object = NULL;
        }
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

void ui_init(void) {
    gUiidScreen = ui_create_transform(UI_NONE);
    Vec3f screenCorner = {-160.0f,-120.0f,-120.0f};
    ui_set_trans_pos(gUiidScreen,screenCorner);

    //ui_create_text(gUiidScreen,TEXT_TEST_2);
    //ui_create_slice(gUiidScreen,&gNotepadSliceParams,10,100,100,10);
}