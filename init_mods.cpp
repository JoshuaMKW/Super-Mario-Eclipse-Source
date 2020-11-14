#include "includes/file_utils.hxx"

//0x803A428A
//.asciz "chr%d.arc"

//0x802A750C
u32 *createCharacterHeap(u32 *newHeap, u32 size, u32 *rootHeap, u32 unk_1)
{
    gInfo.mCharacterHeap = (u32 *)create__10JKRExpHeapFUlP7JKRHeapb(0x200000, (u32 *)*(u32 *)JKRRootHeap, false);
    u32 *gameHeap = (u32 *)create__10JKRExpHeapFPvUlP7JKRHeapb(newHeap, size - 0x200000, rootHeap, unk_1);
    return (u32 *)gameHeap;
}

//0x802A7140
u32 setupMarioDatas(char *filepath)
{
    TApplication *gpApplication = (TApplication *)TApplicationInstance;
    TMarioGamePad *gpGamePad = gpApplication->mGamePad1;
    u32 id;

    switch (gpGamePad->getInput())
    {
    case TMarioGamePad::BUTTONS::DPAD_UP:
        id = 1;
        break;
    case TMarioGamePad::BUTTONS::DPAD_DOWN:
        id = 2;
        break;
    case TMarioGamePad::BUTTONS::DPAD_LEFT:
        id = 3;
        break;
    case TMarioGamePad::BUTTONS::DPAD_RIGHT:
        id = 4;
        break;
    default:
        id = 0;
    }

    sprintf(filepath, filepath, id);
    return DVDConvertPathToEntrynum(filepath);
}

//0x802A714C
u32 *getPrivateHeap()
{
    return gInfo.mCharacterHeap;
}

//kWrite32(0x802A7148, 0x60000000);

void resetGlobalValues()
{
    RGBA<u8> *waterColor = (RGBA<u8> *)WaterAddr;
    RGBA<u8> *juiceColor = (RGBA<u8> *)YoshiJuiceColor;
    RGBA<u8> *yoshiColor = (RGBA<u8> *)YoshiColor;

    waterColor[0] = {0x3C, 0x46, 0x78, 0x14}; //Water rgba
    juiceColor[0] = {0xFE, 0xA8, 0x02, 0x6E}; //Yoshi Juice rgba
    juiceColor[1] = {0x9B, 0x01, 0xFD, 0x6E};
    juiceColor[2] = {0xFD, 0x62, 0xA7, 0x6E};
    juiceColor[3] = {0x40, 0xA1, 0x24, 0xFF};
    yoshiColor[0] = {0xFF, 0x8C, 0x1C, 0xFF}; //Yoshi rgba
    yoshiColor[1] = {0xAA, 0x4C, 0xFF, 0xFF};
    yoshiColor[2] = {0xFF, 0xA0, 0xBE, 0xFF};
    *(float *)0x80415CA8 = 0.25; //Mario overall speed
    *(float *)0x8040C1C0 = 0.75;
    *(float *)0x80417248 = 1;
    *(float *)0x8041731C = 1;
}

//0x802998B4
void initFileMods()
{
    u32 *marioVolumeData = (u32 *)getVolume__13JKRFileLoaderFPCc(0x804165A0);        //"mario"
    u32 *params = (u32 *)getResource__10JKRArchiveFPCc(marioVolumeData, 0x80004A01); //"/params.szs"

    u32 *marioDataField;
    u32 *marioData;
    u32 *allocation;

    char buffer[32];

    free(gInfo.mFile); //Free the file allocation
    resetGlobalValues();

    char folder[] = "/data/scene/sme/";
    const char *stage = getStageName((TApplication *)TApplicationInstance);

    if (!stage) return;

    SMEFile *file = SMEFile::loadFile(SMEFile::parseExtension(folder, stage, false));

    if (!file)
    {
        folder[16] = NULL;
        file = SMEFile::loadFile(SMEFile::parseExtension(folder, stage, true));
    }

    gInfo.mFile = file;

    if (gInfo.mFile && gInfo.mFile->FileHeader.mPlayerID != 0xFF)
    {
        //Attempt to swap character data

        sprintf(buffer, (char *)0x803A4284, gInfo.mFile->FileHeader.mPlayerID); //"/data/chr%d.arc"
        strcpy(strstr(buffer, (char *)0x8041678C), (char *)0x80416794);         //".arc", ".szs"

        if (DVDConvertPathToEntrynum(buffer) >= 0)
        {
            free((void *)*(u32 *)ARCBufferMario);

            marioData = (u32 *)loadToMainRAM__12JKRDvdRipperFPCcPUc15JKRExpandSwitchUlP7JKRHeapQ212JKRDvdRipper15EAllocDirectionUlPi(buffer, 0, 1, 0, gInfo.mCharacterHeap, 1, 0, 0);
            *(u32 *)ARCBufferMario = (u32)marioData;

            __dt__13JKRMemArchiveFv(marioVolumeData);
            __ct__13JKRMemArchiveFPvUl15JKRMemBreakFlag(marioVolumeData, *(u32 *)ARCBufferMario, 0, 0);
        }
    }

    if (params)
    {
        u32 filesize = getResSize__10JKRArchiveCFPCv(marioVolumeData, params);
        u32 compressionState = checkCompressed__9JKRDecompFPUc(params);

        if (compressionState == 2)
        {
            *(u32 *)0x8040E260 = params[0x4 / 4];
            allocation = (u32 *)alloc__7JKRHeapFUliP7JKRHeap(params[0x4 / 4], 32, *(u32 *)JKRCurrentHeap);
            decompSZS_subroutine__FPUcPUc(params, allocation);
            gInfo.mPRMFile = allocation;
        }
        else if (compressionState == 1)
        {
            gInfo.mPRMFile = nullptr;
        }
        else
        {
            allocation = (u32 *)alloc__7JKRHeapFUliP7JKRHeap(filesize, 32, *(u32 *)JKRCurrentHeap);
            memcpy(allocation, params, filesize);
            gInfo.mPRMFile = allocation;
        }

        u32 *oldParams = (u32 *)getVolume__13JKRFileLoaderFPCc(0x8041676C); //params

        unmountFixed__13JKRMemArchiveFv(oldParams);
        mountFixed__13JKRMemArchiveFPv15JKRMemBreakFlag(oldParams, gInfo.mPRMFile, 0);
    }

    asm("mr 3, 26");
    return;
}

//0x80280180
void initShineShadow()
{
    SMEFile *file = gInfo.mFile;
    TWaterManager *gpWaterManager = (TWaterManager *)*(u32 *)TWaterManagerInstance;
    TFlagManager *gpFlagManager = (TFlagManager *)*(u32 *)TFlagManagerInstance;

    if (!file || file->FileHeader.mIsShineShadow == false)
        return;

    if (gpFlagManager->Type4Flag.mShineCount < MAX_SHINES)
    {
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

        if (file->FileHeader.mShineShadowFlag == 1)
        {
            gInfo.Light.mNextSize = file->Light.mSize;
            for (u32 i = 0; i < gpFlagManager->Type4Flag.mShineCount; ++i)
            {
                gInfo.Light.mNextSize += (10000 / MAX_SHINES) + i * 2;
            }
            gpWaterManager->mSphereStep = gpWaterManager->mSize / 2;
        }
        gInfo.Light.mShineShadowCoordinates = file->Light.mCoordinates;
    }
    else
    {
        gInfo.Light.mLightType = 0;
    }
}

//0x802B7A4C
void initSoundBank(u8 areaID, u8 episodeID)
{
    SMEFile *file = gInfo.mFile;

    if (!file || !gInfo.mFile->FileHeader.mIsMusic)
    {
        setMSoundEnterStage__10MSMainProcFUcUc(areaID, episodeID);
    }
    else
    {
        setMSoundEnterStage__10MSMainProcFUcUc(gInfo.mFile->Music.mAreaID, gInfo.mFile->Music.mEpisodeID);
    }
}

//0x802983F0
//0x80298420
void initMusicTrack()
{
    SMEFile *file = gInfo.mFile;

    if (!file || !gInfo.mFile->FileHeader.mIsMusic)
    {
        startStageBGM__10MSMainProcFUcUc();
    }
    else if (gInfo.mFile->Music.mPlayMusic == true)
    {
        *(u32 *)0x8040E1F0 = 0x80010000 | gInfo.mFile->Music.mMusicID;
        *(float *)0x8041731C = gInfo.mFile->Music.mSpeed;
        *(float *)0x80417248 = gInfo.mFile->Music.mPitch;

        if (gInfo.mFile->Music.mVolume > 1)
        {
            *(float *)0x8040C1C0 = 1;
        }
        else if (gInfo.mFile->Music.mVolume < 0)
        {
            *(float *)0x8040C1C0 = 0;
        }
        else
        {
            *(float *)0x8040C1C0 = gInfo.mFile->Music.mVolume;
        }
        startStageBGM__10MSMainProcFUcUc();
    }
}

void initFludd(TMario *gpMario)
{
    SMEFile *stagefile = gInfo.mFile;

    if (stagefile && stagefile->FileHeader.mIsFludd)
    {
        if (stagefile->Fludd.mIsColorWater)
        {
            waterColor = stagefile->Fludd.mWaterColor;
        }
        gpMario->mFludd->mCurrentNozzle = stagefile->Fludd.mPrimaryNozzle;
        gpMario->mFludd->mSecondNozzle = stagefile->Fludd.mSecondaryNozzle;

        gpMario->mFludd->mCurrentWater = gpMario->mFludd->mNozzleList[(u8)gpMario->mFludd->mCurrentNozzle]->mMaxWater;
    }

    if (gpMario->mCustomInfo->mParams)
    {
        waterColor = gpMario->mCustomInfo->mParams->Attributes.FluddAttrs.mWaterColor;
        if (!gpMario->mCustomInfo->mParams->Attributes.FluddAttrs.mCanUseNozzle[(u8)gpMario->mFludd->mCurrentNozzle])
        {
            for (u8 i = 0; i < 8; ++i)
            {
                if (gpMario->mCustomInfo->mParams->Attributes.FluddAttrs.mCanUseNozzle[i])
                {
                    gpMario->mFludd->mCurrentNozzle = (TWaterGun::NOZZLETYPE)i;
                    gpMario->mAttributes.mHasFludd = gpMario->mCustomInfo->mParams->Attributes.mCanUseFludd;
                    gpMario->mFludd->mCurrentWater = gpMario->mFludd->mNozzleList[(u8)gpMario->mFludd->mCurrentNozzle]->mMaxWater;
                    break;
                }
                else if (i == 7)
                {
                    gpMario->mAttributes.mHasFludd = false;
                    gpMario->mCustomInfo->mParams->Attributes.mCanUseFludd = false;
                }
            }
        }

        if (!gpMario->mCustomInfo->mParams->Attributes.FluddAttrs.mCanUseNozzle[(u8)gpMario->mFludd->mSecondNozzle])
        {
            for (u8 i = 0; i < 8; ++i)
            {
                if (gpMario->mCustomInfo->mParams->Attributes.FluddAttrs.mCanUseNozzle[i])
                {
                    gpMario->mFludd->mSecondNozzle = (TWaterGun::NOZZLETYPE)i;
                    gpMario->mAttributes.mHasFludd = gpMario->mCustomInfo->mParams->Attributes.mCanUseFludd;
                    break;
                }
                gpMario->mFludd->mSecondNozzle = gpMario->mFludd->mCurrentNozzle;
            }
        }
    }
}

//0x80276AC0 - Mario
/*
mr r3, r30
__set r4, TRUE
__call r12, 0x800050D0
lwz r0, 0x44 (sp)
*/

//0x800397FC - Shadow Mario
/*
lwz r3, 0x150 (r31)
__set r4, FALSE
__call r12, 0x800050D0
lwz r0, 0x1C (sp)
*/

//0x800050D0
void initMario(TMario *gpMario, bool isMario)
{
    SMEFile *file = gInfo.mFile;
    gpMario->mCustomInfo = (TMario::CustomInfo *)malloc(sizeof(TMario::CustomInfo), 32);
    gpMario->mCustomInfo->mParams = nullptr;
    gpMario->mCustomInfo->mBackUpParams = nullptr;

    if (file && file->FileHeader.mIsMario)
    {
        gpMario->mCustomInfo->mPlayerID = file->FileHeader.mPlayerID;
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

        if (file->FileHeader.MarioStates.mMarioHasGlasses)
        {
            wearGlass__6TMarioFv(gpMario);
        }
    }

    if (!isMario) return;

    gpMario->mCustomInfo->mParams = (MarioParamsFile *)getResource__10JKRArchiveFPCc(getVolume__13JKRFileLoaderFPCc(0x804165A0), //mario
                                                                                     0x800049F5);                                ///params.bin
    
    if (gpMario->mCustomInfo->mParams)
    {
        gpMario->mCustomInfo->mBackUpParams = (MarioParamsFile *)malloc(sizeof(MarioParamsFile), 32);
        gpMario->mCustomInfo->mBackUpParams = gpMario->mCustomInfo->mParams;

        gpMario->mCustomInfo->mBackUpParams->Attributes.mBaseBounce1Multi = gpMario->mCustomInfo->mParams->Attributes.mBaseBounce1Multi *= sizeAvg;
        gpMario->mCustomInfo->mParams->Attributes.mBaseBounce2Multi *= sizeAvg;
        gpMario->mCustomInfo->mParams->Attributes.mBaseBounce3Multi *= sizeAvg;
        gpMario->mCustomInfo->mParams->Attributes.mMaxFallNoDamageMulti *= sizeAvg;
        gpMario->mCustomInfo->mParams->Attributes.mBaseJumpHeightMulti *= sizeAvg;
        gpMario->mCustomInfo->mParams->Attributes.mSpeedMultiplier *= sizeAvg;


        float sizeX = gpMario->mCustomInfo->mParams->Attributes.mSizeMultiplier.x;
        float sizeY = gpMario->mCustomInfo->mParams->Attributes.mSizeMultiplier.y;
        float sizeZ = gpMario->mCustomInfo->mParams->Attributes.mSizeMultiplier.z;
        float sizeAvg = (sizeX + sizeY + sizeZ) / 3;


        gpMario->mCustomInfo->mParams->Attributes.mBaseBounce1Multi *= sizeAvg;
        gpMario->mCustomInfo->mParams->Attributes.mBaseBounce2Multi *= sizeAvg;
        gpMario->mCustomInfo->mParams->Attributes.mBaseBounce3Multi *= sizeAvg;
        gpMario->mCustomInfo->mParams->Attributes.mMaxFallNoDamageMulti *= sizeAvg;
        gpMario->mCustomInfo->mParams->Attributes.mBaseJumpHeightMulti *= sizeAvg;
        gpMario->mCustomInfo->mParams->Attributes.mSpeedMultiplier *= sizeAvg;

        gpMario->mGravity *= gpMario->mCustomInfo->mParams->Attributes.mGravityMulti;
        gpMario->mCustomInfo->mTerminalVelocity = -75 * gpMario->mCustomInfo->mParams->Attributes.mGravityMulti;
        gpMario->mMaxFallNoDamage *= gpMario->mCustomInfo->mParams->Attributes.mMaxFallNoDamageMulti;
        gpMario->mCustomInfo->mMaxJumps = gpMario->mCustomInfo->mParams->Attributes.mJumpCount;

        gpMario->mModelData->mModel->mSizeMultiplier.x *= sizeX;
        gpMario->mModelData->mModel->mSizeMultiplier.y *= sizeY;
        gpMario->mModelData->mModel->mSizeMultiplier.z *= sizeZ;
        gpMario->mOceanOfs *= sizeY;

        gpMario->mWaterHealthDrainSpd /= gpMario->mCustomInfo->mParams->Attributes.mWaterHealthMultiplier;
        gpMario->mWaterHealthScubaDrainSpd /= gpMario->mCustomInfo->mParams->Attributes.mWaterHealthMultiplier;
        gpMario->mBaseBounceSpeed1 *= gpMario->mCustomInfo->mParams->Attributes.mBaseBounce1Multi;
        gpMario->mBaseBounceSpeed2 *= gpMario->mCustomInfo->mParams->Attributes.mBaseBounce2Multi;
        gpMario->mBaseBounceSpeed3 *= gpMario->mCustomInfo->mParams->Attributes.mBaseBounce3Multi;
        gpMario->mHealth = gpMario->mCustomInfo->mParams->Attributes.mHealth;
        gpMario->mMaxHealth = gpMario->mCustomInfo->mParams->Attributes.mMaxHealth;
        gpMario->mOBStep = gpMario->mCustomInfo->mParams->Attributes.mOBStep;
        gpMario->mOBMax = gpMario->mCustomInfo->mParams->Attributes.mOBMax;

        gpMario->mAttributes.mGainHelmet = gpMario->mCustomInfo->mParams->Attributes.mMarioHasHelmet;
        gpMario->mAttributes.mHasFludd = gpMario->mCustomInfo->mParams->Attributes.mCanUseFludd;
        gpMario->mAttributes.mIsShineShirt = gpMario->mCustomInfo->mParams->Attributes.mMarioHasShirt;

        if (gpMario->mCustomInfo->mParams->Attributes.mMarioHasGlasses)
        {
            wearGlass__6TMarioFv(gpMario);
        }
    }
    initFludd(gpMario);
}

//0x802715A0
void initYoshi()
{
    SMEFile *file = gInfo.mFile;
    TMario *gpMario = (TMario *)*(u32 *)TMarioInstance;
    TYoshi *gpYoshi = gpMario->mYoshi;

    if (!file || !file->FileHeader.mIsYoshi) return;

    RGBA<u8> *juiceColor = (RGBA<u8> *)YoshiJuiceColor;
    RGBA<u8> *yoshiColor = (RGBA<u8> *)YoshiColor;

    juiceColor[0] = file->Yoshi.mOrangeYoshi;
    juiceColor[1] = file->Yoshi.mPurpleYoshi;
    juiceColor[2] = file->Yoshi.mPinkYoshi;

    yoshiColor[0] = file->Yoshi.mGreenYoshi;
    yoshiColor[1] = file->Yoshi.mOrangeYoshi;
    yoshiColor[2] = file->Yoshi.mPurpleYoshi;
    yoshiColor[3] = file->Yoshi.mPinkYoshi;

    gpYoshi->mMaxJuice = file->Yoshi.mMaxJuice;
    gpYoshi->mMaxVSpdStartFlutter = file->Yoshi.mMaxVSpdStartFlutter;
    gpYoshi->mFlutterAcceleration = file->Yoshi.mFlutterAcceleration;
    gpYoshi->mMaxFlutterTimer = file->Yoshi.mMaxFlutterTimer;
}

//0x8029CCB0
void initCardColors()
{
    SMEFile *file = gInfo.mFile;
    TMarDirector *gpMarDirector = (TMarDirector *)*(u32 *)TMarDirectorInstance;

    if (file && file->FileHeader.mIsYoshi == true)
    {
        gpMarDirector->mGCConsole->mJuiceCardOrange = file->Yoshi.mOrangeYoshi;
        gpMarDirector->mGCConsole->mJuiceCardPurple = file->Yoshi.mPurpleYoshi;
        gpMarDirector->mGCConsole->mJuiceCardPink = file->Yoshi.mPinkYoshi;
    }

    if (file && file->FileHeader.mIsFludd == true && file->Fludd.mIsColorWater == true)
    {
        gpMarDirector->mGCConsole->mWaterLeftPanel = file->Fludd.mWaterColor;
        gpMarDirector->mGCConsole->mWaterRightPanel.R = lerp<u8>(0, file->Fludd.mWaterColor.R, 0.8125);
        gpMarDirector->mGCConsole->mWaterRightPanel.G = lerp<u8>(0, file->Fludd.mWaterColor.G, 0.8125);
        gpMarDirector->mGCConsole->mWaterRightPanel.B = lerp<u8>(0, file->Fludd.mWaterColor.B, 0.8125);
        gpMarDirector->mGCConsole->mWaterRightPanel.A = lerp<u8>(0, file->Fludd.mWaterColor.A, 0.8125);
    }
}

/*This works by taking the target id and matching it to the
/ ID of the first entry to have the same home ID as the target.
/
/ This makes a half decent linking system for the collision
/ triangles for functionalities like linked warping!
*/

static void parseWarpLinks(TMapCollisionData *col, WarpCollisionList *links, u32 validID, u32 idGroupSize = 0)
{
    u32 curDataIndex = 0;

    for (u32 i = 0; i < col->mFloorArraySize; ++i)
    {
        if (((col->mFloorData->mFloorTriangles[i].mCollisionType & 0x7FFF) - validID) <= idGroupSize ||
            ((col->mFloorData->mFloorTriangles[i].mCollisionType & 0x7FFF) - validID) <= idGroupSize + 1000)
        {

            links->mColList[curDataIndex] = {(TBGCheckData *)&col->mFloorData->mFloorTriangles[i],
                                             (u8)(col->mFloorData->mFloorTriangles[i].mValue4 >> 8),
                                             (u8)col->mFloorData->mFloorTriangles[i].mValue4};
            if (curDataIndex >= 0xFF) break;
            ++curDataIndex;
        }
    }
    links->arrayLength = curDataIndex;
}

//0x802B8B20
u32 initCollisionWarpLinks(char *name, u32 *dest)
{
    TMapCollisionData *collisionMap = (TMapCollisionData *)*(u32 *)TMapCollisionDataInstance;
    WarpCollisionList *warpDataArray = (WarpCollisionList *)malloc(sizeof(WarpCollisionList), 32);
    WarpCollisionList *warpDataPreserveArray = (WarpCollisionList *)malloc(sizeof(WarpCollisionList), 32);
    gInfo.mWarpColArray = warpDataArray;
    gInfo.mWarpColPreserveArray = warpDataPreserveArray;

    if (warpDataArray == nullptr)
        return calcKeyCode__Q26JDrama8TNameRefFPCc(name, dest);

    parseWarpLinks(collisionMap, warpDataArray, 16040);
    parseWarpLinks(collisionMap, warpDataPreserveArray, 16041, 1);

    return calcKeyCode__Q26JDrama8TNameRefFPCc(name, dest);
}

//0x802B57E4
void createUIHeap(u32 size, s32 alignment)
{
    TMarDirector *gpMarDirector = (TMarDirector *)*(u32 *)TMarDirectorInstance;
    gInfo.mGame6Heap = (u32 *)__nw__FUlP7JKRHeapi(size, (u32 *)*(u32 *)JKRSystemHeap, 32);
    gpMarDirector->mGame6Data = (u32 *)__nw__FUli(size, alignment);
}

//0x802A72A4
u32 initHUDElements(char *filepath)
{
    TFlagManager *gpFlagManager = (TFlagManager *)*(u32 *)TFlagManagerInstance;
    char buffer[32];
    s32 entrynum;

    sprintf(buffer, filepath, gpFlagManager->Type6Flag.CustomFlags.mHUDElement);
    entrynum = DVDConvertPathToEntrynum(buffer);

    if (entrynum < 0)
    {
        sprintf(filepath, filepath, 0);
    }
    else
    {
        strcpy(filepath, buffer);
    }

    return DVDConvertPathToEntrynum(filepath);
}

static u32 *switchArchive(char *curArchive, void *newArchive)
{
    u32 *volume = (u32 *)getVolume__13JKRFileLoaderFPCc(curArchive);
    unmountFixed__13JKRMemArchiveFv(volume);
    mountFixed__13JKRMemArchiveFPv15JKRMemBreakFlag(volume, newArchive);
    return volume;
}

//0x80172440
u32 *switchHUDOnStageLoad(char *curArchive, u32 *gameUI)
{
    TMarDirector *gpMarDirector = (TMarDirector *)*(u32 *)TMarDirectorInstance;
    TFlagManager *gpFlagManager = (TFlagManager *)*(u32 *)TFlagManagerInstance;
    TApplication *gpApplication = (TApplication *)TApplicationInstance;

    char buffer[32];

    if (gpApplication->mGamePad1->isPressed(TMarioGamePad::BUTTONS::DPAD_UP))
        gpFlagManager->Type6Flag.CustomFlags.mHUDElement = 1;
    else if (gpApplication->mGamePad1->isPressed(TMarioGamePad::BUTTONS::DPAD_DOWN))
        gpFlagManager->Type6Flag.CustomFlags.mHUDElement = 0;

    sprintf(buffer, (char *)0x803A42BC, gpFlagManager->Type6Flag.CustomFlags.mHUDElement); //"/data/game_%d.arc"
    strcpy(strstr(buffer, (char *)0x8041678C), (char *)0x80416794);                        //".arc", ".szs"

    if (DVDConvertPathToEntrynum(buffer) >= 0)
    {
        free(gpMarDirector->mGame6Data);
        *gameUI = loadToMainRAM__12JKRDvdRipperFPCcPUc15JKRExpandSwitchUlP7JKRHeapQ212JKRDvdRipper15EAllocDirectionUlPi(buffer, 0, 1, 0, gpMarDirector->mGame6Data, 1, 0, 0);
    }

    return switchArchive(curArchive, gameUI);
}

//0x80172440
/*
u32 *switchHUDOnStageLoad(char *curArchive, u32 *aramBlockConsole)
{
    TMarDirector *gpMarDirector = (TMarDirector *)*(u32 *)TMarDirectorInstance;
    TFlagManager *gpFlagManager = (TFlagManager *)*(u32 *)TFlagManagerInstance;
    TApplication *gpApplication = (TApplication *)TApplicationInstance;

    char buffer[32];

    if (gpApplication->mGamePad1->Buttons.mDPadUp)
        gpFlagManager->Type6Flag.CustomFlags.mHUDElement = 1;
    else if (gpApplication->mGamePad1->Buttons.mDPadDown)
        gpFlagManager->Type6Flag.CustomFlags.mHUDElement = 0;

    sprintf(buffer, (char *)0x803A42BC, gpFlagManager->Type6Flag.CustomFlags.mHUDElement); //"/data/game_%d.arc"
    strcpy(strstr(buffer, (char *)0x8041678C), (char *)0x80416794); //".arc", ".szs"

    if (DVDConvertPathToEntrynum(buffer) >= 0)
    {
        *aramBlockConsole = loadToAram__16JKRDvdAramRipperFPcUl15JKRExpandSwitchUlUl(buffer, 0, 0, 0, 0);
        free((void *)*aramBlockConsole);
    }

    u32 *archive = SMSSwitch2DArchive__FPCcR10TARAMBlock(curArchive, aramBlockConsole);
    s32 size = gpMarDirector->mGame6Data[1];

    //if (size >= 0)
        //memset((u8 *)gpMarDirector->mGame6Data + size, 0, 0x64000 - size); //0x64000 allocation
    
    return archive;
}
*/

//0x802B57E4
u32 *useCustomHUDHeap(u32 size, s32 alignment)
{
    return gInfo.mGame6Heap;
}