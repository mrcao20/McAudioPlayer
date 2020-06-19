#pragma once

#include "IMcMusicModel.h"

class IMcPlaylistModel : public IMcMusicModel {
    MC_DEFINE_TYPELIST(MC_DECL_TYPELIST(IMcMusicModel))
public:
    virtual ~IMcPlaylistModel() noexcept = default;
};

MC_DECL_METATYPE(IMcPlaylistModel)
