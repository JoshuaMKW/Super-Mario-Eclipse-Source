#include "eclipse.hxx"

bool isGreenYoshi(TYoshi* gpYoshi) {
    return gpYoshi->mType == GREEN_YOSHI;
}

bool isGreenYoshiMounted(TYoshi* gpYoshi) {
    return isGreenYoshi(gpYoshi) && gpYoshi->mState == MOUNTED;
}

bool isGreenYoshiAscendingWater(TMario* gpMario) {
    if (gpMario->mAttributes.mIsWater == false ||
        gpMario->mController->Buttons.mAButton == false ||
        isGreenYoshiMounted(gpMario->mYoshi) == false) {
        return false;
    } else {
        return true;
    }
}