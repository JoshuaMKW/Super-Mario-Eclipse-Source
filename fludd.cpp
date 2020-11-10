#include "includes/eclipse.hxx"

//0x8026A164
TWaterGun::NOZZLETYPE changeNozzleIfSet(TWaterGun* gpFludd, TWaterGun::NOZZLETYPE nozzle, bool normalize) {
    if (gInfo.mCharacterFile && gpFludd->mMario->mCustomInfo->mParams->Attributes.mCanUseFludd) {
        if (!gInfo.mCharacterFile->Attributes.FluddAttrs.mCanUseNozzle[(u8)nozzle]) {
            nozzle = gpFludd->mCurrentNozzle;
        }
    } 
    return nozzle; //return gpFludd and normalize too
    //mflr r0
}

//0x8014206C
bool hasWaterCardOpen(TGCConsole2* gcConsole) {
    //mr r3, r31
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;

    if (gpMario->mYoshi->mState != TYoshi::STATE::MOUNTED) {
        gpMario->mAttributes.mHasFludd = gpMario->mCustomInfo->mParams->Attributes.mCanUseFludd;
    } else {
        gpMario->mAttributes.mHasFludd = true;
    }

    if (gpMario->mYoshi->mState != TYoshi::STATE::MOUNTED &&
        gpMario->mAttributes.mHasFludd == false &&
        gcConsole->mWaterCardFalling == false &&
        gcConsole->mIsWaterCard == true) {

        startDisappearTank__11TGCConsole2Fv(gcConsole);
    }


    return gcConsole->mIsWaterCard;
    //mr r0, r3
}

//0x80283058
bool canCollectFluddItem(TMario* gpMario) {
    return (onYoshi__6TMarioCFv(gpMario) || !gpMario->mCustomInfo->mParams->Attributes.mCanUseFludd);
}

//0x8024E710
/*
__push_stack r30, 0x20, TRUE
mr r4, r30
__call r0, 0x800050E0
__pop_stack r30, 0x20, TRUE
*/

//0x800050E0
void sprayGoopMap(TPollutionManager* gpPollutionManager, float x, float y, float z, float r, TMario *gpMario) {
    MarioParamsFile* localfile = gpMario->mCustomInfo->mParams;
    if (localfile && localfile->Attributes.FluddAttrs.mCleaningType != localfile->NONE) {
        if (localfile->Attributes.FluddAttrs.mCleaningType == localfile->CLEAN) {
            clean__17TPollutionManagerFffff(gpPollutionManager, x, y, z, r);
        } else if (localfile->Attributes.FluddAttrs.mCleaningType == localfile->GOOP) {
            stamp__17TPollutionManagerFUsffff(gpPollutionManager, 1, x, y, z, r);
        }
    }
}

//0x800FED3C
bool canCleanSeals(TWaterManager* gpWaterManager) {
    MarioParamsFile* localfile = gInfo.mCharacterFile;
    return (gpWaterManager->mWaterCardType != 0 || (localfile && localfile->Attributes.FluddAttrs.mCanCleanSeals));
}

//0x8024D560
void bindFluddtojoint(TWaterGun* gpFludd, u32* joint) {
    MarioParamsFile* localfile = gpFludd->mMario->mCustomInfo->mParams;
    u32* jointlist;
    u32 index;

    if (localfile) {
        index = localfile->Attributes.FluddAttrs.mBindToJointID[(u8)gpFludd->mCurrentNozzle] * 0x30;
        jointlist = gpFludd->mMario->mModelData->mJointList;
        joint = (u32*)(jointlist[0x58 / 4] + index);
    }
    setBaseTRMtx__9TWaterGunFPA4_f(gpFludd, joint);
}

//0x800FED40 -> 2C030000