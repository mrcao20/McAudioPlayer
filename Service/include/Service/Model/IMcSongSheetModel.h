#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McSongSheet);

class IMcSongSheetModel {
    MC_TYPELIST()
public:
    virtual ~IMcSongSheetModel() noexcept = default;
    
    virtual QList<McSongSheetPtr> getSongSheets() const noexcept = 0;
    virtual void setSongSheets(const QList<McSongSheetPtr> &songSheets) noexcept = 0;
    virtual void updateSongSheet(int index, McSongSheetConstPtrRef songSheet) noexcept = 0;
    virtual void deleteSongSheet(int index) noexcept = 0;
    virtual void addSongSheet(McSongSheetConstPtrRef songSheet) noexcept = 0;
};

MC_DECL_METATYPE(IMcSongSheetModel)
