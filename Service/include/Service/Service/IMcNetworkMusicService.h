#pragma once

#include "IMcAcquireModel.h"
#include "IMcAcquireMusic.h"
#include "IMcMusicForSongSheet.h"

class IMcNetworkMusicService : public IMcAcquireModel 
        , public IMcAcquireMusic 
        , public IMcMusicForSongSheet {
    MC_TYPELIST(IMcAcquireModel, IMcAcquireMusic, IMcMusicForSongSheet)
public:
    using IMcMusicForSongSheet::addToSongSheet;
    
    ~IMcNetworkMusicService() noexcept override = default;
    
    virtual void addToSongSheet(int songSheetId, const QList<McMusicPtr> &musics) noexcept = 0;
    virtual void getNetworkMusics(const QString &musicSrc, const QString &keyword) noexcept = 0;
    virtual void getLastPageMusic() noexcept = 0;
    virtual void getNextPageMusic() noexcept = 0;
    virtual void clearModel() noexcept = 0;
};

MC_DECL_METATYPE(IMcNetworkMusicService)
