#pragma once

#include "../IMcPlaylistDao.h"

MC_FORWARD_DECL_PRIVATE_DATA(McPlaylistDao);

class McPlaylistDao : public QObject, public IMcPlaylistDao {
    Q_OBJECT
    MC_DECL_INIT(McPlaylistDao)
    MC_DEFINE_TYPELIST(QObject, MC_DECL_TYPELIST(IMcPlaylistDao))
    Q_CLASSINFO(MC_BEANNAME, "playlistDao")
public:
    Q_INVOKABLE McPlaylistDao() noexcept;
    ~McPlaylistDao() noexcept override;
    
    QList<McMusicPtr> reloadMusic() noexcept override;
    bool deleteAll() noexcept override;
    void setMusics(const QList<McMusicPtr> &musics, int songSheetId) noexcept override;
    
private:
    MC_DECL_PRIVATE(McPlaylistDao)
};

MC_DECL_METATYPE(McPlaylistDao)
