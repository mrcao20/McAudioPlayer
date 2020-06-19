#pragma once

#include "IMcAcquireModel.h"

MC_FORWARD_DECL_CLASS(McMusic);

class IMcPlaylistService : public IMcAcquireModel {
    MC_DEFINE_TYPELIST(MC_DECL_TYPELIST(IMcAcquireModel))
public:
    ~IMcPlaylistService() noexcept override = default;
    
    virtual void loadPlaylist() noexcept = 0;
    virtual void setMusics(const QList<McMusicPtr> &musics, int songSheetId) noexcept = 0;
    virtual McMusicPtr getMusic(int index) noexcept = 0;
};

MC_DECL_METATYPE(IMcPlaylistService)
