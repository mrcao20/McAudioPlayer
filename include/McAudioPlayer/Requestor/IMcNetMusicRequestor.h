#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McMusic);

class IMcNetMusicRequestor {
    MC_DEFINE_TYPELIST()
public:
    virtual ~IMcNetMusicRequestor() noexcept = default;
    
    virtual QString getMusicUrl(McMusicConstPtrRef music) noexcept = 0;
    virtual QList<McMusicPtr> getNetworkMusics(const QString &musicSrc, const QString &keyword) noexcept = 0;
    virtual QList<McMusicPtr> getLastPageMusic() noexcept = 0;
    virtual QList<McMusicPtr> getNextPageMusic() noexcept = 0;
};

MC_DECL_METATYPE(IMcNetMusicRequestor)
