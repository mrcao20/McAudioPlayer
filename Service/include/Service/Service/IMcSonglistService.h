#pragma once

#include "IMcAcquireModel.h"
#include "IMcAcquireMusic.h"
#include "IMcMusicForSongSheet.h"

class IMcSonglistService : public IMcAcquireModel
        , public IMcAcquireMusic 
        , public IMcMusicForSongSheet {
    MC_TYPELIST(IMcAcquireModel, IMcAcquireMusic, IMcMusicForSongSheet)
public:
    ~IMcSonglistService() noexcept override = default;
    
    virtual void reloadMusic(int songSheetId) noexcept = 0;
    virtual void addNewLocalMusics(int songSheetId, const QList<QUrl> &filePaths) noexcept = 0;
};

MC_DECL_METATYPE(IMcSonglistService)
