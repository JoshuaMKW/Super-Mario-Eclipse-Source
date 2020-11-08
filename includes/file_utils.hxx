#pragma once

#include "eclipse.hxx"

const char *getStageName(TApplication *gpApplication)
{
    AreaEpisodeArray *AreaPathArray = gpApplication->mStringPaths;

    if (!AreaPathArray)
        return nullptr;

    u32 *AreaArrayStart = AreaPathArray->startArray;

    if (!AreaArrayStart || (((u32)AreaPathArray->endArray - (u32)AreaArrayStart) >> 2) < gpApplication->mCurrentScene.mAreaID)
        return nullptr;

    AreaEpisodeArray *StagePathArray = (AreaEpisodeArray *)AreaArrayStart[gpApplication->mCurrentScene.mAreaID];
    u32 *StageArrayStart = (u32 *)StagePathArray->startArray;

    if (!StageArrayStart || (((u32)StagePathArray->endArray - (u32)StageArrayStart) >> 4) < gpApplication->mCurrentScene.mEpisodeID)
        return nullptr;

    return (const char *)(StageArrayStart[(gpApplication->mCurrentScene.mEpisodeID << 2) + (0xC / 4)]);
}