#include "includes/yoshi.hxx"

//kWrite32(0x8026EE14, 0x4800020C); Yoshi can't starve
//kWrite32(0x8026E068, 0x2C000001); Turn green when out of juice
//kWrite32(0x8026E0A0, 0x60000000); No flickering

//kWrite32(0x801BC770, 0x3800000C);

//kWrite32(0x801BC870, 0x60000000);
//kWrite32(0x801BC900, 0x60000000);

//0x801BC868
bool isYoshiEggNeedFruit(THitActor* gpFruit) {
    if (!gInfo.mFile || gInfo.mFile->FileHeader.mIsYoshi == false || gInfo.mFile->Yoshi.mIsEggFree == false) {
        return isFruit__11TMapObjBaseFP9THitActor(gpFruit);
    }
    return true;
}

//0x801BC8B4
u8 isYoshiEggFree(TEggYoshi* gpEgg, THitActor* gpFruit) {
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;

    if (gpEgg->mObjBase.mState == 14 ||
        gpEgg->mObjBase.mState == 6 ||
        gpMario->mCanRideYoshi == false)
        return 0;
    
    if (!gInfo.mFile || gInfo.mFile->FileHeader.mIsYoshi == false || gInfo.mFile->Yoshi.mIsEggFree == false) {
        if (gpEgg->mWantedFruit != gpFruit->mObjectID) return 2;
        else return 1;
    } else {
        return 1;
    }
}

//0x8024D690 - Keep Fludd gone if not collected on yoshi
/*
mr r3, r31 #TMario
lis r4, 0x8000
ori r4, r4, 0x4A74 #0x80004A74
mtctr r4
bctrl
cmpwi r3, 0
*/

//0x80004A74
bool isYoshiMaintainFluddModel(TMario* gpMario) {
    if (gpMario->mYoshi->mState == MOUNTED) return (gInfo.Fludd.mHadFludd & gpMario->mAttributes.mHasFludd);
    else return gpMario->mAttributes.mHasFludd;
}


//0x8024F240
void isYoshiDrown(TYoshi* gpYoshi) {
    if (isGreenYoshi(gpYoshi) == false) {
        disappear__6TYoshiFv(gpYoshi);
    }
}

//kWrite32(0x8024EBA0, 0x28030000);
//kWrite32(0x8024EBA4, 0x4182008C);

//kWrite32(0x8026EB04, 0x2C030000);
//kWrite32(0x8026EB08, 0x41820518);

//kWrite32(0x8026EC00, 0x2C030000);
//kWrite32(0x8026EC04, 0x4182041C);

//0x8026EB00
//0x8026EBFC
//0x8026F218
bool isYoshiDie(TMario* gpMario) {
    return isGreenYoshi(gpMario->mYoshi) == false;
}

//kWrite32(0x8026F21C, 0x2C030000);
//kWrite32(0x8026F220, 0x41820164);

//0x80281100
/*
stwu sp, -0x10 (sp)
stw r30, 0x8 (sp)
mr r30, r4
lis r4, 0x8000
ori r4, r4, 0x4A6C
mtctr r4
mr r4, r31
bctrl
mr r4, r30
lwz r30, 0x8 (sp)
addi sp, sp, 0x10
cmpwi r3, 0
*/

//0x80004A6C
bool canMountYoshi(u32 marioState, TMario* gpMario) {
    if ((marioState & STATE_WATERBORN) && gpMario->mCanRideYoshi)
        return true;
    else return ((marioState & STATE_AIRBORN) && gpMario->mCanRideYoshi);
}

//0x8026E810
void fixYoshiJuiceDecrement() {
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;
    if (!gpMario->mYoshi)
        return;

    if (gpMario->mFludd->mIsEmitWater == true && gpMario->mYoshi->mState == MOUNTED) {
        gpMario->mYoshi->mCurJuice -= gpMario->mFludd->mEmitInfo[0x18 / 4];
    }
}

//0x8024E58C
void canYoshiSpray(TWaterGun* gpWaterGun) {
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;
    if (!gpMario->mYoshi)
        return;

    if (isGreenYoshiMounted(gpMario->mYoshi) == false) {
        emit__9TWaterGunFv(gpWaterGun);
    }
}

//0x80273198
u32 calcYoshiSwimVelocity(TMario* gpMario, u32 arg1) {

    if (!gInfo.mFile || gInfo.mFile->FileHeader.mIsYoshi == false) {
        return jumpProcess__6TMarioFi(gpMario, arg1);
    } else if (gInfo.mFile->Yoshi.mYoshiHungry == true) {
        return jumpProcess__6TMarioFi(gpMario, arg1);
    }

    if (!gpMario->mYoshi)
        return jumpProcess__6TMarioFi(gpMario, arg1);

    if (isGreenYoshiMounted(gpMario->mYoshi) == false)
        return jumpProcess__6TMarioFi(gpMario, arg1);

    if (gpMario->mController->Buttons.mAButton == true) {
        if (gInfo.Mario.yoshiWaterSpeed.y > 12) {
            gInfo.Mario.yoshiWaterSpeed.y = 12;
        } else {
            gInfo.Mario.yoshiWaterSpeed.y += 0.34375;
        }
    } else {
        if (gInfo.Mario.yoshiWaterSpeed.y < -12) {
            gInfo.Mario.yoshiWaterSpeed.y = -12;
        } else {
            gInfo.Mario.yoshiWaterSpeed.y -= 0.34375;
        }
    }
    gpMario->mSpeed.y = gInfo.Mario.yoshiWaterSpeed.y;
    return jumpProcess__6TMarioFi(gpMario, arg1);
}

/*Flutter in water, needs to be gecko code ;n;*/ 
//0x8026FF04
u32 isYoshiWaterFlutter(u32 state, u32 copystate, TMario* gpMario) {

    if (!gInfo.mFile || gInfo.mFile->FileHeader.mIsYoshi == false) {
        return gpMario->mYoshi->mFlutterState;
    } else if (gInfo.mFile->Yoshi.mYoshiHungry == false) {
        return gpMario->mYoshi->mFlutterState;
    }

    if (isGreenYoshiAscendingWater(gpMario)) {
        return 1;
    } else {
        return gpMario->mYoshi->mFlutterState;
    }
}

//0x8026FE84 NEEDS ADDI R4, R3, 0
u32 isYoshiValidWaterFlutter(s32 anmIdx, u32 unk1, TMario* gpMario) {
    if (!gInfo.mFile || gInfo.mFile->FileHeader.mIsYoshi == false) {
        return gpMario->mState;
    } else if (gInfo.mFile->Yoshi.mYoshiHungry == true) {
        return gpMario->mState;
    }

    if (isGreenYoshiAscendingWater(gpMario)) {
        return gpMario->mState & 0xFFFFFBFF | STATE_AIRBORN;
    } else {
        return gpMario->mState;
    }
}

//kWrite32(0x8026FF08, 0x28030001);

//0x8024E788
bool isYoshiValidDrip() {
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;
    return gpMario->mYoshi->mState == MOUNTED && isGreenYoshi(gpMario->mYoshi) == false;
}

void maintainYoshi() {
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;
    if (isGreenYoshi(gpMario->mYoshi)) {
        *(u32*)0x80415F4C = 0x43F00000;
        *(u32*)0x80415F68 = 0x46800000;
    } else {
        *(u32*)0x80415F4C = 0x43960000;
        *(u32*)0x80415F68 = 0x461C4000;
    }
}


//Hook with this asm:
/*0x801BC114
addi r3, r31, 0
lis r4, 0x8000
ori r4, r4, 0x4A68
mtctr r4
bctrl
lwz r0, 0x0054 (sp)

0x801BC380
addi r3, r31, 0
lis r4, 0x8000
ori r4, r4, 0x4A68
mtctr r4
bctrl
li r3, 0
*/

//0x80004A68
void checkForFreeEggCard(TEggYoshi* gpEgg) {
    if (!gInfo.mFile || gInfo.mFile->FileHeader.mIsYoshi == false || gInfo.mFile->Yoshi.mIsEggFree == false)
        return;

    if (!gpEgg->mActor)
        return;
    TBckData* bckData = (TBckData*)getFrameCtrl__6MActorFi(gpEgg->mActor, 3);
    bckData->mFrameRate = 11;
}

//0x8028121C
void saveNozzles(TYoshi* gpYoshi, TMario* gpMario) {
    gInfo.Fludd.mCurrentNozzle = gpMario->mFludd->mCurrentNozzle;
    gInfo.Fludd.mSecondNozzle = gpMario->mFludd->mSecondNozzle;
    gInfo.Fludd.mCurrentWater = gpMario->mFludd->mCurrentWater;
    gInfo.Fludd.mHadFludd = gpMario->mAttributes.mHasFludd;
    ride__6TYoshiFv(gpYoshi);
}

//0x8024EC18
void restoreNozzles(TMario* gpMario) {
    float factor = (float)gInfo.Fludd.mCurrentWater / (float)gpMario->mFludd->mNozzleList[(u8)gInfo.Fludd.mCurrentNozzle]->mMaxWater;
    changeNozzle__9TWaterGunFQ29TWaterGun11TNozzleTypeb(gpMario->mFludd, gInfo.Fludd.mSecondNozzle, 1);
    normalizeNozzle__6TMarioFv(gpMario);
    gpMario->mFludd->mCurrentWater = gpMario->mFludd->mNozzleList[(u8)gpMario->mFludd->mCurrentNozzle]->mMaxWater * factor;
    gpMario->mAttributes.mHasFludd = gInfo.Fludd.mHadFludd;
}

//kWrite32(0x8024EC2C, 0x60000000);