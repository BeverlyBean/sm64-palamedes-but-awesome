#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "utf8.h"
#include "types.h"
#include "segment2.h"
#include "ingame_menu.h"
#include "geo_misc.h"
#include "game_init.h"
#include "special_shadow.h"

//0-2 top, 3-5 bottom
u8 print_textcolor[6];
u8 print_italics = 0;
Texture * print_texture = NULL;

// Will initialize size based on difference between last element's xUv and this, if size = 0. Otherwise, can be manually set
// xUv 
fontChar utf8Table[] = {
    [UTF8_SPACE] = {
        .utf8code = ' ',
        .size = 6,
        .tex = NULL,
    },
    [UTF8_UPPERCASE_A] = {
        .utf8code = 'A',
        .xUv = 0,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_B] = {
        .utf8code = 'B',
        .xUv = 5,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_C] = {
        .utf8code = 'C',
        .xUv = 10,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_D] = {
        .utf8code = 'D',
        .xUv = 15,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_E] = {
        .utf8code = 'E',
        .xUv = 20,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_F] = {
        .utf8code = 'F',
        .xUv = 25,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_G] = {
        .utf8code = 'G',
        .xUv = 30,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_H] = {
        .utf8code = 'H',
        .xUv = 35,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_I] = {
        .utf8code = 'I',
        .xUv = 41,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_J] = {
        .utf8code = 'J',
        .xUv = 44,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_K] = {
        .utf8code = 'K',
        .xUv = 49,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_L] = {
        .utf8code = 'L',
        .xUv = 54,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_M] = {
        .utf8code = 'M',
        .xUv = 58,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_N] = {
        .utf8code = 'N',
        .xUv = 63,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_O] = {
        .utf8code = 'O',
        .xUv = 68,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_P] = {
        .utf8code = 'P',
        .xUv = 73,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_Q] = {
        .utf8code = 'Q',
        .xUv = 78,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_R] = {
        .utf8code = 'R',
        .xUv = 84,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_S] = {
        .utf8code = 'S',
        .xUv = 89,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_T] = {
        .utf8code = 'T',
        .xUv = 94,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_U] = {
        .utf8code = 'U',
        .xUv = 99,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_V] = {
        .utf8code = 'V',
        .xUv = 104,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_W] = {
        .utf8code = 'W',
        .xUv = 109,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_X] = {
        .utf8code = 'X',
        .xUv = 114,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_Y] = {
        .utf8code = 'Y',
        .xUv = 119,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_UPPERCASE_Z] = {
        .utf8code = 'Z',
        .xUv = 124,
        .tex = sm64DS_latin_i4,
    },

    [UTF8_LOWERCASE_A] = {
        .utf8code = 'a',
        .xUv = 129,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_B] = {
        .utf8code = 'b',
        .xUv = 133,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_C] = {
        .utf8code = 'c',
        .xUv = 137,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_D] = {
        .utf8code = 'd',
        .xUv = 141,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_E] = {
        .utf8code = 'e',
        .xUv = 145,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_F] = {
        .utf8code = 'f',
        .xUv = 149,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_G] = {
        .utf8code = 'g',
        .xUv = 154,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_H] = {
        .utf8code = 'h',
        .xUv = 159,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_I] = {
        .utf8code = 'i',
        .xUv = 163,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_J] = {
        .utf8code = 'j',
        .xUv = 164,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_K] = {
        .utf8code = 'k',
        .xUv = 168,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_L] = {
        .utf8code = 'l',
        .xUv = 172,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_M] = {
        .utf8code = 'm',
        .xUv = 175,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_N] = {
        .utf8code = 'n',
        .xUv = 180,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_O] = {
        .utf8code = 'o',
        .xUv = 184,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_P] = {
        .utf8code = 'p',
        .xUv = 188,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_Q] = {
        .utf8code = 'q',
        .xUv = 192,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_R] = {
        .utf8code = 'r',
        .xUv = 196,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_S] = {
        .utf8code = 's',
        .xUv = 200,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_T] = {
        .utf8code = 't',
        .xUv = 204,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_U] = {
        .utf8code = 'u',
        .xUv = 208,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_V] = {
        .utf8code = 'v',
        .xUv = 212,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_W] = {
        .utf8code = 'w',
        .xUv = 217,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_X] = {
        .utf8code = 'x',
        .xUv = 222,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_Y] = {
        .utf8code = 'y',
        .xUv = 227,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_LOWERCASE_Z] = {
        .utf8code = 'z',
        .xUv = 232,
        .tex = sm64DS_latin_i4,
        .size = 4,
    },

    [UTF8_ESZETT] = {
        .utf8code = 0x00DF,
        .xUv = 239,
        .tex = sm64DS_latin_i4,
        .size = 4,
    },
    [UTF8_LOWERCASE_UMLAUT_A] = {
        .utf8code = 0x00E4,
        .xUv = 129,
        .tex = sm64DS_latin_i4,
        .size = 4,
        .xUvSecondary = LOWERCASE_UMLAUT_X,
        .sizeSecondary = LOWERCASE_UMLAUT_SIZE,
    },
    [UTF8_LOWERCASE_UMLAUT_O] = {
        .utf8code = 0x00F6,
        .xUv = 184,
        .tex = sm64DS_latin_i4,
        .size = 4,
        .xUvSecondary = LOWERCASE_UMLAUT_X,
        .sizeSecondary = LOWERCASE_UMLAUT_SIZE,
    },
    [UTF8_LOWERCASE_UMLAUT_U] = {
        .utf8code = 0x00FC,
        .xUv = 208,
        .tex = sm64DS_latin_i4,
        .size = 4,
        .xUvSecondary = LOWERCASE_UMLAUT_X,
        .sizeSecondary = LOWERCASE_UMLAUT_SIZE,
    },

    [UTF8_SMILE] = {
        .utf8code = 0x1F60A,
        .xUv = 496,
        .size = 16,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_ANGER] = {
        .utf8code = 0x1F621,
        .xUv = 480,
        .size = 16,
        .tex = sm64DS_latin_i4,
    },
};

void utf8_initialize_table(void) {
    for (int i = 0; i < UTF8_COUNT; i++) {
        fontChar * curChar = &utf8Table[i];
        fontChar * nextChar = &utf8Table[i+1];

        if (curChar->size == 0) {
            curChar->size = nextChar->xUv-curChar->xUv;
        }
    }
}

void utf8_set_texture(Texture * tex) {
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_UI_TEXT, G_CC_UI_TEXT);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

	gSPTexture(gDisplayListHead++,65535, 65535, 0, 0, 1);
	gDPSetTextureImage(gDisplayListHead++,G_IM_FMT_IA, G_IM_SIZ_16b, 1, tex);
	gDPSetTile(gDisplayListHead++,G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0);
	gDPLoadBlock(gDisplayListHead++,7, 0, 0, 2047, 64);
	gDPSetTile(gDisplayListHead++,G_IM_FMT_IA, G_IM_SIZ_4b, 32, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 9, 0);
	gDPSetTileSize(gDisplayListHead++,0, 0, 0, 2044, 60);

    gDPPipeSync(gDisplayListHead++);

    print_texture = tex;
}

fontChar * get_fontchar_from_utf8_codepoint(u32 codepoint) {
    // Binary search
    int low = 0;
    int high = UTF8_COUNT - 1;

    while (low <= high) {
        int mid = low + (high - low)/2;

        u32 searchedCodepoint = utf8Table[mid].utf8code;
        if (searchedCodepoint == codepoint) {
            return &utf8Table[mid];
        } else if (codepoint < searchedCodepoint) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }

    }

    return NULL;
}

void render_fontchar(fontChar * fc ,int x, int y) {
    if (fc->tex != print_texture) {
        utf8_set_texture(fc->tex);
    }

    Vtx * charVerts = alloc_display_list(4 * sizeof(Vtx));

    u16 xUv = fc->xUv*32+2;
    u16 size = fc->size*32-2;

    make_vertex(charVerts, 0, x,          y,    0, xUv,      16*32, print_textcolor[3], print_textcolor[4], print_textcolor[5], 255);
    make_vertex(charVerts, 1, x+fc->size, y,    0, xUv+size, 16*32, print_textcolor[3], print_textcolor[4], print_textcolor[5], 255);
    make_vertex(charVerts, 2, print_italics+x,          y+16, 0, xUv,      0,     print_textcolor[0], print_textcolor[1], print_textcolor[2], 255);
    make_vertex(charVerts, 3, print_italics+x+fc->size, y+16, 0, xUv+size, 0,     print_textcolor[0], print_textcolor[1], print_textcolor[2], 255);

    gSPVertex(gDisplayListHead++,charVerts,4,0);
    gSP2Triangles(gDisplayListHead++, 0, 1, 2, 0, 1, 3, 2, 0);

    if (fc->xUvSecondary > 0) {
        charVerts = alloc_display_list(4 * sizeof(Vtx));
        xUv = fc->xUvSecondary*32+2;
        size = fc->sizeSecondary*32-2;

        make_vertex(charVerts, 0, x,          y,    0, xUv,      16*32, print_textcolor[3], print_textcolor[4], print_textcolor[5], 255);
        make_vertex(charVerts, 1, x+fc->size, y,    0, xUv+size, 16*32, print_textcolor[3], print_textcolor[4], print_textcolor[5], 255);
        make_vertex(charVerts, 2, print_italics+x,          y+16, 0, xUv,      0,     print_textcolor[0], print_textcolor[1], print_textcolor[2], 255);
        make_vertex(charVerts, 3, print_italics+x+fc->size, y+16, 0, xUv+size, 0,     print_textcolor[0], print_textcolor[1], print_textcolor[2], 255);

        gSPVertex(gDisplayListHead++,charVerts,4,0);
        gSP2Triangles(gDisplayListHead++, 0, 1, 2, 0, 1, 3, 2, 0);
    }
}

//returns byte size
s8 utf8_to_codepoint(const char *s, uint32_t *codepoint) {
    unsigned char c = s[0];
    if (c < 0x80) {
        *codepoint = c;
        return 1;
    } else if ((c & 0xE0) == 0xC0) {
        *codepoint = ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
        return 2;
    } else if ((c & 0xF0) == 0xE0) {
        *codepoint = ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
        return 3;
    } else if ((c & 0xF8) == 0xF0) {
        *codepoint = ((s[0] & 0x07) << 18) | ((s[1] & 0x3F) << 12) |
                     ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
        return 4;
    }
    return -1;
}

void print_utf8(char * str, int x, int y) {
    for (int i = 0; i < 6; i++) {
        print_textcolor[i] = 255;
    }
    print_italics = 0;

    int charIndex = 0;
    int printX = 0;
    int printY = 0;
    char * printHead = &str[charIndex];

    while((*printHead) != '\0') {

        if ((*printHead) == '\n') {
            printX = 0;
            printY -= 16;

            charIndex++;
            printHead = &str[charIndex];
            continue;
        }

        if ((*printHead) == '@') {
            for (int i = 0; i < 6; i++) {
                print_textcolor[i] = 255;
            }
            print_italics = 0;

            printHead = &str[++charIndex];
            while ((*printHead) != '@') {
                switch (*printHead) {
                    case 'G':
                        print_textcolor[0] = 50;
                        print_textcolor[1] = 255;
                        print_textcolor[2] = 50;
                        print_textcolor[3] = 0;
                        print_textcolor[4] = 150;
                        print_textcolor[5] = 0;
                        break;
                    case 'R':
                        print_textcolor[0] = 255;
                        print_textcolor[1] = 50;
                        print_textcolor[2] = 50;
                        print_textcolor[3] = 170;
                        print_textcolor[4] = 0;
                        print_textcolor[5] = 0;
                        break;
                    case 'Y':
                        print_textcolor[0] = 255;
                        print_textcolor[1] = 255;
                        print_textcolor[2] = 100;
                        print_textcolor[3] = 255;
                        print_textcolor[4] = 255;
                        print_textcolor[5] = 0;
                        break;
                    case 'I':
                        //print_italics = 4;
                        break;
                }
                printHead = &str[++charIndex];
            }
            printHead = &str[++charIndex];
            continue;
        }

        u32 codepoint;
        u8 size = utf8_to_codepoint(printHead,&codepoint);
        fontChar * fc = get_fontchar_from_utf8_codepoint(codepoint);

        if (fc->tex != NULL) {
            render_fontchar(fc,x+printX,y+printY);
        }
        printX += fc->size+1;
        
        charIndex += size;
        printHead = &str[charIndex];
    }
}

void utf8_print_reset(void) {
    print_texture = NULL;
}

void ui_render(void) {
    create_dl_ortho_matrix();
    utf8_print_reset();
    print_utf8("THE @I@QUICK@@ BROWN FOX @Y@😊@@ JUMPS OVER @GI@ARTHURTILLY@@ ALOT @Y@😊😊@@\n😡@R@ DAS WAR EIN BEFEHL 😡@@ wow 😊\nthe quick brown fox jumps over the lazy dog",-20,50);
    print_utf8("falsches üben von xylophonmusik quält jeden größeren zwerg",10,150);
}