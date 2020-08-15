#include "includes/eclipse.hxx"

void startStreamedBGM(u32 musicID, bool loopMusic) {
    char buffer[0x20];
    u32 handle = 0x803FDB7C;

    sprintf(buffer, "/AudioRes/Streams/Music/%d.adp", (musicID & 0x3FF));

    if (DVDOpen(buffer, handle) == false) return;

    DVDPrepareStreamAsync(handle, 0, 0, 0x803184E4);
    stopBGM__5MSBgmFUlUl(*(u32*)0x8040E1F0, 32);

    if (loopMusic == false) DVDStopStreamAtEndAsync(0x8058943C, 0);
}

void startStreamedSFX(u32 sfxID) {
    char buffer[0x20];
    u32 handle = 0x803FDB7C;

    sprintf(buffer, "/AudioRes/Streams/Music/%d.adp", (sfxID & 0x3FF));

    if (DVDOpen(buffer, handle) == false) return;

    DVDPrepareStreamAsync(handle, 0, 0, 0x803184E4);
    DVDStopStreamAtEndAsync(0x8058943C, 0);
}

void streamAudio(u32 ID, u8 type, bool loopAudio) {
    if (ID & 0x400) {
        if (type == 0) {
            startStreamedBGM(ID, loopAudio);
        } else if (type == 1) {
            startStreamedSFX(ID);
        }
    }
}

//0x80016ABC
void initMusic() {
    if (!gInfo.mFile) return;
    if (!gInfo.mIsAudioStreaming) {
        startStreamedBGM(gInfo.mFile->Music.mMusicID, true);
        gInfo.mIsAudioStreaming = true;
    }
}

//0x80016948
void stopMusic() {
    if (gInfo.mIsAudioStreaming) {
        DVDCancelStreamAsync(0x8058943C, 0);
        gInfo.mIsAudioStreaming = false;
    }
}