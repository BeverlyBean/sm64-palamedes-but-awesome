#include "sm64.h"
#include "neo_save.h"
#include "src/data/text_enums.h"

u8 sFileNum = 0;

struct StarMission gStarMissionList[] = {
    [STAR_MISSION_TEST] = {
        .nameText = TEXT_MISSION_TEST,
        .hintText = TEXT_MISSION_TEST,
        .groupId = STAR_GROUP_TEST,
        .starType = STAR_TYPE_NORMAL
    },
};