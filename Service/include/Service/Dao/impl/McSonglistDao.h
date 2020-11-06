#pragma once

#include "../IMcSonglistDao.h"

MC_FORWARD_DECL_PRIVATE_DATA(McSonglistDao);

class McSonglistDao : public QObject, public IMcSonglistDao {
    Q_OBJECT
    MC_DECL_INIT(McSonglistDao)
    MC_DEFINE_TYPELIST(QObject, MC_DECL_TYPELIST(IMcSonglistDao))
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
    int getMaxSonglistId() const noexcept;
    
private:
    MC_DECL_PRIVATE(McSonglistDao)
};

MC_DECL_METATYPE(McSonglistDao)
