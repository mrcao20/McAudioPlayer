#pragma once

#include "IMcMusicModel.h"

class IMcSonglistModel : public IMcMusicModel {
    MC_TYPELIST(IMcMusicModel)
public:
    virtual ~IMcSonglistModel() noexcept = default;
};

MC_DECL_METATYPE(IMcSonglistModel)
