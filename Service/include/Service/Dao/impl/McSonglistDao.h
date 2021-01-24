#pragma once

#include "../IMcSonglistDao.h"

MC_FORWARD_DECL_PRIVATE_DATA(McSonglistDao);

class McSonglistDao : public QObject, public IMcSonglistDao {
    Q_OBJECT
    MC_DECL_INIT(McSonglistDao)
    MC_TYPELIST(QObject, IMcSonglistDao)
    MC_COMPONENT
    MC_BEANNAME("songlistDao")
public:
    Q_INVOKABLE McSonglistDao() noexcept;
    ~McSonglistDao() noexcept override;
    
    QList<McMusicPtr> reloadMusic(int songSheetId) noexcept override;
    bool isExists(int songSheetId, McMusicConstPtrRef music) noexcept override;
    void addToSongSheet(int songSheetId, McMusicConstPtrRef music) noexcept override;
    int getSonglistId(int songSheetId, McMusicConstPtrRef music) noexcept override;
    void removeSonglist(int id) noexcept override;
    int getMaxMusicId() noexcept override;

private:
    Q_INVOKABLE QList<McMusicPtr> reloadMusic_helper(int songSheetId) noexcept;
    Q_INVOKABLE bool isExists_helper(int songSheetId, const McMusicPtr &music) noexcept;
    Q_INVOKABLE void addToSongSheet_helper(int songSheetId, const McMusicPtr &music) noexcept;
    Q_INVOKABLE int getSonglistId_helper(int songSheetId, const McMusicPtr &music) noexcept;
    Q_INVOKABLE void removeSonglist_helper(int id) noexcept;
    Q_INVOKABLE int getMaxMusicId_helper() noexcept;

private:
    int getMaxSonglistId() const noexcept;
    
private:
    MC_DECL_PRIVATE(McSonglistDao)
};

MC_DECL_METATYPE(McSonglistDao)
