#include "define.hxx"
#include "funcs.hxx"
#include "types.hxx"

struct Vec3 {
    float x;
    float y;
    float z;
};

struct RGBA {
    u8 R;
    u8 G;
    u8 B;
    u8 A;
};

struct AreaEpisodeArray {
    u32 _00[0x10 / 4]; //0x0000
    u32* startArray; //0x0010
    u32* endArray; //0x0014
};

namespace JGeometry {

    template <typename T>
    
    struct TVec3 {
        T x;
        T y;
        T z;
    };

};

namespace JDrama {

    class TCamera {

        public:
            u32 _00[0x30 / 4]; //0x0000

    };

    class TLookAtCamera {

        public:
            TCamera mCamera; //0x0000
            JGeometry::TVec3<float> mUpVector; //0x0030
            JGeometry::TVec3<float> mTargetPosition; //0x003C
            float mProjectionFovy; //0x0048
            float mProjectionAspect; //0x004C

    };

    class TActor {

        public:
            u32 _00[0x10 / 4]; //0x0000
            JGeometry::TVec3<float> mCoordinates; //0x0010
            u32 _01[0x8 / 4]; //0x001C
            Vec3 mSize; //0x0024
            Vec3 mRotation; //0x0030
            u32 _02[0x8 / 4]; //0x003C

    };

};

class SMEFile {

    public:
        struct {
            char mMAGIC[4]; //0x0000 ("CODE")
            u32* mLoadAddress; //0x0004
            u32 mFileSize; //0x0008
            u8 mTotalSections; //0x000C
            bool mIsExecutable; //0x000D
            u16 mNextSectionOffset; //0x000E
            bool mIsShineShadow; //0x0010
            bool mIsMario; //0x0011
            bool mIsYoshi; //0x0012
            bool mIsMusic; //0x0013
            bool mIsFludd; //0x0014
            u8 mShineShadowFlag; //0x0015

            struct {
                bool mWalking : 1; //0x0016
                bool mJumping : 1;
                bool mHovering : 1;
                bool mSliding : 1;
                bool mSwimming : 1;
                bool mMarioOilRunning : 1;
                bool mMarioOilSlip : 1;
                bool mMarioHasFludd : 1;
                bool mMarioHasHelmet : 1;
                bool mMarioHasGlasses : 1;
                bool mMarioHasShirt : 1;
                u8 _00 : 4;
            } MarioStates;

            struct {
                u8 _00 : 4;
                bool mIsExMap : 1;
                bool mIsDivingMap : 1;
                bool mIsOptionMap : 1;
                bool mIsMultiPlayerMap : 1;
            } StageType; //0x0018

            u8 mPlayerID; //0x0019
            u16 _01; //0x001A
            u32 _02; //0x001C
        } FileHeader;
        
        struct {
            JGeometry::TVec3<float> mCoordinates; //0x0020
            float mSize; //0x002C
            float mStep; //0x0030
            RGBA mColor; //0x0034
            u8 mLayerCount; //0x0038
            u8 mDarkLevel; //0x0039
            u16 _00; //0x003A
        } Light;

        struct {
            float mSpeedMulti; //0x003C
            float mGravity; //0x0040
            float mBaseBounce1; //0x0044
            float mBaseBounce2; //0x0048
            float mBaseBounce3; //0x004C
            float mMaxFallNoDamage; //0x0050
            u16 mHealth; //0x0054
            u16 mMaxHealth; //0x0056
            u16 mOBStep; //0x0058
            u16 mOBMax; //0x005A
            u32 _00; //0x005C
        } Mario;

        struct {
            s32 mMaxJuice; //0x0060
            RGBA mGreenYoshi; //0x0064
            RGBA mOrangeYoshi; //0x0068
            RGBA mPurpleYoshi; //0x006C
            RGBA mPinkYoshi; //0x0070
            float mMaxVSpdStartFlutter; //0x0074
            float mFlutterAcceleration; //0x0078
            u16 mMaxFlutterTimer; //0x007C
            bool mYoshiHungry; //0x007E
            bool mIsEggFree; //0x007F
        } Yoshi;

        struct {
            bool mPlayMusic; //0x0080
            u8 mMusicID; //0x0081
            u8 mAreaID; //0x0082
            u8 mEpisodeID; //0x0083
            float mVolume; //0x0084
            float mSpeed; //0x0088
            float mPitch; //0x008C
        } Music;

        struct {
            u8 mPrimaryNozzle; //0x0090
            u8 mSecondaryNozzle; //0x0091
            RGBA mWaterColor; //0x0092
            bool mIsColorWater; //0x0096
            u8 _00; //0x0097
        } Fludd;
};

namespace JUTGamePad {

    class CButton {

        public:
            u32 _00 : 4; //0x0018
            u32 mMainStickUp : 1;
            u32 mMainStickDown : 1;
            u32 mMainStickRight : 1;
            u32 mMainStickLeft : 1;
            u32 _01 : 4;
            u32 mCStickUp : 1;
            u32 mCStickDown : 1;
            u32 mCStickRight : 1;
            u32 mCStickLeft : 1;
            u32 _02 : 3;
            u32 mSButton : 1;
            u32 mYButton : 1;
            u32 mXButton : 1;
            u32 mBButton : 1;
            u32 mAButton : 1;
            u32 _03 : 1;
            u32 mLButton : 1;
            u32 mRButton : 1;
            u32 mZButton : 1;
            u32 mDPadUp : 1;
            u32 mDPadDown : 1;
            u32 mDPadRight : 1;
            u32 mDPadLeft : 1;
            u32 _04[0x8 / 4]; //0x0004
            u16 _05; //0x000C
            u8 mLAnalog; //0x000E
            u8 mRAnalog; //0x000F
            float mLFloatAnalog; //0x0010
            float mRFloatAnalog; //0x0014
    };

    class CStick {

        public:
            float mXAxis; //0x0000
            float mYAxis; //0x0004
            float mDistanceFromNeutral; //0x0008
            short mAngle; //0x000C

    };

};

class J3DDrawBuffer {
};

class TBGCheckData {

    public:
        u16 mCollisionType; //0x0000
        s16 mValue4; //0x0002
        u32 _00; //0x0004
        float mMinHeight; //0x0008
        float mMaxHeight; //0x000C
        JGeometry::TVec3<float> mVertexA; //0x0010
        JGeometry::TVec3<float> mVertexB; //0x001C
        JGeometry::TVec3<float> mVertexC; //0x0028
        float _01[0x10 / 4];
        u32* callbackVTable; //0x0044

};

class THitActor {

    public:
        JDrama::TActor mActor; //0x0000
        THitActor** mCollidingObjs; //0x0044
        s16 mNumObjs; //0x0048
        s16 mMaxObjs; //0x004
        u32 mObjectID; //0x004C
        float mAttackRadius; //0x0050
        float mAttackHeight; //0x0054
        float mReceiveRadius; //0x0058
        float mReceiveHeight; //0x005C
        float _01; //0x0060
        u32 mObjectType; //0x0064

};

class TTakeActor {

    public:
        THitActor mHitActor; //0x0000
        TTakeActor* mHolder; //0x0068
        TTakeActor* mHeldObject; //0x006C

};

class TLiveActor {

    public:
        TTakeActor mTakeActor; //0x0000
        u32 _00[0x24 / 4]; //0x0070
        Vec3 mPositionalVelocity; //0x0094
        Vec3 mRotationalVelocity; //0x00A0
        Vec3 mSpeed; //0x00AC
        float mShadowRadius; //0x00B8
        float mMaxSpeed; //0x00BC
        u32 _01[0xC / 4]; //0x00C0
        float mGravity; //0x00CC
        u32 _02[0x20 / 4]; //0x00D0

};

class TMapObjBase {

    public:
        TLiveActor mLiveActor; //0x0000

        struct {
            u32 _00 : 7;
            bool mIsSunken : 1;
            u32 _01 : 1;
            bool mIsRide : 1;
            u32 _02 : 1;
            bool mIsCanTaken : 1;
            u32 _03 : 16;
            bool mIsShadowDead : 1;
            u32 _04 : 2;
            bool mIsObjDead : 1;
        } DrawInfo; //0x00F0

        u32 _00[0x8 / 4]; //0x00F4
        u16 mState; //0x00FC
        u16 _01; //0x00FE
        u32 _02[0x30 / 4]; //0x0100

};

class TCameraInbetween {

    public:
        u32 _00[0x30 / 4]; //0x0000
        JGeometry::TVec3<float> mSubjectPos; //0x0030

};

class CPolarSubCamera {

    public:
        JDrama::TLookAtCamera mCamera; //0x0000
        u32 _00[0x1C / 4]; //0x0050
        TCameraInbetween* mInbetween; //0x006C
        u32 _01[0x34 / 4]; //0x0070
        u16 _02; //0x00A4
        u16 mHorizontalAngle; //0x00A6
        float mInterpolateDistance; //0x00A8

};

class TGCConsole2 {

    public:
        u32 _00[0x24 / 4]; //0x0000
        s32 mShineCount; //0x0024
        s32 mCurWater; //0x0028
        u32 _01[0x18 / 4]; //0x002C
        bool mIsDEBSAlert; //0x0044
        bool mWaterCardRising; //0x0045
        bool mIsWaterCard; //0x0046
        u8 _02; //0x0047
        u32 _03[0x50 / 4]; //0x0048
        u16 _04; //0x0098
        RGBA mWaterLeftPanel; //0x009A
        RGBA mWaterRightPanel; //0x009E
        RGBA mJuiceCardOrange; //0x00A2
        RGBA mJuiceCardPurple; //0x00A6
        RGBA mJuiceCardPink; //0x00AA
        u16 _05; //0x00AE
        u32 _06[0x1F0 / 4]; //0x00B0
        u32* mWaterCardInfo; //0x02A0
        u32 _07[0x14 / 4]; //0x02A4
        u32 mWaterCardTopHeight; //0x02B8
        u32 _08[0x34 / 4]; //0x02BC
};

//This is not officially named, simply fits a thing I needed lul
class TBckData {

    public:
        u32 mAnimationID; //0x0000
        u32 _00[0xC / 4]; //0x0004
        float mFrameRate; //0x0010
        float mCurFrame; //0x0014
        
};

//This is not officially named, simply fits a thing I needed lul
class MActor {

    public:
        u32 _00[0xC / 4]; //0x0000
        TBckData* mBckInfo; //0x000C

};

class TFlagManager {

    public:
        struct {
            u8 m1Type[0x76]; //0x0000
            u16 _00; //0x0076
        } Type1Flag;

        struct {
            s32 mSaveCount; //0x0078
            s32 mLifeCount; //0x007C
            s32 mGelato5Record; //0x0080
            s32 mPianta2Record; //0x0084
            s32 _01[0x8 / 4]; //0x0088
            s32 mDelfinoCoinRecord; //0x0090
            s32 mBiancoCoinRecord; //0x0094
            s32 mRiccoCoinRecord; //0x0098
            s32 mGelatoCoinRecord; //0x009C
            s32 mPinnaCoinRecord; //0x00A0
            s32 mSirenaCoinRecord; //0x00A4
            s32 mPiantaCoinRecord; //0x00A8
            s32 mNokiCoinRecord; //0x00AC
            s32 _02[0x18 / 4]; //0x00B0
            s32 mNoki5Record; //0x00C8
        } Type2Flag;

        struct {
            u8 _00 : 2; //0x00CC
            u8 mLostLifePrev : 1;
            u8 mPlazaDemoWatched : 1;
            u8 mWatchPeachKidnappedPrev : 1;
            u8 mPpdBJRBalloonsPrev : 1;
            u8 mShineGetPrev : 1;
            u8 _01 : 2;
            u8 mPlaneCrashWatched : 1; //0x00CD
            u8 _02 : 1;
            u8 mCourtWatched : 1;
            u8 mPeachKNAPFMVWatched : 1;
            u8 mFluddTheftViewed : 1;
            u8 _03 : 1;
            u8 _04[2]; //0x00CE
        } Type3Flag;

        struct {
            s32 mShineCount; //0x00D0
            s32 mBlueCoinCount; //0x00D4
            s32 mGoldCoinCount; //0x00D8
            s32 mEpisodeNumber; //0x00DC
            s32 mSecondNozzle; //0x00E0
        } Type4Flag;

        struct {
            u8 mShineSpawned : 1; //0x00E4
            u8 mRiccoUnlockable : 1;
            u8 mGelatoUnlockable : 1;
            u8 mSunflowersRescue : 1;
            u8 mNokiAvailable : 1;
            u8 mPiantismoRaceComplete : 1;
            u8 _00 : 1;
            u8 mMantaSpawned : 1;
            u8 mHotelRising : 1; //0x00E5
            u8 mRedCoinSwitchPressed : 1;
            u8 mMechaBowserDefeated : 1;
            u8 mWigglerFalling : 1;
            u8 mMoleDefeated : 1;
            u8 _01 : 3;
            u8 _02[0xE]; //0x00E6
        } Type5Flag;

        struct {
            s32 mRedCoinCount; //0x00F4
            s32 mBJRBalloonCount; //0x00F8
            s32 _00; //0x00FC
            s32 mShadowMarioEvent; //0x0100
            u32 _01[0xF0 / 4]; //0x0104
            u8 mCustomShineIDs[0x80]; //0x01F4
            struct {
                u8 mIsGamePlus : 1; //0x0274
                u32 _00 : 31;
                u32 _01 : 32;
                u32 _02 : 32;
            } CustomFlags;
        } Type6Flag;

        struct {
            u8 mRumbleDisabled : 1; //0x0284
            u8 mSurroundSound : 1;
            u8 mSubtitlesDisabled : 1;
            u8 _00 : 5;
        } Type7Flag;

        struct {
            s32 mLanguage; //0x0288
        } Type8Flag;

        struct {
            u8 mRumbleEnabled : 1; //0x028C
            u8 mSubtitlesEnabled : 1;
        } Type9Flag;

        struct {
            s32 mSoundMode; //0x0290
            s32 mLanguage; //0x0294
        } TypeAFlag;

        long long mTimeOnLastSave; //0x0298
        long long mTimeOnLastSaveCopy; //0x02A0
        u8 mType1FlagSave[120]; //0x02A8
        u8 mType2FlagSave[84]; //0x0320
        long long mSavedTimeOnLastSave; //0x0378

};

class TMarioGamePad {

    public:
        u32 _00[0x18 / 4]; //0x0000

        struct {
            u32 _00 : 4; //0x0018
            bool mMainStickUp : 1;
            bool mMainStickDown : 1;
            bool mMainStickRight : 1;
            bool mMainStickLeft : 1;
            u32 _01 : 4;
            bool mCStickUp : 1;
            bool mCStickDown : 1;
            bool mCStickRight : 1;
            bool mCStickLeft : 1;
            u32 _02 : 3;
            bool mSButton : 1;
            bool mYButton : 1;
            bool mXButton : 1;
            bool mBButton : 1;
            bool mAButton : 1;
            u32 _03 : 1;
            bool mLButton : 1;
            bool mRButton : 1;
            bool mZButton : 1;
            bool mDPadUp : 1;
            bool mDPadDown : 1;
            bool mDPadRight : 1;
            bool mDPadLeft : 1;
            
        } Buttons;

        u32 _01[0x8 / 4]; //0x001C
        u16 _02; //0x0024
        u8 mLButtonAnalogU8; //0x0026
        u8 mRButtonAnalogU8; //0x0027
        float mLButtonAnalogFloat; //0x0028
        float mRButtonAnalogFloat; //0x002C
        u32 _03[0x18 / 4]; //0x0030
        float mMainStickLeftRight; //0x0048
        float mMainStickUpDown; //0x004C
        float mMainStickOffset; //0x0050
        u32 _04; //0x0054
        float mCStickLeftRight; //0x0058
        float mCStickUpDown; //0x005C
        float mCStickOffset; //0x0060
        u32 _05; //0x0064
        u32 _06[0x78 / 4]; //0x0058
        u16 _07; //0x00E0
        u8 _08; //0x00E2

        struct {
            u8 _00 : 6;
            bool mReadInput : 1;
            u8 _01 : 1;
        } State; //0x00E3
};

class TConductor {
};

class TDemoCannon {
    
    public:
        TMapObjBase mMapObjBase; //0x0000

};

class TMarioCap {
};

class TNozzleBase {

    public:
        u32 _00[0x2C / 4]; //0x0000
        float mEmitSize; //0x002C
        u32 _01[0x24 / 4]; //0x0030
        float mEmitRandom; //0x0054
        u32 _02[0x10 / 4]; //0x0058
        float mDistance; //0x0068
        u32 _03[0x38 / 4]; //0x006C
        float mMasterScale; //0x00A4
        u32 _04[0x10 / 4]; //0x00A8
        float mDistortionStrength; //0x00B8
        u32 _05[0x10 / 4]; //0x00BC
        s32 mMaxWater; //0x00CC
        u32 _06[0x38 / 4]; //0x00D0
        s16 mWaterStep; //0x0108
        u32 _10[0x278 / 4]; //0x010C
};

class TNozzleTrigger {

    public:
        TNozzleBase mBase; //0x0000
        u8 _00; //0x0384
        u8 _01; //0x0385
        u16 _02; //0x0386
        float _03; //0x0388
        u32 _04; //0x038C
};

class TWaterGun {
    
    public:
        u32 _00[0x8 / 4]; //0x0000
        class TMario* mMario; //0x0008
        TNozzleBase mSprayNozzleBase; //0x000C
        TNozzleTrigger mSprayNozzleTrigger; //0x0390
        TNozzleTrigger mRocketNozzle; //0x0720
        TNozzleBase mUnderWaterNozzle; //0x0AB0
        TNozzleBase mYoshiNozzleBase; //0x0E34
        TNozzleTrigger mYoshiNozzleTrigger; //0x11B8
        TNozzleTrigger mHoverNozzle; //0x1548
        TNozzleTrigger mTurboNozzle; //0x18D8
        TNozzleBase* mNozzleList[6]; //0x1C68
        s32 mCurrentWater; //0x1C80
        u8 mCurrentNozzle; //0x1C84
        u8 mSecondNozzle; //0x1C85
        bool mIsEmitWater; //0x1C86
        u8 _13; //0x1C87
        u32 _14[0x8 / 4]; //0x1C88
        JGeometry::TVec3<float> mGeometry[10]; //0x1C90
        u32 _15; //0x1D08
        u32* mEmitInfo; //0x1D0C
        char* mPrmPath; //0x1D14
        char* mRocketPath; //0x1D18
        u32 _16[0xA0 / 4]; //0x1D1C

};

class TNozzleBox {

    public:
        TMapObjBase mObjBase; //0x0000
        u32 _00[0x18 / 4]; //0x0130
        u32 mNozzleToRegen; //0x0148
        TMapObjBase* mNozzleItem; //0x014C
        float mThrowLength; //0x0150
        float mThrowHeight; //0x0154
        char* mStringID; //0x0158
        bool mIsValid; //0x015C
        u8 _01; //0x015D
        u16 _02; //0x015E
        u16 _03; //0x0160
        u16 _04; //0x0162

};

class TEggYoshi {

    public:
        TMapObjBase mObjBase; //0x0000
        u32 _00[0x18 / 4]; //0x0130
        MActor* mActor; //0x0148
        s32 mWantedFruit; //0x014C
        TMario* mMario; //0x0150
};

class TWaterManager {

    public:
        u32 _00[0xC / 4]; //0x0000
        u8 mSprayQuality; //0x000C
        u8 _01; //0x000D
        u16 _02; //0x000E
        s16 mMaxEmit; //0x0010
        s16 mEmitCount; //0x0012
        u32 _03[0x5D48 / 4]; //0x0014
        u16 _04; //0x5D5C
        u8 _05; //0x5D5E
        s8 mWaterCardType; //0x5D5F
        
        struct {
            u8 _00 : 6;
            bool mMaskObjects : 1;
            bool mShowShadow : 1;
            u8 _01 : 8;
        } LightType; //0x5D60
        
        u16 _06; //0x5D62
        u32 _07[0xA8 / 4]; //0x5D64
        float mSize; //0x5E0C
        float _08[0x30 / 4]; //0x5E10
        float mSphereStep; //0x5E40
        u8 mLayerCount; //0x5E44
        u8 mDarkLevel; //0x5E45
        u8 _09; //0x5E46
        RGBA mColor; //0x5E47
};

class TYoshi {

    public:
        s8 mState; //0x0000
        u8 _00; //0x0001
        u16 mSubState; //0x0002 ??
        u32 _01; //0x0004
        s32 mMaxJuice; //0x0008
        s32 mCurJuice; //0x000C
        class TMario* mMario; //0x0010
        u32 _02[0xC / 4]; //0x0014
        JGeometry::TVec3<float> mCoordinates; //0x0020
        u32 _03[0x8 / 4]; //0x002C
        MActor* mAnimationTable; //0x0034
        u32 _04[0x4C / 4]; //0x0038
        float mRedComponent; //0x0084
        float mGreenComponent; //0x0088
        float mBlueComponent; //0x008C
        u32 _05[0x28 / 4]; //0x0090
        u8 mFlutterState; //0x00B8
        u8 _06; //0x00B9
        u16 mFlutterTimer; //0x00BA
        u16 mMaxFlutterTimer; //0x00BC
        u16 _07; //0x00BE
        float mMaxVSpdStartFlutter; //0x00C0
        float mFlutterAcceleration; //0x00C4
        u32 _08[0x8 / 4]; //0x00C8
        s8 mType; //0x00D0
        u8 _09; //0x00D1
        u16 _10; //0x00D2
        u32 _11[0x1C / 4]; //0x00D4
        TEggYoshi* mEgg; //0x00F0
};

class TMario {

    public:
        TTakeActor mTakeActor; //0x0000
        u32 _00[0xC / 4]; //0x0070
        u32 mState; //0x007C
        u32 mPrevState; //0x0080
        u16 mSubState; //0x0084
        u16 mSubStateTimer; //0x0086
        u32 _01; //0x0088
        float mBaseAcceleration; //0x008C
        u16 mAccelerationDirection; //0x0090
        u16 _02; //0x0092
        u16 mAngleX; //0x0094
        u16 mAngleY; //0x0096
        u16 mAngleZ; //0x0098
        u16 _03; //0x009A
        u32 _04[0x8 / 4]; //0x009C
        Vec3 mSpeed; //0x00A4
        float mForwardSpeed; //0x00B0
        u32 _05[0x14 / 4]; //0x00B4
        float mTerminalVelocity; //0x00C8
        u32 _06[0x14 / 4]; //0x00CC
        TBGCheckData* mFloorTriangle; //0x00E0
        TBGCheckData* mFloorTriangleCopy; //0x00E4
        float mCeilingAbove; //0x00E8
        float mFloorBelow; //0x00EC
        float mWaterHeight; //0x00F0
        u32 _07[0x24 / 4]; //0x00F4

        struct {
            u32 _04 : 10;
            bool mIsGone : 1;
            bool mIsShineShirt : 1;
            u32 _03 : 2;
            bool mIsWater : 1;
            bool mIsShallowWater : 1;
            bool mHasFludd : 1;
            u32 _02 : 1;
            bool mGainHelmet : 1;
            bool mGainHelmetFlwCamera : 1;
            bool mIsGroundPoundSitUp : 1;
            bool mIsGameOver : 1;
            u32 _01 : 5;
            bool mLeftRecentWater : 1;
            bool mTalkingNPC : 1;
            bool mIsVisible : 1;
            bool mAboveSewerFloor : 1;
            u32 _00 : 1;
        } mAttributes; //0x0118

        struct {
            u32 _03 : 14;
            bool mIsWater : 1;
            bool mIsShallowWater : 1;
            bool mHasFludd : 1;
            u32 _02 : 2;
            bool mGainHelmet : 1;
            bool mIsGroundPoundSitUp : 1;
            bool mIsTooBad : 1;
            u32 _01 : 5;
            bool mLeftRecentWater : 1;
            bool mTalkingNPC : 1;
            bool mIsVisible : 1;
            bool mAboveSewerFloor : 1;
            u32 _00 : 1;
        } mPrevAttributes; //0x011C

        u16 mHealth; //0x0120
        u16 _08; //0x0122
        u32 _09[0x24 / 4]; //0x0124

        struct {
            bool mIsAirborn : 1; 
            bool mIsFaceUsed : 1;
            bool mIsSpinBounce : 1;
            bool mIsDisableInput : 1;
            u16 _00 : 12;
        } CollisionFlags; //0x0148
        
        u16 mPrevCollision; //0x014A
        s16 mColHealthTimer; //0x014C
        u16 _09a; //0x014E
        u32 _09b[0x148 / 4]; //0x0150
        u32 mInitialWater; //0x0298
        u32 _10[0x10 / 4]; //0x029C
        float lastGroundedHeight; //0x02AC
        u32 _11[0x8 / 4]; //0x02B0
        u16 _12; //0x02B8
        u16 mOBTimer; //0x02BA
        u32 _13[0xC8 / 4]; //0x02BC
        TTakeActor* mGrabTarget; //0x0384
        u32 _14[0xC / 4]; //0x0388
        J3DDrawBuffer* mDrawBufferA; //0x0394
        J3DDrawBuffer* mDrawBufferB; //0x0398
        u32 _14a[0x44 / 4]; //0x039C
        TMarioCap* mCap; //0x03E0
        TWaterGun* mFludd; //0x03E4
        u32 _15[0x8 / 4]; //0x03E8
        TYoshi* mYoshi; //0x03F0
        u32 _16[0x108 / 4]; //0x03F4
        TMarioGamePad* mController; //0x04FC
        u32 _17[0x8C / 4]; //0x0500
        u16 mMaxHealth; //0x058C
        u16 _18; //0x058E
        u32 _19[0x240 / 4]; //0x0590
        float mBaseBounceSpeed1; //0x07D0
        u32 _20[0x10 / 4]; //0x07D4
        float mBaseBounceSpeed2; //0x07E4
        u32 _21[0x10 / 4]; //0x07E8
        float mBaseBounceSpeed3; //0x07F8
        u32 _22[0xC4 / 4]; //0x07FC
        float mMaxFallNoDamage; //0x08C0
        u32 _23[0xC4 / 4]; //0x08C4
        u16 mOBStep; //0x0988
        u16 _24; //0x098A
        u32 _25[0x10 / 4]; //0x098C
        u16 mOBMax; //0x099C
        u16 _26; //0x099E
        u32 _27[0x178 / 4]; //0x09A0
        float mGravity; //0x0B18
        u32 _28[0x38 / 4]; //0x0B1C
        float mAirborneHSpeedMul; //0x0B54
        u32 _29[0x10 / 4]; //0x0B58
        float mDefaultAccelerationMul; //0x0B68
        u32 _30[0x8A8 / 4]; //0x0B6C
        float mTRopeAirborneAccelMul; //0x1414
        u32 _31[0xE04 / 4]; //0x1418
        float mVSpeedYoshiMul; //0x221C
        u32 _32[0x3C / 4]; //0x2220
        float mFSpeedFlutterMul; //0x226C
        u32 _33[0x10 / 4]; //0x2270
        float mBSpeedFlutterMul; //0x2280
        u32 _34[0x200C / 4]; //0x2284
        float mAllSpeedMultiplier; //0x4290
        u8 mMaxJumps; //0x4294
        u8 mCurJump; //0x4295
        u8 mPlayerID; //0x4296
        u8 _35; //0x4297

};

class TShine {

    public:
        TLiveActor mObj; //0x0000
        u32 _07[0xC / 4]; //0x00F0
        u16 mPositionState; //0x00FC
        u16 _08; //0x00FE
        u32 _09[0x34 / 4]; //0x0100
        u32 mObjectID; //0x0134
        u32 _09a[0x1C / 4]; //0x0138
        u32 mType; //0x0154
        u32 _09b[0x50 / 4]; //0x0158
        struct Vec3 mGlowSize; //0x01A8
        u8 isAlreadyObtained; //0x01B4
        u8 _10; //0x01B5
        u16 _11; //0x01B6
        u32 _12[0x40 / 4]; //0x01B8

};

class TMarDirector {

    public:
        u32 _00[0x4C / 4]; //0x0000
        u16 mGameState; //0x004C
        u16 _02; //0x004E
        u32 _03[0x14 / 4]; //0x0050
        u8 mLastState; //0x0064
        u8 _04; //0x0065
        u16 _05; //0x0066
        u32 _06[0xC / 4]; //0x0068
        TGCConsole2* mGCConsole; //0x0074
        u32 _07; //0x0078
        u8 mAreaID; //0x007C
        u8 mEpisodeID; //0x007D
        u16 _09; //0x007E
        u32 _10[0x2C / 4]; //0x0080
        u32* sNextState; //0x00AC
        u32 _11[0x1A4 / 4]; //0x00B0
        TDemoCannon* mCannonObj; //0x0254
        u32 _12; //0x0258
        TShine* mCollectedShine; //0x025C

};

class TApplication {

    public:
        u32 _00; //0x0000
        TMarDirector* mMarDirector; //0x0004
        u32 _01; //0x0008
        u16 _02; //0x000C
        u8 mAreaID; //0x000E
        u8 mEpisodeID; //0x000F
        u32 _03[0x20 / 4]; //0x0010
        AreaEpisodeArray* mStringPaths; //0x0030

};

typedef u32 JSUStreamSeekFrom;

struct JSUIosBase {
    virtual ~JSUIosBase() = 0;
    virtual s32 getAvailable() const = 0;
    virtual void skip(s32 len) = 0;
    virtual void readData(void* dest, s32 len) = 0;
    virtual s32 getLength() const = 0;
    virtual s32 getPosition() const = 0;
    virtual void seekPos(s32 address, JSUStreamSeekFrom whence);
};

struct JSUInputStream : public JSUIosBase {
    void read(void* dest, s32 len);
};

struct JSUOutputStream : public JSUIosBase {
    void write(const void* source, s32 len);
};

struct CustomInfo {
    SMEFile* mFile; //0x0000

    struct {
        u16 mPrevShineCount; //0x0004
        bool mIsShineShadowGrowing; //0x0006
        u8 mLightType; //0x0007
        float mPrevSize; //0x0008
        float mNextSize; //0x0010
        JGeometry::TVec3<float> mShineShadowCoordinates; //0x0014
        float mShineShadowBase; //0x0020
        float mStepContext; //0x0024
    } Light;

    struct {
        Vec3 yoshiWaterSpeed; //0x0028
    } Mario;

    struct {
        u8 mCurrentNozzle; //0x0034
        u8 mSecondNozzle; //0x0035
        s32 mCurrentWater; //0x0036
        u16 _00; //0x003A
    } Fludd;

    struct {
        TMario* mMario[4]; //0x003C
        u8 mCurPlayerCount; //0x004C
        u8 mMaxPlayerCount; //0x004D
        bool mIsActive[4]; //0x004E
        u8 mCurPlayerID[4]; //0x0052
        u8 mCurPlayerTimer[4]; //0x0056
        u8 mMaxPlayerTimer; //0x005A
        bool mIsFreePlay; //0x005B
    } PlayerData;
};

CustomInfo gInfo;
RGBA waterColor;
RGBA juiceColor;
RGBA yoshiColor;

static inline void flushAddr(void* addr)
{
    dcbf(addr);
    icbi(addr);
}

u8 linearInterpolateU8(u8 a, u8 b, float factor) {
    return a + factor * (b - a);
}

float linearInterpolateU32toFloat(u32 a, u32 b, float factor) {
    return a + factor * (b - a);
}

float linearInterpolateFloat(float a, float b, float factor) {
    return a + factor * (b - a);
}