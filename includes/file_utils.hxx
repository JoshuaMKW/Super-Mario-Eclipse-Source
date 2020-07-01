#include "eclipse.hxx"

const char* getStageName(TApplication* gpApplication) {

    AreaEpisodeArray* AreaPathArray = gpApplication->mStringPaths;
    u32* AreaArrayStart = AreaPathArray->startArray;

    if (!AreaArrayStart || (((u32)AreaPathArray->endArray - (u32)AreaArrayStart) >> 2) < gpApplication->mAreaID)
        return nullptr;

    AreaEpisodeArray* StagePathArray = (AreaEpisodeArray*)AreaArrayStart[gpApplication->mAreaID];
    u32* StageArrayStart = (u32*)StagePathArray->startArray;

    if (!StageArrayStart || (((u32)StagePathArray->endArray - (u32)StageArrayStart) >> 4) < gpApplication->mEpisodeID)
        return nullptr;

    return (const char*)(StageArrayStart[(gpApplication->mEpisodeID << 2) + (0xC / 4)]);
}

SMEFile* loadFile(const char* stringPath) {
    u32 handle[0x3C / 4];
    char buffer[sizeof(SMEFile)+31];
    SMEFile *sme_file = (SMEFile *)(((u32)(buffer) + 31) & ~(31));

    for (u32 i = 0; DVDGetDriveStatus() != DVD_STATE_END; ++i) {
        if (i > 100000) {
            return nullptr;
        }
    }
    
    if (DVDOpen(stringPath, handle) == false)
        return nullptr;

    if (DVDReadPrio(handle, sme_file, 32, 0, 2) < DVD_ERROR_OK) {
        DVDClose(handle);
        return nullptr;
    }

    u32* loadAddress;
    if (sme_file->FileHeader.mLoadAddress == nullptr) {
        loadAddress = (u32*)(malloc(((sizeof(SMEFile) + 31) & ~(31)) + 32) + 31 & ~(31)); //Create an allocation
    } else {
        loadAddress = sme_file->FileHeader.mLoadAddress;
    }

    if (DVDReadPrio(handle, loadAddress, sme_file->FileHeader.mFileSize, 0, 2) < DVD_ERROR_OK) {
        DVDClose(handle);
        return nullptr;
    }
    DVDClose(handle);
    return (SMEFile*)loadAddress;
}

char* parseExtension(char* filepath, const char* stage, bool generalize = false) {
    u32 index = 0;
    while (filepath[index] != NULL) {
        ++index;
    }
    
    for (u32 i = 0; stage[i] != NULL && stage[i] != '.'; ++i) {
        if (generalize == true && (stage[i] >= '0' && stage[i] <= '9')) {
            filepath[index] = '+';
            filepath[index + 1] = '.';
            filepath[index + 2] = 's';
            filepath[index + 3] = 'm';
            filepath[index + 4] = 'e';
            filepath[index + 5] = NULL;
            return filepath;
        }
        filepath[index] = stage[i];
        ++index;
    }
    
    filepath[index] = '.';
    filepath[index + 1] = 's';
    filepath[index + 2] = 'm';
    filepath[index + 3] = 'e';
    filepath[index + 4] = NULL;
    return filepath;
}