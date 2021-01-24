#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McSongSheet);

class IMcSongSheetDao {
    MC_TYPELIST()
public:
    virtual ~IMcSongSheetDao() noexcept = default;
    
    virtual QList<McSongSheetPtr> getSongSheets() noexcept = 0;
    virtual void renameSongSheet(McSongSheetConstPtrRef songSheet) noexcept = 0;
    virtual void deleteSongSheet(McSongSheetConstPtrRef songSheet) noexcept = 0;
    virtual bool insert(McSongSheetConstPtrRef songSheet) noexcept = 0;
};

MC_DECL_METATYPE(IMcSongSheetDao)
