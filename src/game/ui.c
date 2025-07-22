#include "sm64.h"
#include "game_init.h"
#include "ui.h"
#include "event_dialog.h"
#include "ingame_menu.h"
#include "utf8_print.h"
#include <PR/gbi.h>
#include "engine/math_util.h"
#include "frame_lerp.h"

Mat4 sUiMatStack[5];
int sUiMatStackIndex = 0;

void ui_transform(Mat4 mat) {
    mtxf_mul(sUiMatStack[sUiMatStackIndex],mat,sUiMatStack[sUiMatStackIndex-1]);

    Mtx *mtx = (Mtx *) alloc_display_list(sizeof(Mtx));
    mtxf_to_mtx(mtx,sUiMatStack[sUiMatStackIndex]);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_MODELVIEW  | G_MTX_MUL | G_MTX_NOPUSH);

    sUiMatStackIndex++;
}

void ui_pop_transform(void) {
    sUiMatStackIndex--;
}

void ui_init_transform(void) {
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

s16 pingTimer = 0;
void ui_render(void) {
    ui_init_transform();

    if (gPlayer1Controller->buttonDown & Z_TRIG) {
        pingTimer++;
    }

    Mat4 rotmat;
    Vec3f vz = {0,0,0};
    Vec3s vr = {0,pingTimer*0x50,0};
    mtxf_rotate_zxy_and_translate(rotmat,vz,vr);
    ui_transform(rotmat);

    Mat4 screenSpace;
    ui_mat4_screenspace(screenSpace);
    ui_transform(screenSpace);


    utf8_init_print();
    utf8_set_font(FONT_SM64DS);
    event_system_render_loop();

    #ifdef ENABLE_DEBUG_FREE_MOVE
        char debugBuffer[100];
        sprintf(debugBuffer,"RAM Remaining: %d*", main_pool_available()/80000);
        utf8_print(debugBuffer,10,220);
        //utf8_print("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",10,220);
    #endif
}