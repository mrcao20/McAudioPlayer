#pragma once

#include "IMcAcquireModel.h"
#include "IMcAcquireMusic.h"
#include "IMcMusicForSongSheet.h"

class IMcSonglistService : public IMcAcquireModel
        , public IMcAcquireMusic 
        , public IMcMusicForSongSheet {
    
    MC_DEFINE_TYPELIST(MC_DECL_TYPELIST(IMcAcquireModel)
                       , MC_DECL_TYPELIST(IMcAcquireMusic)
                       , MC_DECL_TYPELIST(IMcMusicForSongSheet))
public:
    ~IMcSonglistService() noexcept override = default;
    
    virtual void reloadMusic(int songSheetId) noexcept = 0;
    virtual void addNewLocalMusics(int songSheetId, const QList<QUrl> &filePaths) noexcept = 0;
};

MC_DECL_METATYPE(IMcSonglistService)
