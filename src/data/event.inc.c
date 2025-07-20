#include "src/data/text_enums.h"
#include "levels/test/header.inc.h"

EventData testOption1[] = {
    E_SPLINE(test_area_1_spline_testPos,test_area_1_spline_testFoc),
    E_DIALOG(TEXT_TEST_4),
    E_RETURN_TO_CONVERSATION(),
    E_END_BRANCH(),
};

EventData testOption2[] = {
    E_DIALOG(TEXT_TESTCHOICE_2),
    E_END_BRANCH(),
};

EventData testNPC[] = {
    E_DIALOG(TEXT_TEST_2),
    E_DIALOG(TEXT_TEST_3),
    E_DIALOG_CHOICE(TEXT_TESTCHOICE_1,testOption1),
    E_DIALOG_CHOICE(TEXT_TESTCHOICE_2,testOption2),
    E_DIALOG_CHOICE(TEXT_TESTCHOICE_3,testNPC),
    E_DIALOG(TEXT_TEST_PROMPT),
    E_DIALOG(TEXT_TEST_END),
    E_END(),
};