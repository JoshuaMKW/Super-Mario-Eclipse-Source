#include "includes/file_utils.hxx"

//0x803A428A
//.asciz "chr%d.arc"

//0x802A6C4C
void initMarioBoot(u32* memArchive, u32* marioDataArray, u8 unk_1, u8 unk_2) {
    TMarioGamePad* gpGamePad = (TMarioGamePad*)0x8057738C;
    u32 id = 0;
    if (*(u32*)&gpGamePad->Buttons == PRESS_Z) {
        id = 1;
    } else if (*(u32*)&gpGamePad->Buttons == PRESS_R){
        id = 2;
    } else if (*(u32*)&gpGamePad->Buttons == PRESS_L){
        id = 3;
    }
    __ct__13JKRMemArchiveFPvUl15JKRMemBreakFlag(memArchive, marioDataArray[id], unk_1, unk_2);
}

//0x802A716C
u32* setupMarioDatas(char* filepath, u8 unk_1, u8 unk_2, u8 expandSwitch,
                      u32* JKRHeap, u8 JKRDvdRipper, u8 allocDirection, u8 unk_3) {

    char buffer[0x10];
    u32* marioDataArray = (u32*)0x80004FD0;

    for (u32 i = 0; i < 8; ++i) {
        sprintf(buffer, filepath, i);

        if (DVDConvertPathToEntrynum(buffer) == -1)
            break;

        u32* marioData = (u32*)loadToMainRAM__12JKRDvdRipperFPCcPUc15JKRExpandSwitchUlP7JKRHeapQ212JKRDvdRipper15EAllocDirectionUlPi(buffer, unk_1, unk_2,
                                                                                                                                     expandSwitch, JKRHeap,
                                                                                                                                     JKRDvdRipper, allocDirection, unk_3);
        if (marioData == nullptr)
            break;

        marioDataArray[i] = (u32)marioData;
    }
    return marioDataArray;
}

//kWrite32(0x802A7148, 0x60000000);

//0x802B7720
void switchChrSZS(TFlagManager* gpFlagManager) {
    resetStage__12TFlagManagerFv(gpFlagManager);

    if (!gInfo.mFile || gInfo.mFile->FileHeader.mPlayerID == 0xFF)
        return;

    u32* marioVolumeData = (u32*)getVolume__13JKRFileLoaderFPCc("mario");
    u32* marioDataArray = (u32*)*(u32*)ARCBufferMario;

    __dt__13JKRMemArchiveFv(marioVolumeData);
    __ct__13JKRMemArchiveFPvUl15JKRMemBreakFlag(marioVolumeData, marioDataArray[gInfo.mFile->FileHeader.mPlayerID], 0, 0);
}

//0x802998B4
void initFileMods() {

    if (gInfo.mFile) {
        free(gInfo.mFile); //Free the file allocation
    }

    *(u32*)0x803DD898 = 0x3C467814; //Water rgba
    *(u32*)0x803DD89C = 0xFEA8026E; //Yoshi Juice rgba
    *(u32*)0x803DD8A0 = 0x9B01FD6E;
    *(u32*)0x803DD8A4 = 0xFD62A76E;
    *(u32*)0x8039F934 = 0x40A124FF;
    *(u32*)0x8039F938 = 0xFF8C1CFF; //Yoshi rgba
    *(u32*)0x8039F93C = 0xAA4CFFFF;
    *(u32*)0x8039F940 = 0xFFA0BEFF;
    *(u32*)0x80415CA8 = 0x3E800000; //Mario overall speed
    *(float*)0x8040C1C0 = 0.75;
    *(float*)0x80417248 = 1;
    *(float*)0x8041731C = 1;

    char folder[] = "/data/scene/sme/";
    const char* stage = getStageName((TApplication*)0x803E9700);

    if (!stage) {
        return;
    }

    SMEFile* file = loadFile(parseExtension(folder, stage, false));

    if (!file) {
        folder[16] = NULL;
        file = loadFile(parseExtension(folder, stage, true));
    }
    gInfo.mFile = file;
    asm("mr 3, 26");
}

//0x80280180
void initShineShadow() {
    SMEFile* file = gInfo.mFile;
    TWaterManager* gpWaterManager = (TWaterManager*)*(u32*)TWaterManagerInstance;
    TFlagManager* gpFlagManager = (TFlagManager*)*(u32*)TFlagManagerInstance;

    if (!file || file->FileHeader.mIsShineShadow == false)
        return;

    if (file->FileHeader.mIsShineShadow && gpFlagManager->Type4Flag.mShineCount < MAX_SHINES) {
        gInfo.Light.mLightType = file->FileHeader.mShineShadowFlag;
        gInfo.Light.mShineShadowBase = file->Light.mSize;
        gInfo.Light.mPrevShineCount = gpFlagManager->Type4Flag.mShineCount;
        
        gpWaterManager->mColor = file->Light.mColor;
        gpWaterManager->mDarkLevel = file->Light.mDarkLevel;
        gpWaterManager->mLayerCount = file->Light.mLayerCount;
        gpWaterManager->mSphereStep = file->Light.mStep;
        gpWaterManager->mSize = file->Light.mSize;
        gpWaterManager->LightType.mMaskObjects = true;
        gpWaterManager->LightType.mShowShadow = true;

        if (file->FileHeader.mShineShadowFlag == 1) {
            for (u32 i = 0; i < gpFlagManager->Type4Flag.mShineCount; ++i) {
                gpWaterManager->mSize += (10000 / MAX_SHINES) + (gpFlagManager->Type4Flag.mShineCount * 2);
            }
            gpWaterManager->mSphereStep = gpWaterManager->mSize / 2;
        }
        gInfo.Light.mShineShadowCoordinates = file->Light.mCoordinates;
    } else {
        gInfo.Light.mLightType = 0;
    }
}

//0x802B7A4C
void initSoundBank(u8 areaID, u8 episodeID) {
    SMEFile* file = gInfo.mFile;

    if (!file || gInfo.mFile->FileHeader.mIsMusic == false) {
        setMSoundEnterStage__10MSMainProcFUcUc(areaID, episodeID);
    } else {
        setMSoundEnterStage__10MSMainProcFUcUc(gInfo.mFile->Music.mAreaID, gInfo.mFile->Music.mEpisodeID);
    }
}

//0x802983F0
//0x80298420
void initMusicTrack() {
    SMEFile* file = gInfo.mFile;

    if (!file || gInfo.mFile->FileHeader.mIsMusic == false) {
        startStageBGM__10MSMainProcFUcUc();
    } else if (gInfo.mFile->Music.mPlayMusic == true) {
        *(u32*)0x8040E1F0 = 0x80010000 | gInfo.mFile->Music.mMusicID;
        *(float*)0x8041731C = gInfo.mFile->Music.mSpeed;
        *(float*)0x80417248 = gInfo.mFile->Music.mPitch;

        if (gInfo.mFile->Music.mVolume > 1) {
            *(float*)0x8040C1C0 = 1;
        } else if (gInfo.mFile->Music.mVolume < 0) {
            *(float*)0x8040C1C0 = 0;
        } else {
            *(float*)0x8040C1C0 = gInfo.mFile->Music.mVolume;
        }
        startStageBGM__10MSMainProcFUcUc();
    }
}

//0x8026AA44
void initFludd() {
    SMEFile* file = gInfo.mFile;
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;

    if (!file || file->FileHeader.mIsFludd == false) {
        return;
    }

    if (file->Fludd.mIsColorWater == true) {
        waterColor = file->Fludd.mWaterColor;
    }
    gpMario->mFludd->mCurrentNozzle = file->Fludd.mPrimaryNozzle;
    gpMario->mFludd->mSecondNozzle = file->Fludd.mSecondaryNozzle;

    gpMario->mFludd->mCurrentWater = gpMario->mFludd->mNozzleList[gpMario->mFludd->mCurrentNozzle]->mMaxWater;
}

//0x80276AC8
/*
lis r29, 0x8000
ori r29, r29, 0x50D0
mr r3, r30
mtctr r29
bctrl
lwz r30, 0x38 (sp)
*/

//0x800050D0
void initMario(TMario* gpMario) {
    SMEFile* file = gInfo.mFile;

    if (!file)
        return;

    
    gpMario->mPlayerID = file->FileHeader.mPlayerID;
    gInfo.PlayerData.mCurPlayerID[0] = file->FileHeader.mPlayerID;

    gpMario->mBaseBounceSpeed1 = file->Mario.mBaseBounce1;
    gpMario->mBaseBounceSpeed2 = file->Mario.mBaseBounce2;
    gpMario->mBaseBounceSpeed3 = file->Mario.mBaseBounce3;
    gpMario->mHealth = file->Mario.mHealth;
    gpMario->mMaxHealth = file->Mario.mMaxHealth;
    gpMario->mOBStep = file->Mario.mOBStep;
    gpMario->mOBMax = file->Mario.mOBMax;

    gpMario->mAttributes.mGainHelmet = file->FileHeader.MarioStates.mMarioHasHelmet;
    gpMario->mAttributes.mHasFludd = file->FileHeader.MarioStates.mMarioHasFludd;
    gpMario->mAttributes.mIsShineShirt = file->FileHeader.MarioStates.mMarioHasShirt;
    
    if (file->FileHeader.MarioStates.mMarioHasGlasses) {
        wearGlass__6TMarioFv(gpMario);
    }

    switch(file->FileHeader.mPlayerID) {
    case(1):
        gpMario->mGravity = file->Mario.mGravity * 0.875;
        gpMario->mTerminalVelocity *= 0.875;
        gpMario->mMaxFallNoDamage = file->Mario.mMaxFallNoDamage;
        *(u32*)0x80415CA8 = 0x3E800000;
        break;
    case(2):
        gpMario->mGravity = file->Mario.mGravity * 0.875;
        gpMario->mMaxFallNoDamage = file->Mario.mMaxFallNoDamage * 1.5;
        gpMario->mAttributes.mHasFludd = false;
        *(u32*)0x80415CA8 = 0x3EC00000;
        break;
    case(3):
        gpMario->mGravity = file->Mario.mGravity;
        gpMario->mMaxFallNoDamage = file->Mario.mMaxFallNoDamage;
        gpMario->mAttributes.mHasFludd = false;
        *(u32*)0x80415CA8 = 0x3E800000;
        break;
    default:
        gpMario->mGravity = file->Mario.mGravity;
        gpMario->mMaxFallNoDamage = file->Mario.mMaxFallNoDamage;
        *(u32*)0x80415CA8 = 0x3E800000;
        break;
    }
}

//0x802715A0
void initYoshi() {
    SMEFile* file = gInfo.mFile;
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;

    if (!file || file->FileHeader.mIsYoshi == false)
        return;

    RGBA* juiceColor = (RGBA*)YoshiJuiceColor;
    RGBA* yoshiColor = (RGBA*)YoshiColor;

    juiceColor[0] = file->Yoshi.mOrangeYoshi;
    juiceColor[1] = file->Yoshi.mPurpleYoshi;
    juiceColor[2] = file->Yoshi.mPinkYoshi;

    yoshiColor[0] = file->Yoshi.mGreenYoshi;
    yoshiColor[1] = file->Yoshi.mOrangeYoshi;
    yoshiColor[2] = file->Yoshi.mPurpleYoshi;
    yoshiColor[3] = file->Yoshi.mPinkYoshi;

    TYoshi* gpYoshi = gpMario->mYoshi;

    gpYoshi->mMaxJuice = file->Yoshi.mMaxJuice;
    gpYoshi->mMaxVSpdStartFlutter = file->Yoshi.mMaxVSpdStartFlutter;
    gpYoshi->mFlutterAcceleration = file->Yoshi.mFlutterAcceleration;
    gpYoshi->mMaxFlutterTimer = file->Yoshi.mMaxFlutterTimer;
}

//0x8029CCB0
void initCardColors() {
    SMEFile* file = gInfo.mFile;
    TMarDirector* gpMarDirector = (TMarDirector*)*(u32*)TMarDirectorInstance;

    if (file && file->FileHeader.mIsYoshi == true) {
        gpMarDirector->mGCConsole->mJuiceCardOrange = file->Yoshi.mOrangeYoshi;
        gpMarDirector->mGCConsole->mJuiceCardPurple = file->Yoshi.mPurpleYoshi;
        gpMarDirector->mGCConsole->mJuiceCardPink = file->Yoshi.mPinkYoshi;
    }

    if (file && file->FileHeader.mIsFludd == true && file->Fludd.mIsColorWater == true) {
        gpMarDirector->mGCConsole->mWaterLeftPanel = file->Fludd.mWaterColor;
        gpMarDirector->mGCConsole->mWaterRightPanel.R = linearInterpolateU8(0, file->Fludd.mWaterColor.R, 0.8125);
        gpMarDirector->mGCConsole->mWaterRightPanel.G = linearInterpolateU8(0, file->Fludd.mWaterColor.G, 0.8125);
        gpMarDirector->mGCConsole->mWaterRightPanel.B = linearInterpolateU8(0, file->Fludd.mWaterColor.B, 0.8125);
        gpMarDirector->mGCConsole->mWaterRightPanel.A = linearInterpolateU8(0, file->Fludd.mWaterColor.A, 0.8125);
    }

}

//0x80164DE4
void newGamePlus(TFlagManager* gpFlagManager, u32* stream) {
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;
    load__12TFlagManagerFR20JSUMemoryInputStream(gpFlagManager, stream);
    if (gpFlagManager->Type4Flag.mShineCount < 120 || (gpFlagManager->Type1Flag.m1Type[0xE] & 0x80) == 0) {
        return;
    }
    if (gpMario->mController->Buttons.mRButton && gpMario->mController->Buttons.mLButton) {
        gpFlagManager->Type6Flag.CustomFlags.mIsGamePlus = true;
        //Type 1
        memset(gpFlagManager->Type1Flag.m1Type, 0, 0x77);
        //Type 2
        gpFlagManager->Type2Flag.mDelfinoCoinRecord = 0;
        gpFlagManager->Type2Flag.mBiancoCoinRecord = 0;
        gpFlagManager->Type2Flag.mRiccoCoinRecord = 0;
        gpFlagManager->Type2Flag.mGelatoCoinRecord = 0;
        gpFlagManager->Type2Flag.mPinnaCoinRecord = 0;
        gpFlagManager->Type2Flag.mSirenaCoinRecord = 0;
        gpFlagManager->Type2Flag.mPiantaCoinRecord = 0;
        gpFlagManager->Type2Flag.mNokiCoinRecord = 0;
        gpFlagManager->Type2Flag.mNoki5Record = 0;

        //Type 3
        gpFlagManager->Type3Flag.mLostLifePrev = false;
        gpFlagManager->Type3Flag.mPlazaDemoWatched = false;
        gpFlagManager->Type3Flag.mWatchPeachKidnappedPrev = false;
        gpFlagManager->Type3Flag.mPpdBJRBalloonsPrev = false;
        gpFlagManager->Type3Flag.mShineGetPrev = false;
        gpFlagManager->Type3Flag.mPlaneCrashWatched = false;
        gpFlagManager->Type3Flag.mCourtWatched = false;
        gpFlagManager->Type3Flag.mPeachKNAPFMVWatched = false;
        gpFlagManager->Type3Flag.mFluddTheftViewed = false;

        //Type 4
        gpFlagManager->Type4Flag.mShineCount = 0;
        gpFlagManager->Type4Flag.mBlueCoinCount = 0;
        gpFlagManager->Type4Flag.mGoldCoinCount = 0;
        gpFlagManager->Type4Flag.mSecondNozzle = TURBO_NOZZLE;

        //Type 5
        gpFlagManager->Type5Flag.mShineSpawned = false;
        gpFlagManager->Type5Flag.mRiccoUnlockable = false;
        gpFlagManager->Type5Flag.mGelatoUnlockable = false;
        gpFlagManager->Type5Flag.mSunflowersRescue = false;
        gpFlagManager->Type5Flag.mNokiAvailable = false;
        gpFlagManager->Type5Flag.mPiantismoRaceComplete = false;
        gpFlagManager->Type5Flag.mMantaSpawned = false;
        gpFlagManager->Type5Flag.mHotelRising = false;
        gpFlagManager->Type5Flag.mRedCoinSwitchPressed = false;
        gpFlagManager->Type5Flag.mMechaBowserDefeated = false;
        gpFlagManager->Type5Flag.mWigglerFalling = false;
        gpFlagManager->Type5Flag.mMoleDefeated = false;

        //Type 6
        gpFlagManager->Type6Flag.mRedCoinCount = 0;
        gpFlagManager->Type6Flag.mShadowMarioEvent = 0;
    }
}

//GPlus health
//0x80243838
/*
lis r5, 0x8041
lwz r5, -0x1EA0(r5)
lwz r5, 0x27C(r5)
rlwinm r5,r5,1,31,31
slw r4, r4, r5
mr r31, r4
*/

//Force no hover
//0x8026A180
/*
lis r6, 0x8041
lwz r6, -0x1EA0(r6)
lwz r6, 0x27C(r6)
andis. r6, r6, 0x8000
beq+ pass
cmpwi r4, 4
bne+ pass
li r4, 5
pass:
mr. r30, r4
*/

//Init with turbo
//0x8026A3C8
/*
li r8, 4
lis r7, 0x8041
lwz r7, -0x1EA0(r7)
lwz r7, 0x27C(r7)
andis. r7, r7, 0x8000
beq+ pass
li r8, 5
pass:
*/



//0x801BB660
/*
.loc_0x0:
  lis r4, 0x8041
  lwz r4, -0x1EA0(r4)
  lwz r4, 0x27C(r4)
  andis. r4, r4, 0x8000
  beq- .loc_0x34
  lwz r4, 0x148(r31)
  cmplwi r4, 0x4
  bne- .loc_0x34
  mr r3, r31
  lis r4, 0x801B
  ori r4, r4, 0x738
  mtctr r4
  bctrl 

.loc_0x34:
  lwz r0, 0x4C(sp)
*/
void isGPlusNozzleBox(TNozzleBox* gpNozzleBox) {
    TFlagManager* gpFlagManager = (TFlagManager*)*(u32*)TFlagManagerInstance;
    if (gpFlagManager->Type6Flag.CustomFlags.mIsGamePlus == false) {
        return;
    }
    if (gpNozzleBox->mNozzleToRegen == HOVER_NOZZLE) {
        makeObjDead__11TMapObjBaseFv((TMapObjBase*)gpNozzleBox);
    }
}

//80415CA8 = Mario speed everything