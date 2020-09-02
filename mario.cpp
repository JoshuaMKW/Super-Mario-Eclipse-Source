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

//0x8024E02C
void manageExtraJumps(TMario* gpMario) {
    if ((gpMario->mState & STATE_AIRBORN) == false || (gpMario->mState & 0x800000) || gpMario->mYoshi->mState == MOUNTED) {
        gpMario->mCurJump = 1;
    } else {
        if (gpMario->mController->FrameButtons.mAButton &
            gpMario->mCurJump < gpMario->mMaxJumps &
            gpMario->mState != STATE_WALLSLIDE) {
            if ((gpMario->mMaxJumps - gpMario->mCurJump) == 1) {
                changePlayerJumping__6TMarioFUlUl(gpMario, STATE_TRIPLE_J, 0);
            } else if ((gpMario->mState - STATE_JUMP) > 1) {
                changePlayerJumping__6TMarioFUlUl(gpMario, STATE_JUMP, 0);
            } else {
                changePlayerJumping__6TMarioFUlUl(gpMario, gpMario->mState ^ 1, 0);
            }
            gpMario->mCurJump += 1;
        }
    }
    stateMachine__6TMarioFv(gpMario);
}

//0x802546E4, 0x802546B0, 0x80254540
/*
stwu sp, -0x10 (sp)
stw r31, 0x8 (sp)
mr r31, r4
lis r3, TMario@ha
lwz r3, TMario@l (r3)
cmpw r30, r3
bne notMario
mr r3, r30
fmr f3, f0
lis r0, 0x8000
ori r0, r0, 0x4A78
mtctr r0
bctrl
notMario:
mr r3, r30
mr r4, r31
fmr f0, f1
lwz r31, 0x8 (sp)
addi sp, sp, 0x10
*/

//0x80004A78
float calcJumpPower(TMario* gpMario, float factor, float curYVelocity, float jumpPower) {
    jumpPower *= gpMario->mBaseJumpMulti;
    if (gpMario->mState & STATE_AIRBORN) {
        jumpPower *= powf(gpMario->mExJumpMulti, (float)gpMario->mCurJump);
        gpMario->mForwardSpeed *= gpMario->mExJumpFSpeedMulti;
    }
    return (curYVelocity * factor) + jumpPower;
}

//0x8025B8C8 - fSpeed Limit Multiplier - ground
/*
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r31
bne- notMario
lfs f2, 0x42A4 (r31)
fmuls f31, f31, f2
notMario:
lfs f2, 0xB0 (r31)
*/

//0x8025B8F8 - fSpeed Multiplier - ground
/*
lfs f1, 0xEF4 (r31)
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r31
bne- notMario
lfs f0, 0x42A4 (r31)
fdivs f1, f1, f0
notMario:
*/

//0x8024CC58 - fSpeed Limit Multiplier - jump
/*
lfs f0, -0x1048 (rtoc)
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r31
bne- notMario
lfs f5, 0x42A4 (r31)
fmuls f0, f0, f5
notMario:
*/

//0x8024CC2C - fSpeed Multiplier - jump
/*
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r31
bne- notMario
lfs f5, 0x42A4 (r31)
fmuls f1, f1, f5
notMario:
fmadds f0, f1, f2, f0
*/

//0x80272FF0 - fSpeed Multplier - swim
/*
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r31
bne- notMario
lfs f5, 0x42A4 (r31)
fmuls f2, f2, f5
notMario:
fmadds f0, f2, f1, f0
*/

//0x8025C3F4 - fSpeed Multplier - slide
/*
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r30
bne- notMario
lfs f5, 0x42A4 (r30)
fdivs f2, f2, f5
notMario:
fmul f0, f2, f0
*/

//0x8025BC44 - fSpeed Cap Multiplier
/*
lfs f1, 0x5A0 (r31)
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r31
bne- notMario
lfs f2, 0x42A4 (r31)
fmuls f1, f1, f2
notMario:
*/

//0x8024AE80 - fSpeed Multplier - hover
/*
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r30
bne- notMario
lfs f5, 0x42A4 (r30)
fmuls f1, f1, f5
notMario:
fmadds f0, f2, f1, f0
*/

//0x802558B4 - fSpeed Multplier - addvelocity
/*
lfs f0, -0xF1C (rtoc)
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r3
bne- notMario
lfs f2, 0x42A4 (r3)
fmuls f1, f1, f2
notMario:
*/

//0x80259368 - fSpeed Multplier - hover
/*
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r31
bne- notMario
lfs f5, 0x42A4 (r31)
fmuls f1, f1, f5
notMario:
fmadds f0, f2, f1, f0
*/

//0x8024C7C4 - fSpeed Wall Bonk Air Cap Multiplier
/*
lfs f0, 0x8E8 (r28)
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r28
bne- notMario
lfs f2, 0x42A4 (r28)
fmuls f0, f0, f2
notMario:
*/

//0x8025B14C - fSpeed Wall Bonk Ground Cap Multiplier
/*
lfs f0, 0x8E8 (r28)
lis r11, TMario@ha
lwz r11, TMario@l (r11)
cmpw r11, r31
bne- notMario
lfs f2, 0x42A4 (r31)
fmuls f0, f0, f2
notMario:
*/
