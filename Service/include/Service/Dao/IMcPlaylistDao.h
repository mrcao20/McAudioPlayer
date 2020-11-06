#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McMusic);

class IMcPlaylistDao {
    MC_DEFINE_TYPELIST()
public:
    virtual ~IMcPlaylistDao() noexcept = default;
    
    virtual QList<McMusicPtr> reloadMusic() noexcept = 0;
    virtual bool deleteAll() noexcept = 0;
    virtual void setMusics(const QList<McMusicPtr> &musics, int songSheetId) noexcept = 0;
};

MC_DECL_METATYPE(IMcPlaylistDao)
