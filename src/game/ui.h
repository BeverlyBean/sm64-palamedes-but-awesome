#include "sm64.h"
#include "utf8_print.h"

#ifndef UI_H
#define UI_H

typedef s8 uiid;

uiid ui_create_transform(s8 parentId);
uiid ui_create_text(s8 parentTransId, s16 textId);
uiid ui_create_slice(s8 parentTransId, nineSliceParams * p, s16 x1, s16 y1, s16 x2, s16 y2);
uiid ui_create_btn(s8 parentTransId, s16 textId);

void ui_destroy_trans(uiid idPtr);
void ui_destroy_object(uiid idPtr);

void ui_set_trans_pos(s8 myId, Vec3f pos);
void ui_set_trans_xy(s8 myId, s16 x, s16 y);
void ui_set_text(s8 myId, s16 textId);
void ui_set_trans_color(s8 myId, u8 r, u8 g, u8 b);

void ui_set_transition_instant(s8 myId);

void ui_trans_begin_remove(s8 myId);

void ui_trans_transition_fade_in(uiid myId);
void ui_trans_transition_fade_out(uiid myId);
void ui_trans_transition_instant(uiid myId);
void ui_trans_transition_page_rip_out(uiid myId);

extern uiid gUiidScreen;

void ui_render(void);
void ui_logic(void);
void ui_init(void);

#define UI_NONE -1

#define UI_OBJECT_COUNT 30
#define UI_TRANS_COUNT 40

enum {
    UI_CLASS_TEXT,
    UI_CLASS_SLICE,
    UI_CLASS_BUTTON,
    UI_CLASS_IMAGE,
};

enum {
    PRINT_ORIGIN_LEFT,
    PRINT_ORIGIN_CENTER,
    PRINT_ORIGIN_RIGHT,
};

typedef struct {
    u8 initialized:1;

    uiid parentTrans;

    u8 type;
    s8 uiObjectSibling;

    u16 text;
    u8 textXsize;

    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;

    void * ptr;
    u8 printParam;
    u8 printOrigin;
    u8 printFont;
    s16 printInt[2];
} uiObject;

typedef struct {
    u8 initialized:1;
    u8 base:1;
    u8 getout:1;
    u8 layer:1;

    s8 parent;

    uiid childlist;
    uiid next;
    uiid prev;

    s8 objlist;

    Vec3f pos;
    Vec3f posLerp;
    Vec3f rot;
    Vec3f rotLerp;

    void (* transitionFunction[2])(uiid self);

    f32 transition;
    u8 alpha;
    u8 color[3];
} uiTrans;

uiTrans * ui_trans_ptr(s8 myId);
uiObject * ui_object_ptr(s8 myId);

#endif