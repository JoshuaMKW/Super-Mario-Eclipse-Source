#include "includes/eclipse.hxx"

//**MASTER GROUND HOOK**//
//0x80250CA0
/*
lhz r4, 0 (r3)
mr r3, r29
andi. r4, r4, 0x7FFF
cmplwi r4, 16010
beq- restoreFunction
cmplwi r4, 17010
beq- restoreFunction
cmplwi r4, 16020
beq- boostPanelFunction
cmplwi r4, 17020
beq- boostPanelFunction
cmplwi r4, 16021
beq- gravitySwitchFunction
cmplwi r4, 17021
beq- gravitySwitchFunction
cmplwi r4, 16040
beq- linkedWarpFunction
cmplwi r4, 17040
beq- linkedWarpFunction
subi r0, r4, 16041
cmplwi r0, 1
ble- linkedWarpPreserveFunction
subi r0, r4, 17041
cmplwi r0, 1
ble- linkedWarpPreserveFunction
cmplwi r4, 16080
beq- cannonFunction
cmplwi r4, 17080
beq- cannonFunction
subi r0, r4, 16090
cmplwi r0, 5
ble- changeFluddFunction
subi r0, r4, 17090
cmplwi r0, 5
ble- changeFluddFunction
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

linkedWarpFunction:
lis r0, 0x8000
ori r0, r0, 0x4AAC
b callFunction

linkedWarpPreserveFunction:
andi. r4, r0, 1
lis r0, 0x8000
ori r0, r0, 0x4AB0
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
void checkIsGlideBounce(TMario *gpMario, u32 state, u32 unk1, u32 unk2)
{
    if ((gpMario->mFloorTriangle->mCollisionType & 0x7FFF) == 16007 || (gpMario->mFloorTriangle->mCollisionType & 0x7FFF) == 17007)
    {
        gpMario->mCustomInfo->mTerminalVelocity = -20 * gpMario->mGravity;
        gpMario->mCustomInfo->CollisionFlags.mIsSpinBounce = true;
        state = TMario::STATE::JUMPSPIN1;
    }
    changePlayerStatus__6TMarioFUlUlb(gpMario, state, 0, 0);
}

//Restore Health Collision

//0x80004A94
void checkRestoreHealth(TMario *gpMario)
{
    if (gpMario->mCustomInfo->mCollisionTimer <= 0)
    {
        incHP__6TMarioFi(gpMario, 1);
        gpMario->mCustomInfo->mCollisionTimer = gpMario->mFloorTriangle->mValue4;
    }
    else
    {
        gpMario->mCustomInfo->mCollisionTimer -= 1;
    }
}

//0x8024C558
u16 checkIsRestoreTypeNoFallDamage(TBGCheckData *floor)
{
    if ((floor->mCollisionType & 0x7FFF) == 16010 || (floor->mCollisionType & 0x7FFF) == 17010)
    {
        return 10;
    }
    else
    {
        return floor->mCollisionType;
    }
}

//0x80004A98
void checkIsCannonType(TMario *gpMario)
{
    if (!gpMario->mController->isPressed(TMarioGamePad::BUTTONS::DPAD_UP) ||
        !gpMario->mCustomInfo->CollisionFlags.mIsFaceUsed)
        return;

    if ((gpMario->mFloorTriangle->mCollisionType & 0x7FFF) == 16080 || (gpMario->mFloorTriangle->mCollisionType & 0x7FFF) == 17080)
    {
        changePlayerStatus__6TMarioFUlUlb(gpMario, TMario::STATE::TRIPLE_J, 0, 0);
        emitParticle__6TMarioFis(gpMario, TMario::EFFECT::GROUND_SHARP_SHOCK);
        emitParticle__6TMarioFis(gpMario, TMario::EFFECT::GROUND_SMOKE_PLUME);
        gpMario->mForwardSpeed = (u8)(gpMario->mFloorTriangle->mValue4 >> 8);
        gpMario->mCoordinates.y += 1;
        gpMario->mSpeed.y = (u8)gpMario->mFloorTriangle->mValue4;
        gpMario->mCustomInfo->CollisionFlags.mIsDisableInput = true;
        gpMario->mController->setEnabled(false);
        gpMario->mCustomInfo->CollisionFlags.mIsFaceUsed = true;
    }
}

//0x80004A9C
void changeNozzleType(TMario *gpMario, u16 type)
{
    if (gpMario->mCustomInfo->CollisionFlags.mIsFaceUsed || !isMario__6TMarioFv(gpMario))
    {
        return;
    }

    gpMario->mAttributes.mHasFludd = gpMario->mFloorTriangle->mValue4 == 1;

    TWaterGun::NOZZLETYPE nozzle = TWaterGun::NOZZLETYPE::Hover;
    if (type >= 17090)
        nozzle = (TWaterGun::NOZZLETYPE)(type - 17090);
    else
        nozzle = (TWaterGun::NOZZLETYPE)(type - 16090);

    changeNozzle__9TWaterGunFQ29TWaterGun11TNozzleTypeb(gpMario->mFludd, nozzle, 1);
    gpMario->mCustomInfo->CollisionFlags.mIsFaceUsed = true;
}

//0x80004AA0
void boostPadCol(TMario *gpMario)
{
    gpMario->mForwardSpeed = gpMario->mFloorTriangle->mValue4;
    if (gpMario->mState == TMario::STATE::IDLE || !gpMario->mCustomInfo->CollisionFlags.mIsFaceUsed)
    {
        changePlayerStatus__6TMarioFUlUlb(gpMario, TMario::STATE::RUNNING, 0, 0);
        startVoice__6TMarioFUl(gpMario, TMario::VOICE::JUMP);
    }
}

//0x80004AA4
void setGravityCol(TMario *gpMario)
{
    gpMario->mGravity = (float)(gpMario->mFloorTriangle->mValue4) / 100.0f;
}

//0x80004AA8
void antiGravityCol(TMario *gpMario)
{
    if ((gpMario->mCoordinates.y - gpMario->mFloorTriangle->mMaxHeight) > gpMario->mFloorTriangle->mValue4 &&
        gpMario->mFloorTriangle->mValue4 != 0)
    {
        return;
    }
    gpMario->mSpeed.y = 10;
    if ((gpMario->mState & TMario::STATE::AIRBORN) == false)
    {
        gpMario->mCoordinates.y += 1;
        changePlayerStatus__6TMarioFUlUlb(gpMario, TMario::STATE::FALL, 0, 0);
    }
}

void warpToLinkedCol(TMario *gpMario)
{
    CPolarSubCamera *gpCamera = (CPolarSubCamera *)*(u32 *)CPolarSubCameraInstance;
    TBGCheckData *linkedCol = gInfo.mWarpColArray->resolveCollisionWarp(gpMario->mFloorTriangle);

    if (linkedCol == nullptr)
    {
        gpMario->mCustomInfo->mCollisionTimer = 0;
        return;
    }

    float speed = Vector3D::getResultant(gpMario->mSpeed);

    if (speed > 1)
    {
        gpMario->mCustomInfo->mCollisionTimer = 0;
        return;
    }

    if (!gpMario->mCustomInfo->CollisionFlags.mIsFaceUsed)
    {
        if (gpMario->mCustomInfo->mCollisionTimer > 140)
        {
            gpMario->mCoordinates = getTriCenter(linkedCol->mVertexA,
                                                 linkedCol->mVertexB,
                                                 linkedCol->mVertexC);
            gpMario->mFloorTriangle = linkedCol;
            gpMario->mFloorTriangleCopy = linkedCol;
            gpMario->mFloorBelow = gpMario->mCoordinates.y;
            gpMario->mCustomInfo->CollisionFlags.mIsFaceUsed = true;
            gpMario->mCustomInfo->mCollisionTimer = 0;
            startSoundActor__6TMarioFUl(gpMario, TMario::VOICE::JUMP);

            gpCamera->mCoordinates.x = lerp<float>(gpCamera->mCoordinates.x,
                                                   gpMario->mCoordinates.x,
                                                   0.9375);
            gpCamera->mCoordinates.y = gpMario->mCoordinates.y + 300;
            gpCamera->mCoordinates.z = lerp<float>(gpCamera->mCoordinates.z,
                                                   gpMario->mCoordinates.z,
                                                   0.9375);
            gpCamera->mHorizontalAngle = getYAngleBetween<u16>(gpMario->mCoordinates,
                                                               gpCamera->mCoordinates) * 182;
        }
        else if (gpMario->mCustomInfo->mCollisionTimer > 80)
        {
            gpMario->mCustomInfo->CollisionFlags.mIsDisableInput = true;
            gpMario->mController->setEnabled(false);
            emitGetEffect__6TMarioFv(gpMario);
        }
    }
    else
    {
        if (gpMario->mCustomInfo->mCollisionTimer > 60)
        {
            gpMario->mCustomInfo->CollisionFlags.mIsDisableInput = false;
            gpMario->mController->setEnabled(false);
        }
    }
    gpMario->mCustomInfo->mCollisionTimer += 1;
}

void warpToLinkedColPreserve(TMario *gpMario, bool fluid)
{
    CPolarSubCamera *gpCamera = (CPolarSubCamera *)*(u32 *)CPolarSubCameraInstance;
    TBGCheckData *linkedCol = gInfo.mWarpColArray->resolveCollisionWarp(gpMario->mFloorTriangle);

    if (linkedCol == nullptr)
        return;

    if (!gpMario->mCustomInfo->CollisionFlags.mIsFaceUsed)
    {
        gpMario->mFloorTriangle = linkedCol;
        gpMario->mFloorTriangleCopy = linkedCol;
        gpMario->mCustomInfo->CollisionFlags.mIsFaceUsed = true;

        gpMario->mCoordinates = getTriCenter(linkedCol->mVertexA,
                                             linkedCol->mVertexB,
                                             linkedCol->mVertexC);

        gpCamera->mCoordinates.x = lerp<float>(gpCamera->mCoordinates.x,
                                               gpMario->mCoordinates.x,
                                               0.9375);
        gpCamera->mCoordinates.y = gpMario->mCoordinates.y + 300;
        gpCamera->mCoordinates.z = lerp<float>(gpCamera->mCoordinates.z,
                                               gpMario->mCoordinates.z,
                                               0.9375);
        gpCamera->mHorizontalAngle = getYAngleBetween<u16>(gpMario->mCoordinates,
                                                           gpCamera->mCoordinates) * 182;

        JGeometry::TVec3<float> colNormal = Vector3D::getNormal(linkedCol->mVertexA, linkedCol->mVertexB, linkedCol->mVertexC, false);
        JGeometry::TVec3<float> colUnit = Vector3D::getUnitVector(colNormal);

        float magnitude = fabsf__Ff(gpMario->mSpeed.x) + fabsf__Ff(gpMario->mSpeed.y) + fabsf__Ff(gpMario->mSpeed.z);

        gpMario->mAngle.y = Vector3D::getNormalAngle<u16>(colNormal) * 182;
        setPlayerVelocity__6TMarioFf(gpMario, magnitude * colUnit.x + magnitude * colUnit.z);
        gpMario->mSpeed.y = magnitude * colUnit.y;

        gpMario->mCoordinates.x += 40 * colUnit.x;
        gpMario->mCoordinates.y += 40 * colUnit.y;
        gpMario->mCoordinates.z += 40 * colUnit.z;

        changePlayerStatus__6TMarioFUlUlb(gpMario, TMario::STATE::FALL, 0, 0);
    }
    else
    {
        gpMario->mCustomInfo->CollisionFlags.mIsFaceUsed = (!gpMario->mController->isFramePressed(TMarioGamePad::BUTTONS::DPAD_DOWN) && !fluid);
    }
}

inline void resetValuesOnStateChange(TMario *gpMario)
{
    switch (gpMario->mPrevState)
    {
    case (TMario::STATE::JUMPSPIN1):
        gpMario->mCustomInfo->mTerminalVelocity = -75 * gpMario->mGravity;
        gpMario->mCustomInfo->CollisionFlags.mIsSpinBounce = false;
    case (TMario::STATE::TRIPLE_J):
        gpMario->mCustomInfo->CollisionFlags.mIsDisableInput = false;
        gpMario->mController->setEnabled(true);
    }
    if (gpMario->mCustomInfo->CollisionFlags.mIsDisableInput)
    { //Patches pausing/map escaping the controller lock
        gpMario->mController->setEnabled(false);
    }
}

inline void resetValuesOnGroundContact(TMario *gpMario)
{
    if ((gpMario->mState & TMario::STATE::AIRBORN) == false)
    {
        gpMario->mCustomInfo->mTerminalVelocity = -75 * gpMario->mGravity;
        gpMario->mCustomInfo->CollisionFlags.mIsAirborn = false;
        gpMario->mCustomInfo->CollisionFlags.mIsDisableInput = false;
    }
}

inline void resetValuesOnAirborn(TMario *gpMario)
{
    if ((gpMario->mState & TMario::STATE::AIRBORN) == false)
    {
        return;
    }
}

inline void resetValuesOnCollisionChange(TMario *gpMario)
{
    if (gpMario->mFloorTriangle->mCollisionType != gpMario->mCustomInfo->mPrevCollision)
    {
        gpMario->mCustomInfo->mPrevCollision = gpMario->mFloorTriangle->mCollisionType;
        gpMario->mCustomInfo->CollisionFlags.mIsFaceUsed = false;
        gpMario->mCustomInfo->mCollisionTimer = 0;
    }
}

//0x802500B8
u32 resetValues(TMario *gpMario)
{
    resetValuesOnStateChange(gpMario);
    resetValuesOnGroundContact(gpMario);
    resetValuesOnAirborn(gpMario);
    resetValuesOnCollisionChange(gpMario);
    return 1;
}