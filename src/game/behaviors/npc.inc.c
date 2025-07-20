void bhv_npc(void) {

    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_PLACEHOLDER_NPC];

    if (gMarioState->usedObj == o && gEventHead) {
        o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, obj_angle_to_object(o,gMarioState->marioObj), 0x1000);
    }
}