#include "includes/eclipse.hxx"

#ifdef SME_DEBUG
    //0x802A615C
    TMarDirector* xyzModifierMario(TMarDirector* gpMarDirector) {
        TMario* gpMario = (TMario*)*(u32*)TMarioInstance;
        JGeometry::TVec3<float>* gpMarioCoordinates = (JGeometry::TVec3<float>*)&gpMario->mTakeActor.mHitActor.mActor.mCoordinates;
        if (!gpMario) {
            return gpMarDirector;
        }

        if ((u32*)gpMario->mController < MEM1_LO || (u32*)gpMario->mController >= MEM1_HI) {
            return gpMarDirector;
        }

        if (gpMario->mController->Buttons.mDPadRight && *(bool*)0x80003ED0 == false) {
            *(bool*)0x80003ED0 = true;
        } else if (gpMario->mController->Buttons.mDPadLeft && *(bool*)0x80003ED0 == true) {
            if (gpMario->mPrevState != 0x133F) {
                changePlayerStatus__6TMarioFUlUlb(gpMario, gpMario->mPrevState, 0, 0);
            } else {
                gpMario->mState = STATE_IDLE;
            }
            *(bool*)0x80003ED0 = false;
        }

        if (*(bool*)0x80003ED0 == true) {
            gpMario->mState = STATE_IDLE | STATE_CUTSCENE;
            float speedMultiplier = linearInterpolate<float>(1, 2, gpMario->mController->mRButtonAnalogFloat);
            gpMarioCoordinates->x += ((gpMario->mController->mMainStickLeftRight * 83) * speedMultiplier);
            gpMarioCoordinates->z -= ((gpMario->mController->mMainStickUpDown * 83) * speedMultiplier);

            if (gpMario->mController->Buttons.mDPadDown) {
                gpMarioCoordinates->y -= (83 * speedMultiplier);
            } else if (gpMario->mController->Buttons.mDPadUp) {
                gpMarioCoordinates->y += (83 * speedMultiplier);
            }
        }
        return gpMarDirector;
    }

    //0x802A8064
    u32 set_debugger() {
        TMario* gpMario = (TMario*)*(u32*)TMarioInstance;
        TFlagManager* gpFlagManager = (TFlagManager*)*(u32*)TFlagManagerInstance;
        TWaterManager* gpWaterManager = (TWaterManager*)*(u32*)TWaterManagerInstance;
        
        if (!gpWaterManager || !gpMario || ((u32*)gpMario->mController < MEM1_LO || (u32*)gpMario->mController >= MEM1_HI)) {
            return 0;
        }

        if (gpMario->mController->Buttons.mBButton && gpMario->mController->Buttons.mDPadUp) {
            gpWaterManager->mLayerCount += 1;
        } else if (gpMario->mController->Buttons.mBButton && gpMario->mController->Buttons.mDPadDown) {
            gpWaterManager->mLayerCount -= 1;
        } else if (gpMario->mController->Buttons.mBButton && gpMario->mController->Buttons.mDPadRight) {
            gpFlagManager->Type4Flag.mShineCount += 1;
        } else if (gpMario->mController->Buttons.mBButton && gpMario->mController->Buttons.mDPadLeft) {
            gpFlagManager->Type4Flag.mShineCount -= 1;
        } else if (gpMario->mController->Buttons.mXButton && gpMario->mController->Buttons.mDPadUp) {
            *(s16*)0x8027C90E += 1;
            if (*(s16*)0x8027C90E > 7) {
                *(s16*)0x8027C90E = 7;
            }
            flushAddr((void*)0x8027C90C);
        } else if (gpMario->mController->Buttons.mXButton && gpMario->mController->Buttons.mDPadDown) {
            *(s16*)0x8027C90E -= 1;
            if (*(s16*)0x8027C90E < 0) {
                *(s16*)0x8027C90E = 0;
            }
            flushAddr((void*)0x8027C90C);
        }
        return 0;
    }

    //0x80243940
    TMario* warpMario(TMario* gpMario) {
        warpInEffect__6TMarioFv(gpMario);
        return gpMario;
    }
#endif

//0x802A8B58
bool SMS_IsExMap() {
    TApplication* gpApplication = (TApplication*)0x803E9700;
    if (gInfo.mFile) {
        return gInfo.mFile->FileHeader.StageType.mIsExMap;
    } else {
        return (gpApplication->mCurAreaID > 20 && gpApplication->mCurAreaID < 53);
    }
}

//0x802A8B30
bool SMS_IsMultiplayerMap() {
    TMarDirector* gpMarDirector = (TMarDirector*)*(u32*)TMarDirectorInstance;
    if (gInfo.mFile) {
        return gInfo.mFile->FileHeader.StageType.mIsMultiPlayerMap;
    } else {
        return (gpMarDirector->mAreaID == 12 && gpMarDirector->mEpisodeID == 0);
    }
}

//0x802A8AFC
bool SMS_IsDivingMap() {
    TMarDirector* gpMarDirector = (TMarDirector*)*(u32*)TMarDirectorInstance;
    if (gInfo.mFile) {
        return gInfo.mFile->FileHeader.StageType.mIsDivingMap;
    } else {
        return (gpMarDirector->mAreaID == 57 ||
                gpMarDirector->mAreaID == 44 ||
                gpMarDirector->mAreaID == 16);
    }
}

//0x802A8AE0
bool SMS_IsOptionMap() {
    TMarDirector* gpMarDirector = (TMarDirector*)*(u32*)TMarDirectorInstance;
    if (gInfo.mFile) {
        return gInfo.mFile->FileHeader.StageType.mIsOptionMap;
    } else {
        return (gpMarDirector->mAreaID == 15);
    }
}

//0x801BD664
void manageShineVanish(JGeometry::TVec3<float>* marioPos) {
    TMarDirector* gpMarDirector = (TMarDirector*)*(u32*)TMarDirectorInstance;
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;
    TShine* gpShine = gpMarDirector->mCollectedShine;
    JDrama::TActor shineData = gpShine->mObj.mLiveActor.mTakeActor.mHitActor.mActor;

    if (shineData.mSize.x - 0.01055 <= 0) {
        shineData.mSize = { 1, 1, 1 };
        gpShine->mGlowSize = { 1, 1, 1 };
        shineData.mRotation.y = 0;
        makeObjDead__11TMapObjBaseFv(gpShine);
    } else if (gpMario->mState != STATE_SHINE_C) {
        shineData.mCoordinates.y += 4;
        shineData.mSize.x -= 0.01055;
        shineData.mSize.y -= 0.01055;
        shineData.mSize.z -= 0.01055;
        gpShine->mGlowSize.x -= 0.01055;
        gpShine->mGlowSize.y -= 0.01055;
        gpShine->mGlowSize.z -= 0.01055;
        shineData.mRotation.y += 3;
    } else {
        shineData.mCoordinates = *marioPos;
    }
}

//kWrite32(0x801BD668, 0x48000568);

//0x802413E0
void isKillEnemiesShine(TConductor* gpConductor, JGeometry::TVec3<float>* gpMarioCoordinates, float range) {
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;
    TShine* gpShine = (TShine*)gpMario->mGrabTarget;
    if ((gpShine->mType & 0x10) == false) {
        killEnemiesWithin__10TConductorFRCQ29JGeometry8TVec3_f(gpConductor, gpMarioCoordinates, range);
    }
}

void restoreMario(TMarDirector* gpMarDirector, u32 curState) {
    TShine* gpShine = (TShine*)gpMarDirector->mCollectedShine;
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;
    CPolarSubCamera* gpCamera = (CPolarSubCamera*)*(u32*)CPolarSubCameraInstance;

    if (!gpShine || !(gpShine->mType & 0x10)) return;
    if (!gpMarDirector->sNextState) return;

    u8* curSaveCard = (u8*)(gpMarDirector->sNextState[0x118 / 4]);

    if ((curState != NORMAL) || (gpMarDirector->mLastState != SAVE_CARD)) return;
    if (gpMario->mState != 0x1302) return;

    if (curSaveCard[0x2E9] != 1) {
        if (SMS_isDivingMap__Fv() || (gpMario->mPrevState & 0x20D0) == 0x20D0) {
            gpMario->mState = gpMario->mPrevState;
        } else {
            gpMario->mState = STATE_IDLE;
        }
        startStageBGM__10MSMainProcFUcUc();
        endDemoCamera__15CPolarSubCameraFv(gpCamera);
    } else {
        gpMarDirector->mGameState |= WARP_OUT;
    }
}

//0x802995BC
void checkBootOut(TMarDirector* gpMarDirector, u32 curState) {
    restoreMario(gpMarDirector, curState);
    currentStateFinalize__12TMarDirectorFUc(gpMarDirector, curState);
}

//0x80293B10
void extendShineIDLogic(TFlagManager* gpFlagManager, u32 flagID) {
    if ((flagID & 0xFFFF) > 0x77) flagID += (0x60040 - 0x78);
    if (flagID > 0x60334) flagID = 0;
    getFlag__12TFlagManagerCFUl(gpFlagManager, flagID);
}

/*Needs to be input as gecko code
u32 shineObjectStringMod() {
    u32 shineStatus = 1;
    if (callFunction(strcmp)("nbnorm", "shine") == 0) {
        shineStatus = 0x10;
    } else if (callFunction(strcmp)("nbquik", "shine") == 0) {
        shineStatus = 0x12;
    } else if (callFunction(strcmp)("nbdemo", "shine") == 0) {
        shineStatus = 0x11;
    }
    return shineStatus;
}*/

/*Shine casts, fix light
kWrite32(0x80412548, (u32)300.0f);
kWrite32(0x80293AF8, 0x3BFF03E7);
kWrite32(0x802946B8, 0x280003E7);
kWrite32(0x8017BE78, 0x5464037E);
kWrite32(0x8017BEF4, 0x5464037E);
kWrite32(0x8017BF34, 0x5464037E);
kWrite32(0x801BCE30, 0x5464037E);
kWrite32(0x801FF850, 0x5404037E);
kWrite32(0x802946B4, 0x5480043E);
kWrite32(0x80294730, 0x5480043E);
kWrite32(0x80294734, 0x280003E7);
kWrite32(0x80297BA0, 0x5404037E);
kWrite32(0x80294FCC, 0x418200C8);
kWrite32(0x8029519C, 0x418200C8);
*/

//0x80294334
void extendFlagManagerLoad(JSUInputStream& stream) {
    read__14JSUInputStreamFPvl((0x80578988 + 0x1F4), 0x8C);
    stream.skip(0x120);
}

//kWrite32(0x802939BC, 0x48000014);

//0x802939B8
void extendFlagManagerSave(JSUOutputStream& stream) {
    write__15JSUOutputStreamFPCvl((0x80578988 + 0x1F4), 0x8C);
    stream.skip(0x120);
}

//kWrite32(0x80294338 0x48000010);

//0x8027C6A4
bool manageLightSize() {
    SMEFile* file = gInfo.mFile;
    TMarDirector* gpMarDirector = (TMarDirector*)*(u32*)TMarDirectorInstance;
    TWaterManager* gpWaterManager = (TWaterManager*)*(u32*)TWaterManagerInstance;
    TFlagManager* gpFlagManager = (TFlagManager*)*(u32*)TFlagManagerInstance;
    JGeometry::TVec3<float>* gpLightCoordinates = (JGeometry::TVec3<float>*)ShineShadowCoordinates;
    JGeometry::TVec3<float>* gpMarioCoordinates = (JGeometry::TVec3<float>*)*(u32*)TMarioCoordinates;
    if (!file) {
        return (gpMarDirector->mAreaID == 1);
    }

    if (gInfo.Light.mLightType == 1) {

        if (file->Light.mDarkLevel != 255) {
            gpWaterManager->mDarkLevel = file->Light.mDarkLevel;
        } else if (gpFlagManager->Type4Flag.mShineCount < MAX_SHINES) {
            gpWaterManager->mDarkLevel = linearInterpolate<u8>(30, 190, (float)gpFlagManager->Type4Flag.mShineCount / (float)MAX_SHINES);
        } else {
            if (gpWaterManager->mDarkLevel < 255) {
                gpWaterManager->mDarkLevel += 1;
            } else {
                gInfo.Light.mLightType = 0;
            }
        }

        gpLightCoordinates->x = gInfo.Light.mShineShadowCoordinates.x;
        gpLightCoordinates->y = gInfo.Light.mShineShadowCoordinates.y;
        gpLightCoordinates->z = gInfo.Light.mShineShadowCoordinates.z;
        
        if (gInfo.Light.mIsShineShadowGrowing == false) {
            if (gpFlagManager->Type4Flag.mShineCount > gInfo.Light.mPrevShineCount) {

                gInfo.Light.mPrevSize = gpWaterManager->mSize;
                gInfo.Light.mNextSize = gpWaterManager->mSize;

                for (u32 i = 0; i < (gpFlagManager->Type4Flag.mShineCount - gInfo.Light.mPrevShineCount); ++i) {
                    gInfo.Light.mNextSize += (10000 / MAX_SHINES) + (gpFlagManager->Type4Flag.mShineCount * 2);
                } 
                gInfo.Light.mPrevShineCount = gpFlagManager->Type4Flag.mShineCount;
                gInfo.Light.mIsShineShadowGrowing = true;
                
                gInfo.Light.mStepContext = 0;
            }
        }
        if (gInfo.Light.mIsShineShadowGrowing == true) {

            float diff = gInfo.Light.mNextSize - gInfo.Light.mPrevSize;
            
            if (gpWaterManager->mSize > 65535) {
                gpWaterManager->mSize = 65535;
                gInfo.Light.mIsShineShadowGrowing = false;
            } else if (gpWaterManager->mSize < gInfo.Light.mNextSize) {
                if (gInfo.Light.mStepContext > 0) {
                    gpWaterManager->mSize += gInfo.Light.mStepContext;
                } else {
                    gpWaterManager->mSize += 0.1;
                }
                gpWaterManager->mSphereStep = (gpWaterManager->mSize / 2);
                if (gpWaterManager->mSize < (gInfo.Light.mPrevSize + (diff / 2))) {
                    gInfo.Light.mStepContext += (0.05 + (gpFlagManager->Type4Flag.mShineCount / MAX_SHINES));
                } else {
                    gInfo.Light.mStepContext -= (0.05 + (gpFlagManager->Type4Flag.mShineCount / MAX_SHINES));
                }
            } else {
                gpWaterManager->mSize = gInfo.Light.mNextSize;
                gInfo.Light.mIsShineShadowGrowing = false;
            }
        }
    } else if (gInfo.Light.mLightType == 2) {
        gpLightCoordinates->x = gpMarioCoordinates->x + gInfo.Light.mShineShadowCoordinates.x;
        gpLightCoordinates->y = gpMarioCoordinates->y + gInfo.Light.mShineShadowCoordinates.y;
        gpLightCoordinates->z = gpMarioCoordinates->z + gInfo.Light.mShineShadowCoordinates.z;
    }
    return !(gInfo.Light.mLightType == 0 || gpMarDirector->mAreaID == OPTION0);
}

//0x802571F0
float velocityCoordinatePatches(float floorCoordinateY) {
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;

    if (gpMario->mState != STATE_IDLE) { //Y storage
        gpMario->mSpeed.y = 0;
    }

    if (floorCoordinateY < gpMario->mTakeActor.mHitActor.mActor.mCoordinates.y - 20) { //Downwarping
        floorCoordinateY = gpMario->mTakeActor.mHitActor.mActor.mCoordinates.y;
    }
    asm("lfs 0, -0x0EC8 (2)");
    return floorCoordinateY;
}

//0x8028113C
bool infiniteFlutterPatch(float yVelocity) {
    return (yVelocity < -1);
}


/*0x8018987C
addi r3, r31, 0
lis r4, 0x8000
ori r4, r4, 0x4A6C
mtctr r4
bctrl
lwz r0, 0x000C (sp)
*/
//0x80004A6C
float downWarpPatch(TMario* gpMario, float yVelocity) {
    if (yVelocity < -100) {
        return gpMario->mSpeed.y;
    } else {
        return yVelocity;
    }
}

/*0x8018987C
addi r3, r31, 0
lis r4, 0x8000
ori r4, r4, 0x4A6C
mtctr r4
bctrl
lwz r0, 0x000C (sp)
*/
float upWarpPatch(TMario* gpMario, float yVelocity) {
    if (yVelocity > 1000000) {
        return gpMario->mSpeed.y;
    } else {
        return yVelocity;
    }
}