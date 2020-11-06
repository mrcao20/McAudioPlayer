#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McMusic);

class IMcSonglistDao {
    MC_DEFINE_TYPELIST()
public:
    virtual ~IMcSonglistDao() noexcept = default;
    
    virtual QList<McMusicPtr> reloadMusic(int songSheetId) noexcept = 0;
    virtual bool isExists(int songSheetId, McMusicConstPtrRef music) noexcept = 0;
    virtual void addToSongSheet(int songSheetId, McMusicConstPtrRef music) noexcept = 0;
    // 得到t_songlist_info表中的id字段
    virtual int getSonglistId(int songSheetId, McMusicConstPtrRef music) noexcept = 0;
    // 从t_songlist_info表中移除id为'id'的数据
    virtual void removeSonglist(int id) noexcept = 0;
    virtual int getMaxMusicId() noexcept = 0;
};

MC_DECL_METATYPE(IMcSonglistDao)
