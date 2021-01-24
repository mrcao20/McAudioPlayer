#pragma once

#include "../IMcPlaylistDao.h"

MC_FORWARD_DECL_PRIVATE_DATA(McPlaylistDao);

class McPlaylistDao : public QObject, public IMcPlaylistDao {
    Q_OBJECT
    MC_DECL_INIT(McPlaylistDao)
    MC_TYPELIST(QObject, IMcPlaylistDao)
    MC_COMPONENT
    MC_BEANNAME("playlistDao")
public:
    Q_INVOKABLE McPlaylistDao() noexcept;
    ~McPlaylistDao() noexcept override;
    
    QList<McMusicPtr> reloadMusic() noexcept override;
    bool deleteAll() noexcept override;
    void setMusics(const QList<McMusicPtr> &musics, int songSheetId) noexcept override;

private:
    Q_INVOKABLE QList<McMusicPtr> reloadMusic_helper() noexcept;
    Q_INVOKABLE bool deleteAll_helper() noexcept;
    Q_INVOKABLE void setMusics_helper(const QList<McMusicPtr> &musics, int songSheetId) noexcept;

private:
    MC_DECL_PRIVATE(McPlaylistDao)
};

MC_DECL_METATYPE(McPlaylistDao)
