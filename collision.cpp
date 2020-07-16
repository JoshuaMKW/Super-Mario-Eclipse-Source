#include "includes/eclipse.hxx"

//**MASTER GROUND HOOK**//
//0x80250CA0
/*
lhz r4, 0 (r3)
mr r3, r29
andi. r4, r4, 0x7FFF
cmplwi r4, 16010
beq restoreFunction
cmplwi r4, 17010
beq restoreFunction
cmplwi r4, 16020
beq boostPanelFunction
cmplwi r4, 17020
beq boostPanelFunction
cmplwi r4, 16021
beq gravitySwitchFunction
cmplwi r4, 17021
beq gravitySwitchFunction
cmplwi r4, 16080
beq cannonFunction
cmplwi r4, 17080
beq cannonFunction
subi r0, r4, 16090
cmplwi r0, 5
ble changeFluddFunction
subi r0, r4, 17090
cmplwi r0, 5
ble changeFluddFunction
b pass

restoreFunction:
lis r0, 0x8000
ori r0, r0, 0x4A94
b callFunction

cannonFunction:
lis r0, 0x8000
ori r0, r0, 0x4A98
b callFunction

changeFluddFunction:
lis r0, 0x8000
ori r0, r0, 0x4A9C
b callFunction

boostPanelFunction:
lis r0, 0x8000
ori r0, r0, 0x4AA0
b callFunction

gravitySwitchFunction:
lis r0, 0x8000
ori r0, r0, 0x4AA4
b callFunction

callFunction:
mtctr r0
bctrl

pass:
lwz r3, 0xE0 (r29)
lhz r0, 0 (r3)
*/

//**MASTER ALL HOOK**//
//0x8025059C
/*
mr r28, r3
lwz r3, 0xE0 (r3)
lhz r4, 0 (r3)
andi. r4, r4, 0x7FFF
cmplwi r4, 16022
beq gravitySwitchFunction
cmplwi r4, 17022
beq gravitySwitchFunction
cmplwi r4, 16023
beq reverseGravityFunction
cmplwi r4, 17023
beq reverseGravityFunction
subi r0, r4, 16100
cmplwi r0, 5
ble changeFluddFunction
subi r0, r4, 17100
cmplwi r0, 5
ble changeFluddFunction
b pass

changeFluddFunction:
mr r3, r28
subi r4, r4, 10
lis r0, 0x8000
ori r0, r0, 0x4A9C
b callFunction

gravitySwitchFunction:
mr r3, r28
lis r0, 0x8000
ori r0, r0, 0x4AA4
b callFunction

reverseGravityFunction:
mr r3, r28
lis r0, 0x8000
ori r0, r0, 0x4AA8
b callFunction

callFunction:
mtctr r0
bctrl

pass:
mr r3, r28
lwz r0, 0x7C (r3)
*/

/*
62 * 256 + 135 (16007) == Spin Bounce
66 * 256 + 111 (17007) == Spin Bounce Shaded
62 * 256 + 138 (16010) == No Fall Damage Restore Health        | Option 4 frames to regenerate
66 * 256 + 114 (17010) == No Fall Damage Restore Health Shaded | Option 4 frames to regenerate
62 * 256 + 208 (16080) == Cannon Shot                          | Option 4 forward/upward speed
66 * 256 + 184 (17080) == Cannon Shot Shaded                   | Option 4 forward/upward speed
62 * 256 + 218 (16090) == Spray Nozzle                         | Option 4 has fludd?
66 * 256 + 194 (17090) == Spray Nozzle Shaded                  | Option 4 has fludd?
62 * 256 + 222 (16094) == Hover Nozzle                         | Option 4 has fludd?
66 * 256 + 198 (17094) == Hover Nozzle Shaded                  | Option 4 has fludd?
62 * 256 + 219 (16091) == Rocket Nozzle                        | Option 4 has fludd?
66 * 256 + 195 (17091) == Rocket Nozzle Shaded                 | Option 4 has fludd?
62 * 256 + 223 (16095) == Turbo Nozzle                         | Option 4 has fludd?
66 * 256 + 199 (17095) == Turbo Nozzle Shaded                  | Option 4 has fludd?
62 * 256 + 220 (16092) == UnderWater Nozzle                    | Option 4 has fludd?
66 * 256 + 196 (17092) == UnderWater Nozzle Shaded             | Option 4 has fludd?
62 * 256 + 221 (16093) == Yoshi Nozzle                         | Option 4 has fludd?
66 * 256 + 197 (17093) == Yoshi Nozzle Shaded                  | Option 4 has fludd?
*/

//Twirl Bounce Collision

//0x802523D4
/*
lhz r0, 0 (r3)
cmplwi r0, 16007
beq bounce
cmplwi r0, 17007
bne pass
bounce:
li r0, 7
pass:
*/

//0x80252430
/*
lwz r6, 0xE0 (r31)
lhz r6, 0 (r6)
cmplwi r6, 16007
beq bounce
cmplwi r6, 17007
bne pass
bounce:
ori r0, r0, 0x800
pass:
rlwinm. r0, r0, 0, 20, 20
*/

//0x80254750
/*
.set .LCPI3_0, 0x800034F0

        stwu 1, -16(1)
        lbz 4, 328(30)
        andi. 4, 4, 32
        beq     0, .LBB3_2
        lwz 4, 224(30)
        lis 5, 17200
        lha 4, 2(4)
        stw 5, 8(1)
        xoris 4, 4, 32768
        stw 4, 12(1)
        lis 4, .LCPI3_0@ha
        lfd 0, 8(1)
        lfs 1, .LCPI3_0@l(4)
        fsub 0, 0, 1
        frsp 0, 0
.LBB3_2:
        stfs 0, 168(30)
        li 4, 30902
        addi 1, 1, 16
*/

//0x8025246C
void checkIsGlideBounce(TMario* gpMario, u32 state, u32 unk1, u32 unk2) {
    if ((gpMario->mFloorTriangle->mCollisionType & 0x7FFF) == 16007 || (gpMario->mFloorTriangle->mCollisionType & 0x7FFF) == 17007) {
        gpMario->mTerminalVelocity = -20 * gpMario->mGravity;
        gpMario->CollisionFlags.mIsSpinBounce = true;
        state = STATE_JUMPSPIN1;
    }
    changePlayerStatus__6TMarioFUlUlb(gpMario, state, 0, 0);
}

//Restore Health Collision

//0x80004A94
void checkRestoreHealth(TMario* gpMario) {
    if (gpMario->mColHealthTimer == 0) {
        incHP__6TMarioFi(gpMario, 1);
        gpMario->mColHealthTimer = gpMario->mFloorTriangle->mValue4;
    } else {
        gpMario->mColHealthTimer -= 1;
    }
}


//0x8024C558
u16 checkIsRestoreTypeNoFallDamage(TBGCheckData* floor) {
    if ((floor->mCollisionType & 0x7FFF) == 16010 || (floor->mCollisionType & 0x7FFF) == 17010) {
        return 10;
    } else {
        return floor->mCollisionType;
    }
}

//0x80004A98
void checkIsCannonType(TMario* gpMario) {
    if (gpMario->mController->Buttons.mDPadUp == false || gpMario->CollisionFlags.mIsFaceUsed == false)
        return;

    if ((gpMario->mFloorTriangle->mCollisionType & 0x7FFF) == 16080 || (gpMario->mFloorTriangle->mCollisionType & 0x7FFF) == 17080) {
        changePlayerStatus__6TMarioFUlUlb(gpMario, STATE_TRIPLE_J, 0, 0);
        gpMario->mForwardSpeed = (u8)(gpMario->mFloorTriangle->mValue4 >> 8);
        gpMario->mTakeActor.mHitActor.mActor.mCoordinates.y += 1;
        gpMario->mSpeed.y = (u8)gpMario->mFloorTriangle->mValue4;
        gpMario->CollisionFlags.mIsDisableInput = true;
        gpMario->mController->State.mReadInput = false;
        gpMario->CollisionFlags.mIsFaceUsed = true;
    }
}

//0x80004A9C
void changeNozzleType(TMario* gpMario, u16 type) {
    if (gpMario->CollisionFlags.mIsFaceUsed == true) {
        return;
    }
    if (gpMario->mFloorTriangle->mValue4 == 1) {
        gpMario->mAttributes.mHasFludd = true;
    } else {
        gpMario->mAttributes.mHasFludd = false;
    }

    u8 nozzle = HOVER_NOZZLE;
    if (type >= 17090) nozzle = type - 17090;
    else nozzle = type - 16090;

    changeNozzle__9TWaterGunFQ29TWaterGun11TNozzleTypeb(gpMario->mFludd, nozzle, 1);
    gpMario->CollisionFlags.mIsFaceUsed = true;
}

//0x80004AA0
void boostPadCol(TMario* gpMario) {
    gpMario->mForwardSpeed = gpMario->mFloorTriangle->mValue4;
    if (gpMario->mState == STATE_IDLE || gpMario->CollisionFlags.mIsFaceUsed == false) {
        changePlayerStatus__6TMarioFUlUlb(gpMario, STATE_RUNNING, 0, 0);
        startVoice__6TMarioFUl(gpMario, VOICE_TJUMP);
    }
}

//0x80004AA4
void setGravityCol(TMario* gpMario) {
    gpMario->mGravity = (float)(gpMario->mFloorTriangle->mValue4) / 100.0f;
}

//0x80004AA8
void antiGravityCol(TMario* gpMario) {
    if ((gpMario->mTakeActor.mHitActor.mActor.mCoordinates.y - gpMario->mFloorTriangle->mMaxHeight) > gpMario->mFloorTriangle->mValue4 &&
        gpMario->mFloorTriangle->mValue4 != 0) {
        return;
    }
    gpMario->mSpeed.y = 10;
    if ((gpMario->mState & STATE_AIRBORN) == false) {
        gpMario->mTakeActor.mHitActor.mActor.mCoordinates.y += 1;
        changePlayerStatus__6TMarioFUlUlb(gpMario, STATE_FALL, 0, 0);
    }
}


inline void resetValuesOnStateChange(TMario* gpMario) {
    switch(gpMario->mPrevState) {
    case(STATE_JUMPSPIN1):
        gpMario->mTerminalVelocity = -75 * gpMario->mGravity;
        gpMario->CollisionFlags.mIsSpinBounce = false;
    case(STATE_TRIPLE_J):
        gpMario->CollisionFlags.mIsDisableInput = false;
        gpMario->mController->State.mReadInput = true;
    }
    if (gpMario->CollisionFlags.mIsDisableInput == true) { //Patches pausing/map escaping the controller lock
        gpMario->mController->State.mReadInput = false;
    }
}

inline void resetValuesOnGroundContact(TMario* gpMario) {
    if ((gpMario->mState & STATE_AIRBORN) == false) {
        gpMario->mTerminalVelocity = -75 * gpMario->mGravity;
        gpMario->CollisionFlags.mIsAirborn = false;
        gpMario->CollisionFlags.mIsDisableInput = false;
    }
}

inline void resetValuesOnAirborn(TMario* gpMario) {
    if ((gpMario->mState & STATE_AIRBORN) == false) {
        return;
    }
}

inline void resetValuesOnCollisionChange(TMario* gpMario) {
    if (gpMario->mFloorTriangle->mCollisionType != gpMario->mPrevCollision) {
        gpMario->mPrevCollision = gpMario->mFloorTriangle->mCollisionType;
        gpMario->CollisionFlags.mIsFaceUsed = false;
    }
}

//0x802500B8
u32 resetValues(TMario* gpMario) {
    resetValuesOnStateChange(gpMario);
    resetValuesOnGroundContact(gpMario);
    resetValuesOnAirborn(gpMario);
    resetValuesOnCollisionChange(gpMario);
    return 1;
}