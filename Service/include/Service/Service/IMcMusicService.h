#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McMusic);

class IMcMusicService {
    MC_TYPELIST()
public:
    virtual ~IMcMusicService() noexcept = default;
    
    virtual void acquireMusicUrl(McMusicConstPtrRef music) noexcept = 0;
};

MC_DECL_METATYPE(IMcMusicService)
