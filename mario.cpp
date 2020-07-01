#include "includes/eclipse.hxx"

//0x8029D7FC  **INITIALIZE 4 MARIOS**
/*
lis r12, gInfo@h
ori r12, r12, gInfo@l + 0x3C
lwz r11, 0 (r12)
cmpwi r11, 0
bne- no_init
li r11, 0
stw r29, -0x60D8 (r13)
stw r29, -0x60B8 (r13)
stb r11, 0x10 (r12)
no_init:
lbz r11, 0x10 (r12)
addi r10, r11, 1
slwi r11, r11, 2
stwx r29, r12, r11
lbz r9, 0x11 (r12)
cmpw r10, r9
blt skipreset
li r10, 0
skipreset:
stb r10, 0x10 (r12)
mr r3, r29
*/

//kWrite32(0x8029D800, 0x4180FFE4);
//kWrite32(0x8029D804, 0x60000000);

//0x80276AB8  **INITVALUES 4 MARIOS**
/*

stb r3, 0x535 (r30)
sth r0, 0x556 (r30)

lis r12, gInfo@h
ori r12, r12, gInfo@l + 0x3C
lwz r11, 0 (r12)
cmpw r11, r30
bne+ isMultiMario
li r11, 0
stb r11, 0x10 (r12)
isMultiMario:
lbz r11, 0x10 (r12)
addi r10, r11, 1
slwi r11, r11, 2
lwzx r30, r12, r11
mr r3, r30
lbz r9, 0x11 (r12)
cmpw r10, r9
blt skipreset
li r10, 0
skipreset:
stb r10, 0x10 (r12)
*/

//kWrite32(0x80276ABC, 0x4180FC10);

//0x80276C90 LOAD VALUES 4 MARIOS
/*

mtlr r12
blrl

lis r12, gInfo@h
ori r12, r12, gInfo@l + 0x3C
lwz r11, 0 (r12)
cmpw r11, r31
bne+ isMultiMario
li r11, 0
stb r11, 0x10 (r12)
isMultiMario:
lbz r11, 0x10 (r12)
addi r10, r11, 1
slwi r11, r11, 2
lwzx r3, r12, r11
lbz r9, 0x11 (r12)
cmpw r10, r9
blt skipreset

li r10, 0
b pass

skipreset:
stb r10, 0x10 (r12)
lwz r12, 0 (r30)
lwz r12, 0x10 (r30)
mtlr r12
blrl

pass:

0x8
*/

//kWrite32(0x80276C94, 0x4180FF58);

//0x80
/*void loopAndUpdatePlayers() {
    for (u32 i = 0; i < gInfo.PlayerData.mMaxPlayerCount; ++i) {
        if (gInfo.PlayerData.mMario == nullptr) {
            continue;
        }
        if (gInfo.PlayerData.mIsActive[i] == false) {
            if (gInfo.PlayerData.mMario[i]->mController->Buttons.mSButton) {
                gInfo.PlayerData.mIsActive[i] = true;
            }
        } else {
            u8 prevPlayerID = gInfo.PlayerData.mCurPlayerID[i];

            if (gInfo.PlayerData.mMario[i]->mController->Buttons.mDPadRight == false &&
                gInfo.PlayerData.mMario[i]->mController->Buttons.mDPadLeft == false) {
                gInfo.PlayerData.mCurPlayerTimer[i] = 0;
            }
            if (gInfo.PlayerData.mMario[i]->mController->Buttons.mDPadRight == true) {
                if (gInfo.PlayerData.mCurPlayerTimer[i] == 0) {
                    gInfo.PlayerData.mCurPlayerID[i] += 1;
                    if (gInfo.PlayerData.mCurPlayerID[i] > 8) {
                        gInfo.PlayerData.mCurPlayerID[i] = 0;
                    }
                    gInfo.PlayerData.mCurPlayerTimer[i] = gInfo.PlayerData.mMaxPlayerTimer;
                } else {
                    gInfo.PlayerData.mCurPlayerTimer[i] -= 1;
                }
            } else if (gInfo.PlayerData.mMario[i]->mController->Buttons.mDPadLeft == true) {
                if (gInfo.PlayerData.mCurPlayerTimer[i] == 0) {
                    gInfo.PlayerData.mCurPlayerID[i] -= 1;
                    if (gInfo.PlayerData.mCurPlayerID[i] < 0) {
                        gInfo.PlayerData.mCurPlayerID[i] = 8;
                    }
                    gInfo.PlayerData.mCurPlayerTimer[i] = gInfo.PlayerData.mMaxPlayerTimer;
                } else {
                    gInfo.PlayerData.mCurPlayerTimer[i] -= 1;
                }
            }

            if (gInfo.PlayerData.mCurPlayerID[i] != prevPlayerID) {
                initModel__6TMarioFv(gInfo.PlayerData.mMario[i]);
                initMirrorModel__6TMarioFv(gInfo.PlayerData.mMario[i]);
            }
            
            *(u32*)TMarioInstance = (u32)gInfo.PlayerData.mMario[i];
            SMS_SetMarioAccessParams__Fv();
        }
    }
}*/

//0x8024D2C4
TMario* updateMario(TMario* gpMario) {
    u32 i = 0;
    u8 prevPlayerID = gInfo.PlayerData.mCurPlayerID[i];

    if (gpMario->mController->Buttons.mDPadRight == false &&
        gpMario->mController->Buttons.mDPadLeft == false) {
        gInfo.PlayerData.mCurPlayerTimer[i] = 0;
    }
    if (gpMario->mController->Buttons.mDPadRight == true) {
        if (gInfo.PlayerData.mCurPlayerTimer[i] == 0) {
            gInfo.PlayerData.mCurPlayerID[i] += 1;
            if (gInfo.PlayerData.mCurPlayerID[i] > 8) {
                gInfo.PlayerData.mCurPlayerID[i] = 0;
            }
            gInfo.PlayerData.mCurPlayerTimer[i] = gInfo.PlayerData.mMaxPlayerTimer;
        } else {
            gInfo.PlayerData.mCurPlayerTimer[i] -= 1;
        }
    } else if (gpMario->mController->Buttons.mDPadLeft == true) {
        if (gInfo.PlayerData.mCurPlayerTimer[i] == 0) {
            gInfo.PlayerData.mCurPlayerID[i] -= 1;
            if (gInfo.PlayerData.mCurPlayerID[i] < 0) {
                gInfo.PlayerData.mCurPlayerID[i] = 8;
            }
            gInfo.PlayerData.mCurPlayerTimer[i] = gInfo.PlayerData.mMaxPlayerTimer;
        } else {
            gInfo.PlayerData.mCurPlayerTimer[i] -= 1;
        }
    }

    if (gInfo.PlayerData.mCurPlayerID[i] != prevPlayerID) {
        u32* marioVolumeData = (u32*)getVolume__13JKRFileLoaderFPCc("mario");
        u32* marioDataArray = (u32*)*(u32*)ARCBufferMario;

        if (marioDataArray[gInfo.PlayerData.mCurPlayerID[i]]) {
            __dt__13JKRMemArchiveFv(marioVolumeData);
            __ct__13JKRMemArchiveFPvUl15JKRMemBreakFlag(marioVolumeData, marioDataArray[i], 0, 0);

            initModel__6TMarioFv(gpMario);
            initMirrorModel__6TMarioFv(gpMario);
        }
    }
    asm("lhz 0, 0x114 (3)");
    return gpMario;
}