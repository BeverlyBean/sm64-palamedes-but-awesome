#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "make_const_nonconst.h"
#include "levels/test/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_test_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _test_segment_7SegmentRomStart, _test_segment_7SegmentRomEnd), 
	LOAD_YAY0(0xa, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, test_area_1),
		WARP_NODE(1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(2, LEVEL_WF, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		BRIDGE_START(7, testbridge_collision, 886.2921752929688, 466.65478515625, 384.58197021484375),
		BRIDGE_END(5886.29248046875, 1271.6546630859375, 384.58209228515625),
		MARIO_POS(0x01, 0, -314, 471, 280),
		OBJECT(MODEL_NONE, 1431, -2153, -2569, 0, 0, 0, 0x00000000, bhvCoinFormation),
		CUBIC_VOLUME(6393.318359375, 49.11333465576172, -3944.277099609375,
			7.695290565490723, 0.8631196022033691, 0.7068579792976379,
			0.7820308804512024, 0.5485619306564331, -0.07849472761154175, -0.2852123975753784,
			VOLUME_TYPE_REGION,
			0),
		CUBIC_VOLUME(3399.93505859375, 795.8930053710938, 382.9988708496094,
			28.43522834777832, 4.556764602661133, 2.833754777908325,
			0.9966919422149658, 5.515833123581615e-08, -2.2366308805032986e-09, 0.08127211034297943,
			VOLUME_TYPE_BRIDGE,
			0),
		CUBIC_VOLUME(-1730.524658203125, -1421.517578125, -5725.19189453125,
			4.952780723571777, 4.889551162719727, 2.833753824234009,
			0.9238795638084412, -5.211227005474939e-08, 0.3826833963394165, -1.7277731245712857e-08,
			VOLUME_TYPE_WARP,
			1),
		CUBIC_VOLUME(-1018.3031005859375, -344.3511962890625, -7704.03369140625,
			4.952780723571777, 4.345637321472168, 3.2187211513519287,
			1.0, -7.769151988412659e-10, 0.0, 0.0,
			VOLUME_TYPE_WARP,
			2),
		OBJECT(MODEL_STAR, -1689, -1884, -1439, 0, 0, 0, 0x00000000, bhvStar),
		OBJECT(MODEL_NONE, 1846, -2153, -1345, 0, -104, 0, 0x00000000, bhvNPC),
		OBJECT(MODEL_NONE, 1846, -2153, -1672, 0, -65, 0, (1 << 16), bhvNPC),
		TERRAIN(test_area_1_collision),
		MACRO_OBJECTS(test_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -314, 471, 280),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};