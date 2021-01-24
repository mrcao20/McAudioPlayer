#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McMusic);

class IMcMusicDao {
    MC_TYPELIST()
public:
    virtual ~IMcMusicDao() noexcept = default;
    
    virtual void getMusicUrl(McMusicConstPtrRef music) noexcept = 0;
    virtual void getMusicDetail(McMusicConstPtrRef music) noexcept = 0;
    virtual void updateMusicUrl(McMusicConstPtrRef music) noexcept = 0;
};

MC_DECL_METATYPE(IMcMusicDao)
