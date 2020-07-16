#include "includes/file_utils.hxx"

//0x803A428A
//.asciz "chr%d.arc"

//0x802A750C
u32* createPrivateHeap(u32* newHeap, u32 size, u32* rootHeap, u32 unk_1) {
    gInfo.mJKRHeap = (u32*)create__10JKRExpHeapFUlP7JKRHeapb(0x1C0000, *(u32*)JKRRootHeap, 0);
    u32* gameHeap = (u32*)create__10JKRExpHeapFPvUlP7JKRHeapb(newHeap, size - 0x1C0000, rootHeap, unk_1);
    return (u32*)gameHeap;
}

//0x802A7140
u32 setupMarioDatas(char* filepath) {
    TMarioGamePad* gpGamePad = (TMarioGamePad*)0x8057738C;
    TApplication* gpApplication = (TApplication*)TApplicationInstance;
    u32* marioDataField = (u32*)ARCBufferMario;
    
    u32 id = 0;
    if (*(u32*)&gpGamePad->Buttons == PRESS_Z) {
        id = 1;
    } else if (*(u32*)&gpGamePad->Buttons == PRESS_R){
        id = 2;
    } else if (*(u32*)&gpGamePad->Buttons == PRESS_L){
        id = 3;
    }

    sprintf(filepath, filepath, id);

    return DVDConvertPathToEntrynum(filepath);
}

//0x802A714C
u32* getPrivateHeap() {
    return gInfo.mJKRHeap;
}

//kWrite32(0x802A7148, 0x60000000);

//0x802A664C
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
    
    if (!gInfo.mFile || gInfo.mFile->FileHeader.mPlayerID == 0xFF)
        return;

    char buffer[0x10];

    strcpy(buffer, "/data/chr%d.arc");
    strcpy(strstr(buffer, ".arc"), ".szs");
    sprintf(buffer, buffer, gInfo.mFile->FileHeader.mPlayerID);

    u32* marioVolumeData = (u32*)getVolume__13JKRFileLoaderFPCc("mario");

    if (DVDConvertPathToEntrynum(buffer) == -1)
        return;

    free(*(u32*)ARCBufferMario);

    u32* marioData = (u32*)loadToMainRAM__12JKRDvdRipperFPCcPUc15JKRExpandSwitchUlP7JKRHeapQ212JKRDvdRipper15EAllocDirectionUlPi(buffer, 0, 1, 0, gInfo.mJKRHeap, 1, 0, 0);
    u32* marioDataField = (u32*)ARCBufferMario;

    *marioDataField = (u32)marioData;

    __dt__13JKRMemArchiveFv(marioVolumeData);
    __ct__13JKRMemArchiveFPvUl15JKRMemBreakFlag(marioVolumeData, *marioDataField, 0, 0);

    asm("mr 3, 26");
    return;
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

    gpMario->mMaxJumps = 1;
    gpMario->mPlayerID = gInfo.PlayerData.mCurPlayerID[0];
    gpMario->mCanRideYoshi = true;
    gpMario->mCanHaveFludd = true;

    if (file) {
        gpMario->mPlayerID = file->FileHeader.mPlayerID;
        gInfo.PlayerData.mCurPlayerID[0] = file->FileHeader.mPlayerID;

        gpMario->mGravity = file->Mario.mGravity;
        gpMario->mBaseBounceSpeed1 = file->Mario.mBaseBounce1;
        gpMario->mBaseBounceSpeed2 = file->Mario.mBaseBounce2;
        gpMario->mBaseBounceSpeed3 = file->Mario.mBaseBounce3;
        gpMario->mMaxFallNoDamage = file->Mario.mMaxFallNoDamage;
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
    }

    MarioParamsFile* paramsFile = (MarioParamsFile*)getResource__10JKRArchiveFPCc(getVolume__13JKRFileLoaderFPCc("mario"),
                                                                                  "/params.bin");

    if (!paramsFile) return;

    gpMario->mGravity *= paramsFile->Attributes.mGravityMulti;
    gpMario->mTerminalVelocity *= paramsFile->Attributes.mGravityMulti;
    gpMario->mMaxFallNoDamage *= paramsFile->Attributes.mMaxFallNoDamageMulti;
    gpMario->mMaxJumps = paramsFile->Attributes.mJumpCount;

    gpMario->mBaseBounceSpeed1 *= paramsFile->Attributes.mBaseBounce1Multi;
    gpMario->mBaseBounceSpeed2 *= paramsFile->Attributes.mBaseBounce2Multi;
    gpMario->mBaseBounceSpeed3 *= paramsFile->Attributes.mBaseBounce3Multi;
    gpMario->mHealth = paramsFile->Attributes.mHealth;
    gpMario->mMaxHealth = paramsFile->Attributes.mMaxHealth;
    gpMario->mOBStep = paramsFile->Attributes.mOBStep;
    gpMario->mOBMax = paramsFile->Attributes.mOBMax;

    gpMario->mAttributes.mGainHelmet = paramsFile->Attributes.mMarioHasHelmet;
    gpMario->mAttributes.mHasFludd = paramsFile->Attributes.mCanUseFludd;
    gpMario->mAttributes.mIsShineShirt = paramsFile->Attributes.mMarioHasShirt;

    if (paramsFile->Attributes.mMarioHasGlasses) {
        wearGlass__6TMarioFv(gpMario);
    }

    gpMario->mCanRideYoshi = paramsFile->Attributes.mCanRideYoshi;

    *(float*)0x80415CA8 *= paramsFile->Attributes.mOverallMulti;

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

//80415CA8 = Mario speed everything