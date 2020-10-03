#pragma once

#include "IMcMusicModel.h"

class IMcNetworkMusicModel : public IMcMusicModel {
    MC_DEFINE_TYPELIST(MC_DECL_TYPELIST(IMcMusicModel))
public:
    virtual ~IMcNetworkMusicModel() noexcept = default;
};

MC_DECL_METATYPE(IMcNetworkMusicModel)
