// Will initialize size based on difference between last element's xUv and this, if size = 0. Otherwise, can be manually set
fontChar sCharListSM64DS[UTF8_COUNT] = {
    [UTF8_SPACE] = {
        .utf8code = ' ',
        .size = 6,
        .tex = NULL,
    },

    [UTF8_EXCLAMATION] = {
        .utf8code = '!',
        .xUv = 318,
        .tex = sm64DS_latin_i4,
        .size = 4,
    },
    [UTF8_APOSTROPHE] = {
        .utf8code = 0x27,
        .xUv = 321,
        .tex = sm64DS_latin_i4,
        .size = 2,
    },
    [UTF8_OPEN_BRACKET] = {
        .utf8code = '(',
        .xUv = 326,
        .tex = sm64DS_latin_i4,
        .size = 3,
    },
    [UTF8_CLOSE_BRACKET] = {
        .utf8code = ')',
        .xUv = 329,
        .tex = sm64DS_latin_i4,
        .size = 3,
    },
    [UTF8_PERCENTAGE] = {
        .utf8code = '*',
        .xUv = 312,
        .tex = sm64DS_latin_i4,
        .size = 6,
    },
    [UTF8_PLUS] = {
        .utf8code = '+',
        .xUv = 333,
        .tex = sm64DS_latin_i4,
        .size = 8,
    },
    [UTF8_COMMA] = {
        .utf8code = 0x2C,
        .xUv = 304,
        .tex = sm64DS_latin_i4,
        .size = 2,
    },
    [UTF8_DASH] = {
        .utf8code = 0x2D,
        .xUv = 332,
        .tex = sm64DS_latin_i4,
        .size = 4,
    },
    [UTF8_PERIOD] = {
        .utf8code = '.',
        .xUv = 300,
        .tex = sm64DS_latin_i4,
        .size = 2,
    },
    [UTF8_SLASH] = {
        .utf8code = '/',
        .xUv = 373,
        .tex = sm64DS_latin_i4,
        .size = 5,
    },

    [UTF8_0] = {
        .utf8code = '0',
        .xUv = 243,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_1] = {
        .utf8code = '1',
        .xUv = 249,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_2] = {
        .utf8code = '2',
        .xUv = 252,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_3] = {
        .utf8code = '3',
        .xUv = 258,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_4] = {
        .utf8code = '4',
        .xUv = 264,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_5] = {
        .utf8code = '5',
        .xUv = 270,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_6] = {
        .utf8code = '6',
        .xUv = 276,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_7] = {
        .utf8code = '7',
        .xUv = 282,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_8] = {
        .utf8code = '8',
        .xUv = 288,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_9] = {
        .utf8code = '9',
        .xUv = 294,
        .tex = sm64DS_latin_i4,
        .size = 6
    },

    [UTF8_COLON] = {
        .utf8code = ':',
        .xUv = 302,
        .tex = sm64DS_latin_i4,
        .size = 2
    },
    [UTF8_QUESTION] = {
        .utf8code = '?',
        .xUv = 306,
        .tex = sm64DS_latin_i4,
        .size = 6
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

    [UTF8_LEFT] = {
        .utf8code = 0x2190, /*←*/
        .xUv = 352,
        .size = 4,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_RIGHT] = {
        .utf8code = 0x2192, /*→*/
        .xUv = 355,
        .size = 4,
        .tex = sm64DS_latin_i4,
    },

    [UTF8_L_BUTTON] = {
        .utf8code = 0x1D40B, /*𝐋*/
        .xUv = 347,
        .size = 5,
        .tex = sm64DS_latin_i4,
    },
    [UTF8_R_BUTTON] = {
        .utf8code = 0x1D411, /*𝐑*/
        .xUv = 341,
        .size = 6,
        .tex = sm64DS_latin_i4,
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

fontChar sCharListPinball[] = {
    {
        .utf8code = ' ',
        .size = 16,
        .tex = NULL,
    },
    {
        .utf8code = '$',
        .xUv = 114,
        .size = 14,
        .tex = pinball_2_rgba16,
    },
    /*
    [UTF8_PERCENTAGE] = {
        .utf8code = '*',
        .xUv = 312,
        .tex = pinball_2_rgba16,
        .size = 6,
    },
    [UTF8_DASH] = {
        .utf8code = 0x2D,
        .xUv = 332,
        .tex = pinball_2_rgba16,
        .size = 4,
    },
    [UTF8_PERIOD] = {
        .utf8code = '.',
        .xUv = 300,
        .tex = pinball_2_rgba16,
        .size = 2,
    },
    [UTF8_SLASH] = {
        .utf8code = '/',
        .xUv = 373,
        .tex = pinball_2_rgba16,
        .size = 5,
    },
    */

    {
        .utf8code = '0',
        .xUv = 0,
        .tex = pinball_1_rgba16,
    },
    {
        .utf8code = '1',
        .xUv = 15,
        .tex = pinball_1_rgba16,
    },
    {
        .utf8code = '2',
        .xUv = 25,
        .tex = pinball_1_rgba16,
    },
    {
        .utf8code = '3',
        .xUv = 39,
        .tex = pinball_1_rgba16,
    },
    {
        .utf8code = '4',
        .xUv = 53,
        .tex = pinball_1_rgba16,
    },
    {
        .utf8code = '5',
        .xUv = 68,
        .tex = pinball_1_rgba16,
    },
    {
        .utf8code = '6',
        .xUv = 82,
        .tex = pinball_1_rgba16,
    },
    {
        .utf8code = '7',
        .xUv = 96,
        .tex = pinball_1_rgba16,
    },
    {
        .utf8code = '8',
        .xUv = 110,
        .tex = pinball_1_rgba16,
        .size = 14,
    },
    {
        .utf8code = '9',
        .xUv = 0,
        .tex = pinball_2_rgba16,
        .size = 14,
    },
    {
        .utf8code = 'X',
        .xUv = 14,
        .tex = pinball_2_rgba16,
        .size = 12
    },
    {
        .utf8code = 0x2605, /*★*/
        .xUv = 84,
        .size = 16,
        .tex = pinball_2_rgba16,
    },
};