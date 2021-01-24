#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McMusic);

class IMcMusicApi {
    MC_TYPELIST()
public:
    virtual ~IMcMusicApi() noexcept = default;
    
    virtual QString getMusicUrl(McMusicConstPtrRef music) noexcept = 0;
    virtual QString getDownloadUrl(McMusicConstPtrRef music) noexcept = 0;
    virtual QList<McMusicPtr> searchSong(const QString &songName, int limit = 20, int offset = 0) noexcept = 0;
};

MC_DECL_METATYPE(IMcMusicApi)
