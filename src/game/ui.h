#include "sm64.h"

#ifndef UI_H
#define UI_H

enum uiTransforms {
    UI_TR_SCREENSPACE,
};

enum uiObjects {
    UI_OB_TX_RAM,
};

void ui_render(void);
void ui_init(void);

#define UI_NONE -1

#define UI_OBJECT_COUNT 25
#define UI_TRANS_COUNT 15

enum {
    UI_CLASS_TEXT,
    UI_CLASS_SLICE,
    UI_CLASS_TRANSFORM,
};

typedef struct {
    u8 initialized:1;

    u8 type;
    s8 uiObjectSibling;

    u16 text;
} uiObject;

typedef struct {
    u8 initialized:1;
    u8 base:1;

    s8 uiTransChild;
    s8 uiTransSibling;

    s8 uiObjectChild;

    Vec3f pos;
    Vec3f posLerp;
    Vec3f rot;
    Vec3f rotLerp;
} uiTrans;

#endif