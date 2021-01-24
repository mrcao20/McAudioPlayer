#pragma once

#include "IMcAcquireModel.h"

MC_FORWARD_DECL_CLASS(McSongSheet);

class IMcSongSheetService : public IMcAcquireModel {
    MC_TYPELIST(IMcAcquireModel)
public:
    ~IMcSongSheetService() noexcept override = default;
    
    virtual QList<McSongSheetPtr> loadSongSheets(
            const QString &section, const QStringList &list) noexcept = 0;
    virtual int getSongSheetId(int index) const noexcept = 0;
    virtual bool rename(int index, const QString &newText) noexcept = 0;
    virtual void deleteSongSheet(int index) noexcept = 0;
    virtual int createSongSheet(const QString &title, const QString &newName) noexcept = 0;
};

MC_DECL_METATYPE(IMcSongSheetService)
