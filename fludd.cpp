#include "includes/eclipse.hxx"

//0x8026A164 - Conditional Fludd Usage
/*
lwz r6, 0x8 (r3) #TMario
lbz r0, 0x4298 (r6) #CanUseFludd
cmpwi r0, 0
bne+ usable
lwz r0, 0x118 (r6)
rlwinm r0, r0, 0, 17, 15
stw r0, 0x118 (r6)
lwz r6, 0x1CDC (r3)
lwz r6, 0x10 (r6)
lwz r6, 0x4 (r6)
lwz r6, 0x4 (r6)
lhz r0, 0x4 (r6)
rlwinm r0, r0, 0, 
mflr r0
*/

//0x8014206C
bool hasWaterCardOpen(TGCConsole2* gcConsole) {
    //mr r3, r31
    TMario* gpMario = (TMario*)*(u32*)TMarioInstance;

    if (gpMario->mAttributes.mHasFludd == false && gcConsole->mWaterCardFalling == false)
        startDisappearTank__11TGCConsole2Fv(gcConsole);

    return gcConsole->mIsWaterCard;
    //mr r0, r3
}