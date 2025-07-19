#include "text_load.h"

#include "src/data/text.inc.c"

int gLanguage = LANGUAGE_ENGLISH;

char ** sLanguageTable[] = {
    [LANGUAGE_ENGLISH] = sEnglishText,
    [LANGUAGE_GERMAN] = sGermanText,
};

char * get_text(int textEnum) {
    return sLanguageTable[gLanguage][textEnum];
}