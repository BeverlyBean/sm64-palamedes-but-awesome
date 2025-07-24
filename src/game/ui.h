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

#define UI_NONE -1

#define UI_OBJECT_TOTAL_COUNT 25
#define UI_TRANS_TOTAL_COUNT 15

enum {
    CLASS_TEXT,
    CLASS_SLICE,
    CLASS_TRANSFORM,
};

typedef struct {
    u8 initialized:1;

    u8 type;
    s8 uiObjectSibling;

    u16 text;
} uiObject;

typedef struct {
    u8 initialized:1;

    s8 uiTransChildPtr;
    s8 uiTransSibling;

    s8 uiObjectChildPtr;

    Vec3f pos;
    Vec3f posLerp;
    Vec3s rot;
    Vec3s rotLerp;
} uiTrans;

#endif