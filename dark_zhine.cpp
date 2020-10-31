#include "includes/eclipse.hxx"

/*
VTABLE

.long 0x00000000, 0x00000000, 0x8007BC50, 0x80007D70
.long 0x8003C39C, 0x802FA6F4, 0x802FA6F8, 0x802FA6FC
.long 0x80075C44* 0x00000000, 0x00000000, 0x8007C2C0
.long 0x803370C0, 0x8033720C, 0x80037214, 0x8033721C
.long 0x80337220, 0x80337228, 0x8033722C, 0x80337230
.long 0x*/

class TDarkZhine
{

    struct ZhineFile
    {
        u32 *mCodeBlock[8]; //0x0000
        u32 mBlockSize[8];  //0x0020

        struct
        {
            JGeometry::TVec3<float> mBoundingPoint; //0x0040
            float mBoundingAreaRadius;              //0x004C
            float mDistanceFromMario;               //0x0050
            float mSpeedMultiplier;                 //0x0054
            float mAccelerationRate;                //0x0058
            float mShockRadius;                     //0x005C
            float mMaxSpeed;                        //0x0060
            float mStampRadius;                     //0x0064
            float mRisingRate;                      //0x0068
            float mMaxPoundingHeight;               //0x006C
            s16 mPoundingTimerMax;                  //0x0070
            s16 mGoopingTimerMax;                   //0x0072
            s16 mShockingTimerMax;                  //0x0074
            s16 mRollingTimerMax;                   //0x0076
            s16 mFramesToCleanOnce;                 //0x0078
            u8 mGoopLevel;                          //0x007A
        } /*__attribute__((packed))*/ ZhineBinData;
    };

    enum PoundingState
    {
        INACTIVE = 0,
        DROPPING = 11,
        SHOCKING = 22,
        GROUNDROLL = 33,
        RISING = 44
    };

    TBossGesso mBossInfo;
    JGeometry::TVec3<float> mBoundingPoint; //0x01B0
    float mGroundSpeed;                     //0x01BC
    float mBoundingAreaRadius;              //0x01C0
    float mDistanceFromMario;
    float mSpeedMultiplier;
    float mAccelerationRate;
    float mShockRadius;
    float mMaxSpeed;
    float mStampRadius;
    bool mIsFollowMario;
    bool mIsPounding;
    bool mIsGooping;
    bool mIsShocking;
    s16 mPoundingTimer;
    s16 mGoopingTimer;
    s16 mShockingTimer;
    s16 mRollingTimer;
    s16 mStatusTimer;
    s16 mCleaningTimer;
    s16 mFramesToCleanOnce;
    s16 mPoundingTimerMax;
    s16 mGoopingTimerMax;
    s16 mShockingTimerMax;
    s16 mRollingTimerMax;
    PoundingState mPoundingStatus;
    bool mIsDarkZhine;
    float mRisingRate;
    float mMaxPoundingHeight;
    JDrama::TActor *mTarget;

public:
    void setBoundingPoint(JGeometry::TVec3<float> *vec) { mBoundingPoint = *vec; }
    void setGroundSpeed(float vec) { mGroundSpeed = vec; }
    void setBoundingRadius(float r) { mBoundingAreaRadius = r; }
    void setMarioDistance(float d) { mDistanceFromMario = d; }
    void setSpeedMultiplier(float speedm) { mSpeedMultiplier = speedm; }
    void setAccelerationRate(float accel) { mAccelerationRate = accel; }
    void setShockRadius(float r) { mShockRadius = r; }
    void setMaxSpeed(float speed) { mMaxSpeed = speed; }
    void setStampRadius(float r) { mStampRadius = r; }
    void setIsFollowMario(bool state) { mIsFollowMario = state; }
    void setIsPounding(bool state) { mIsPounding = state; }
    void setIsGooping(bool state) { mIsGooping = state; }
    void setIsShocking(bool state) { mIsShocking = state; }
    void setPoundingTimer(u16 timer) { mPoundingTimer = timer; }
    void setGoopingTimer(u16 timer) { mGoopingTimer = timer; }
    void setShockingTimer(u16 timer) { mShockingTimer = timer; }
    void setRollingTimer(u16 timer) { mRollingTimer = timer; }
    void setStatusTimer(u16 timer) { mStatusTimer = timer; }
    void setCleaningTimer(u16 timer) { mCleaningTimer = timer; }
    void setFramesToCleanOnce(u16 timer) { mFramesToCleanOnce = timer; }
    void setPoundingTimerMax(u16 timer) { mPoundingTimerMax = timer; }
    void setGoopingTimerMax(u16 timer) { mGoopingTimerMax = timer; }
    void setShockingTimerMax(u16 timer) { mShockingTimerMax = timer; }
    void setRollingTimerMax(u16 timer) { mRollingTimerMax = timer; }
    void setPoundingStatus(PoundingState state) { mPoundingStatus = state; }
    void setIsDarkZhine(bool state) { mIsDarkZhine = state; }
    void setRisingRate(float rate) { mRisingRate = rate; }
    void setMaxPoundingHeight(float m) { mMaxPoundingHeight = m; }

    JGeometry::TVec3<float> getBoundingPoint() { return mBoundingPoint; }
    float getGroundSpeed() { return mGroundSpeed; }
    float getBoundingRadius() { return mBoundingAreaRadius; }
    float getMarioDistance() { return mDistanceFromMario; }
    float getSpeedMultiplier() { return mSpeedMultiplier; }
    float getAccelerationRate() { return mAccelerationRate; }
    float getShockRadius() { return mShockRadius; }
    float getMaxSpeed() { return mMaxSpeed; }
    float getStampRadius() { return mStampRadius; }
    bool getIsFollowMario() { return mIsFollowMario; }
    bool getIsPounding() { return mIsPounding; }
    bool getIsGooping() { return mIsGooping; }
    bool getIsShocking() { return mIsShocking; }
    s16 getPoundingTimer() { return mPoundingTimer; }
    s16 getGoopingTimer() { return mGoopingTimer; }
    s16 getShockingTimer() { return mShockingTimer; }
    s16 getRollingTimer() { return mRollingTimer; }
    s16 getStatusTimer() { return mStatusTimer; }
    s16 getCleaningTimer() { return mCleaningTimer; }
    s16 getFramesToCleanOnce() { return mFramesToCleanOnce; }
    s16 getPoundingTimerMax() { return mPoundingTimerMax; }
    s16 getGoopingTimerMax() { return mGoopingTimerMax; }
    s16 getShockingTimerMax() { return mShockingTimerMax; }
    s16 getRollingTimerMax() { return mRollingTimerMax; }
    PoundingState getPoundingStatus() { return mPoundingStatus; }
    bool getIsDarkZhine() { return mIsDarkZhine; }
    float getRisingRate() { return mRisingRate; }
    float getMaxPoundingHeight() { return mMaxPoundingHeight; }

    float getAngleToTarget()
    {
        JGeometry::TVec3<float> zhineCoordinates = mBossInfo.mSpineEnemy.mLiveActor.mTakeActor.mHitActor.mActor.mCoordinates;

        return atan2(this->mTarget->mCoordinates.x - zhineCoordinates.x,
                     this->mTarget->mCoordinates.z - zhineCoordinates.z);
    }

    bool isTargetInRangeToHome(JGeometry::TVec3<float> home, float r)
    {
        return (fabsf__Ff(this->mTarget->mCoordinates.x - home.x) +
                fabsf__Ff(this->mTarget->mCoordinates.y - home.y) +
                fabsf__Ff(this->mTarget->mCoordinates.z - home.z) <
                r);
    }

    void advanceRollMovement(TPollutionManager *gpPollutionManager)
    {
        JDrama::TActor *zhineActor = &mBossInfo.mSpineEnemy.mLiveActor.mTakeActor.mHitActor.mActor;

        if (getRollingTimer() < getRollingTimerMax()/2)
            this->mGroundSpeed = sigmoidCurve(getRollingTimer(), 0, getMaxSpeed()*getSpeedMultiplier(), 300, 0.04*getAccelerationRate());
        else
            this->mGroundSpeed = sigmoidCurve(getRollingTimer() - getRollingTimerMax()/2, 0, getMaxSpeed()*getSpeedMultiplier(), 300, -0.04*getAccelerationRate());

        if (this->mGroundSpeed > getMaxSpeed())
            this->mGroundSpeed = getMaxSpeed();
        else if (this->mGroundSpeed < 0)
            this->mGroundSpeed = 0;

        zhineActor->mCoordinates.x += (this->mGroundSpeed * sinf(angleToRadians(zhineActor->mRotation.y)));
        zhineActor->mCoordinates.z += (this->mGroundSpeed * cosf(angleToRadians(zhineActor->mRotation.y)));
        this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.x = (this->mGroundSpeed * sinf(angleToRadians(zhineActor->mRotation.y)));
        this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.z = (this->mGroundSpeed * cosf(angleToRadians(zhineActor->mRotation.y)));

        stamp__17TPollutionManagerFUsffff(gpPollutionManager, 1,
                                          zhineActor->mCoordinates.x,
                                          zhineActor->mCoordinates.y,
                                          zhineActor->mCoordinates.z,
                                          (float)400);
    }

    PoundingState advanceDropAttack(TPollutionManager *gpPollutionManager, TMario *gpMario)
    {
        JDrama::TActor *zhineActor = &this->mBossInfo.mSpineEnemy.mLiveActor.mTakeActor.mHitActor.mActor;

        if (getPoundingStatus() == PoundingState::DROPPING)
        {
            this->mBossInfo.mSpineEnemy.mLiveActor.mGravity = 1;
            this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.x = 0;
            this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.z = 0;
            this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.y *= this->mSpeedMultiplier;

            if (zhineActor->mCoordinates.y - this->mBossInfo.mSpineEnemy.mLiveActor.mFloorBelow->mMaxHeight < 10 &&
                zhineActor->mCoordinates.y >= this->mBossInfo.mSpineEnemy.mLiveActor.mFloorBelow->mMinHeight)
            {

                startShake__12TCameraShakeF16EnumCamShakeModef(*(u32 *)TCameraShakeInstance, 0x27, (float)1);
                startSoundActor__Q214MSoundSESystem8MSoundSEFUlPC3VecUlPP8JAISoundUlUc(6158, zhineActor->mCoordinates,
                                                                                       0, 0, 0, 4);
                start__9RumbleMgrFiP3Vec(*(u32 *)GamePad1Instance, 8, zhineActor->mCoordinates);
                stamp__17TPollutionManagerFUsffff(gpPollutionManager, 1,
                                                  zhineActor->mCoordinates.x,
                                                  this->mBossInfo.mSpineEnemy.mLiveActor.mFloorBelow->mMaxHeight,
                                                  zhineActor->mCoordinates.z,
                                                  mStampRadius);

                if (this->mBossInfo.mGoopLevel > (0xFF - 0x30))
                {
                    this->mBossInfo.mGoopLevel = 0xFF;
                }
                else
                {
                    this->mBossInfo.mGoopLevel += 0x20;
                }

                setPoundingStatus(PoundingState::SHOCKING);
                setStatusTimer(getShockingTimerMax());
            }
        }
        else if (getPoundingStatus() == PoundingState::SHOCKING)
        {
            if (!(gpMario->mState & STATE_AIRBORN) &&
                isTargetInRangeToHome(zhineActor->mCoordinates, getShockRadius()) &&
                (gpMario->mState != STATE_KNCK_LND &&
                 gpMario->mState != 0x4045C))
            {
                decHP__6TMarioFi(gpMario, 1);
                changePlayerStatus__6TMarioFUlUlb(gpMario, STATE_KNCK_LND, 0, 0);
            }

            if (getStatusTimer() <= 0)
            {
                setPoundingStatus(PoundingState::GROUNDROLL);
                setStatusTimer(getRollingTimerMax());
            }
        }
        else if (getPoundingStatus() == PoundingState::GROUNDROLL)
        {
            if (zhineActor->mCoordinates.y - this->mBossInfo.mSpineEnemy.mLiveActor.mFloorBelow->mMaxHeight > 100)
            {
                setPoundingStatus(PoundingState::RISING);
                this->mBossInfo.mSpineEnemy.mLiveActor.mGravity *= (-1 * getRisingRate() * getSpeedMultiplier());
            }
            else if (getRollingTimer() > 0)
            {
                advanceRollMovement(gpPollutionManager);
                if (!(getStatusTimer() % 15))
                {
                    if (this->mBossInfo.mGoopLevel == 0xFF)
                    {
                        this->mBossInfo.mGoopLevel = 0xFF;
                    }
                    else
                    {
                        this->mBossInfo.mGoopLevel += 1;
                    }
                }
            }
            else
            {
                setPoundingStatus(PoundingState::RISING);
                zhineActor->mCoordinates.y += 1;
                this->mBossInfo.mSpineEnemy.mLiveActor.mGravity *= (-1 * getRisingRate() * getSpeedMultiplier());
            }
        }
        else if (getPoundingStatus() == PoundingState::RISING)
        {
            float averageFloorHeight = (this->mBossInfo.mSpineEnemy.mLiveActor.mFloorBelow->mMaxHeight +
                                        this->mBossInfo.mSpineEnemy.mLiveActor.mFloorBelow->mMinHeight) /
                                       2;
            this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.x = 0;
            this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.z = 0;

            if (zhineActor->mCoordinates.y - averageFloorHeight > 500 &&
                zhineActor->mCoordinates.y > getBoundingPoint().y + 100)
            {

                this->mBossInfo.mSpineEnemy.mLiveActor.mGravity *= (-1 * getRisingRate() * getSpeedMultiplier());
                setPoundingStatus(PoundingState::INACTIVE);
            }
        }
        else
        {
            setPoundingStatus(PoundingState::INACTIVE);
        }
        setStatusTimer(getStatusTimer() - 1);
        return getPoundingStatus();
    }

    void advanceGoopDroplet()
    {
        JDrama::TActor *zhineActor = &this->mBossInfo.mSpineEnemy.mLiveActor.mTakeActor.mHitActor.mActor;
        TBGPolDrop *pollutionDrop = this->mBossInfo.mPollutionDrop;
        Vec3<float> launchVelocity;

        if (pollutionDrop->mStatus == pollutionDrop->DropStatus::DEAD)
        {
            launchVelocity = {this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.x,
                                this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.y/2,
                                this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.z};

            launch__10TBGPolDropFRCQ29JGeometry8TVec3_f(this->mBossInfo.mPollutionDrop,
                                                        zhineActor->mCoordinates,
                                                        launchVelocity);
        }
        else
        {
            move__10TBGPolDropFv(pollutionDrop);
        }
    }

    void update(TMario *gpMario)
    {
        TPollutionManager *gpPollutionManager = (TPollutionManager *)*(u32 *)TPollutionManagerInstance;
        JDrama::TActor *zhineActor = &this->mBossInfo.mSpineEnemy.mLiveActor.mTakeActor.mHitActor.mActor;
        float targetAngle;

        float averageFloorHeight = (this->mBossInfo.mSpineEnemy.mLiveActor.mFloorBelow->mMaxHeight +
                                    this->mBossInfo.mSpineEnemy.mLiveActor.mFloorBelow->mMinHeight)/2;

        if (getIsPounding() == false)
        {
            if (getIsGooping() == true)
                advanceGoopDroplet();

            if (zhineActor->mCoordinates.y - averageFloorHeight < 700)
            {
                if (zhineActor->mCoordinates.y - this->mBossInfo.mSpineEnemy.mLiveActor.mFloorBelow->mMaxHeight < 10)
                {
                    zhineActor->mCoordinates.y += 1;
                }
                this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.y = 1 * getSpeedMultiplier();
            }
            else if (zhineActor->mCoordinates.y - averageFloorHeight > 700)
            {
                if (zhineActor->mCoordinates.y < getBoundingPoint().y - getBoundingRadius())
                {
                    zhineActor->mCoordinates.y = getBoundingPoint().y - getBoundingRadius();
                    this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.x = 0;
                }
                else
                {
                    this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.y = -1 * getSpeedMultiplier();
                }
            }
        }

        if (isTargetInRangeToHome(zhineActor->mCoordinates, getShockRadius()) == true && getIsPounding() == false)
        {
            setIsFollowMario(true);
            setPoundingTimer(getPoundingTimer() - 1);
            setGoopingTimer(getGoopingTimer() - 1);
            this->mBossInfo.mSpineEnemy.mLiveActor.mGravity = 0;
        }
        else
        {
            setIsFollowMario(false);
        }

        if (getPoundingStatus() == PoundingState::DROPPING || getPoundingStatus() == PoundingState::INACTIVE)
            moveObject__10TLiveActorFv((TLiveActor *)this);

        if (getIsFollowMario() == true)
        {
            setPoundingTimer(getPoundingTimer() - 1);
            setGoopingTimer(getGoopingTimer() - 1);

            if (getPoundingTimer() <= 0 && zhineActor->mCoordinates.y - averageFloorHeight < getMaxPoundingHeight())
            {
                setIsPounding(true);
                setPoundingStatus(PoundingState::DROPPING);
                setPoundingTimer(getPoundingTimerMax());
            }

            if (getGoopingTimer() <= 0)
            {
                setIsGooping(true);
                setGoopingTimer(getGoopingTimerMax());
            }

            this->mGroundSpeed += (getAccelerationRate() * this->mSpeedMultiplier);
            if (this->mGroundSpeed > this->mMaxSpeed)
                this->mGroundSpeed = this->mMaxSpeed;

            this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.x = this->mGroundSpeed * sinf(angleToRadians(zhineActor->mRotation.y));
            this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.z = this->mGroundSpeed * cosf(angleToRadians(zhineActor->mRotation.y));
        }
        else if (isTargetInRangeToHome(zhineActor->mCoordinates, getShockRadius()) &&
                 getPoundingStatus() != PoundingState::GROUNDROLL)
        {
            this->mGroundSpeed -= (getAccelerationRate() * this->mSpeedMultiplier);
            if (this->mGroundSpeed < 0)
                this->mGroundSpeed = 0;

            this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.x = this->mGroundSpeed * sinf(angleToRadians(zhineActor->mRotation.y));
            this->mBossInfo.mSpineEnemy.mLiveActor.mSpeed.z = this->mGroundSpeed * cosf(angleToRadians(zhineActor->mRotation.y));
        }

        if (isTargetInRangeToHome(zhineActor->mCoordinates, getShockRadius()))
        {
            if (getIsPounding() && advanceDropAttack(gpPollutionManager, gpMario) == PoundingState::INACTIVE)
                setIsPounding(false);
            else
                this->mBossInfo.mSpineEnemy.mLiveActor.mGravity = 0;
        }
        else
        {
            setIsPounding(false);
            setPoundingStatus(PoundingState::INACTIVE);
            zhineActor->mCoordinates = getBoundingPoint();
        }
    }

    //0x80079B44
    void init()
    {
        ZhineFile *gessoZhineFile = (ZhineFile *)getResource__10JKRArchiveFPCc(getVolume__13JKRFileLoaderFPCc("scene"), "/bgeso/zhine.data");

        JDrama::TActor *zhineActor = &this->mBossInfo.mSpineEnemy.mLiveActor.mTakeActor.mHitActor.mActor;
        this->mBossInfo.mGoopLevel = 0xE6;

        if (gessoZhineFile)
        {

            u32 *newVTable = (u32 *)malloc(0x120, 32);
            memcpy(newVTable, zhineActor->vTable, 0x114);
            newVTable[0xD0 / 4] = (u32)gessoZhineFile + (u32)gessoZhineFile->mCodeBlock[0]; //Replace move vtable entry
            *(u32 *)0x803B2A94 = (u32)gessoZhineFile + (u32)gessoZhineFile->mCodeBlock[1];  //Replace eye damage vtable entry

            this->setBoundingPoint(&gessoZhineFile->ZhineBinData.mBoundingPoint);
            this->setBoundingRadius(gessoZhineFile->ZhineBinData.mBoundingAreaRadius);
            this->setShockRadius(gessoZhineFile->ZhineBinData.mShockRadius);
            this->setStampRadius(gessoZhineFile->ZhineBinData.mStampRadius);
            this->setMarioDistance(gessoZhineFile->ZhineBinData.mDistanceFromMario);
            this->setSpeedMultiplier(gessoZhineFile->ZhineBinData.mSpeedMultiplier);
            this->setAccelerationRate(gessoZhineFile->ZhineBinData.mAccelerationRate);
            this->setMaxSpeed(gessoZhineFile->ZhineBinData.mMaxSpeed);
            this->setFramesToCleanOnce(gessoZhineFile->ZhineBinData.mFramesToCleanOnce);
            this->setPoundingTimer(gessoZhineFile->ZhineBinData.mPoundingTimerMax);
            this->setShockingTimer(gessoZhineFile->ZhineBinData.mShockingTimerMax);
            this->setRollingTimer(gessoZhineFile->ZhineBinData.mRollingTimerMax);
            this->setGoopingTimer(gessoZhineFile->ZhineBinData.mGoopingTimerMax);
            this->setPoundingTimerMax(gessoZhineFile->ZhineBinData.mPoundingTimerMax);
            this->setShockingTimerMax(gessoZhineFile->ZhineBinData.mShockingTimerMax);
            this->setRollingTimerMax(gessoZhineFile->ZhineBinData.mRollingTimerMax);
            this->setGoopingTimerMax(gessoZhineFile->ZhineBinData.mGoopingTimerMax);
            this->setRisingRate(gessoZhineFile->ZhineBinData.mRisingRate);
            this->setMaxPoundingHeight(gessoZhineFile->ZhineBinData.mMaxPoundingHeight);

            zhineActor->vTable = newVTable;
            *(float *)0x8041014C = gessoZhineFile->ZhineBinData.mBoundingAreaRadius;
            *(float *)0x80410150 *= gessoZhineFile->ZhineBinData.mSpeedMultiplier;

            this->mBossInfo.mGoopLevel = gessoZhineFile->ZhineBinData.mGoopLevel;
            this->setIsDarkZhine(true);
        }
        else
        {
            this->setIsDarkZhine(false);
        }
        initAnmSound__10TLiveActorFv(this);
        return;
    }

    TDarkZhine *destroy()
    {
        //use r6 and up
        *(u32 *)0x803B2A94 = 0x80074E54; //restore eye damage vtable entry
        *(float *)0x8041014C = 800;
        *(float *)0x80410150 = 3000;
        return this;
    }
};

//0x80005004
u32 cleanZhine(u32 *gpNerveBGEye, TSpineBase<TLiveActor> *gpSpineBase)
{
    TDarkZhine *gpDarkZhine = (TDarkZhine *)gpSpineBase->mTarget;
    if (gpDarkZhine->getCleaningTimer() < gpDarkZhine->getFramesToCleanOnce())
    {
        gpDarkZhine->setCleaningTimer(gpDarkZhine->getCleaningTimer() + 1);
        return 0;
    }
    else
    {
        gpDarkZhine->setCleaningTimer(0);
        return execute__17TNerveBGEyeDamageCFP24TSpineBase_1(gpNerveBGEye, gpSpineBase);
    }
}

//0x800764CC
void canUtilizeTentacles(u32 *TBGTentacle, u32 *unk1, u32 *JDramaGraphics, TDarkZhine *thisZhine)
{
    //mr r6, r31
    if (thisZhine->getIsDarkZhine() == false)
    {
        testPerform__Q26JDrama8TViewObjFUlPQ26JDrama9TGraphics(TBGTentacle, unk1, JDramaGraphics);
    }
}

//0x80005000
void control(TDarkZhine *thisZhine)
{
    TMario *gpMario = (TMario *)*(u32 *)TMarioInstance;
    thisZhine->update(gpMario);
}

//0x800FFFAC = remove tentacles BLR, 0x800764CC perform tentacles?

//0x802A9D54 = TBossGesso Class Size
