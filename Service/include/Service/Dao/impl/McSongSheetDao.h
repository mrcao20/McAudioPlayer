#pragma once

#include "../IMcSongSheetDao.h"

MC_FORWARD_DECL_PRIVATE_DATA(McSongSheetDao);

class McSongSheetDao : public QObject, public IMcSongSheetDao {
    Q_OBJECT
    MC_DECL_INIT(McSongSheetDao)
    MC_TYPELIST(QObject, IMcSongSheetDao)
    MC_COMPONENT
    MC_BEANNAME("songSheetDao")
public:
    Q_INVOKABLE McSongSheetDao() noexcept;
    ~McSongSheetDao() noexcept override;
    
    QList<McSongSheetPtr> getSongSheets() noexcept override;
    void renameSongSheet(McSongSheetConstPtrRef songSheet) noexcept override;
    void deleteSongSheet(McSongSheetConstPtrRef songSheet) noexcept override;
    bool insert(McSongSheetConstPtrRef songSheet) noexcept override;

private:
    Q_INVOKABLE QList<McSongSheetPtr> getSongSheets_helper() noexcept;
    Q_INVOKABLE void renameSongSheet_helper(const McSongSheetPtr &songSheet) noexcept;
    Q_INVOKABLE void deleteSongSheet_helper(const McSongSheetPtr &songSheet) noexcept;
    Q_INVOKABLE bool insert_helper(const McSongSheetPtr &songSheet) noexcept;

private:
    MC_DECL_PRIVATE(McSongSheetDao)
};

MC_DECL_METATYPE(McSongSheetDao)
