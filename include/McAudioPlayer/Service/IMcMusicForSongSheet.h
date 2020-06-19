#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McMusic);

class IMcMusicForSongSheet {
    MC_DEFINE_TYPELIST()
public:
    virtual ~IMcMusicForSongSheet() noexcept = default;
    
    virtual void addToSongSheet(int songSheetId, const QList<int> &indexs) noexcept = 0;
    virtual void removeFromSongSheet(int songSheetId, const QList<int> &indexs) noexcept = 0;
};

MC_DECL_METATYPE(IMcMusicForSongSheet)
