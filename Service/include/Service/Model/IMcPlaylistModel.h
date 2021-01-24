#pragma once

#include "IMcMusicModel.h"

class IMcPlaylistModel : public IMcMusicModel {
    MC_TYPELIST(IMcMusicModel)
public:
    virtual ~IMcPlaylistModel() noexcept = default;
};

MC_DECL_METATYPE(IMcPlaylistModel)
