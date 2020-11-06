#pragma once

#include "../IMcSongSheetService.h"
#include <McBoot/McBootGlobal.h>

MC_FORWARD_DECL_CLASS(IMcSongSheetModel);
MC_FORWARD_DECL_CLASS(IMcSongSheetDao);

MC_FORWARD_DECL_PRIVATE_DATA(McSongSheetService);

class McSongSheetService : public QObject, public IMcSongSheetService {
    Q_OBJECT
    MC_DECL_INIT(McSongSheetService)
    MC_DEFINE_TYPELIST(QObject, MC_DECL_TYPELIST(IMcSongSheetService))
    MC_SERVICE
    MC_BEANNAME("songSheetService")
    MC_AUTOWIRED("model = songSheetModel")
    Q_PROPERTY(IMcSongSheetModelPtr model READ model WRITE setModel)
    MC_AUTOWIRED("songSheetDao")
    Q_PROPERTY(IMcSongSheetDaoPtr songSheetDao READ songSheetDao WRITE setSongSheetDao)
public:
    Q_INVOKABLE McSongSheetService() noexcept;
    ~McSongSheetService() noexcept override;
    
    IMcSongSheetModelPtr model() const noexcept;
    void setModel(IMcSongSheetModelConstPtrRef val) noexcept;
    QAbstractItemModel *getModel() const noexcept override;
    
    IMcSongSheetDaoPtr songSheetDao() const noexcept;
    void setSongSheetDao(IMcSongSheetDaoConstPtrRef val) noexcept;
    
    QList<McSongSheetPtr> loadSongSheets(
            const QString &section, const QStringList &list) noexcept override;
    int getSongSheetId(int index) const noexcept override;
    bool rename(int index, const QString &newText) noexcept override;
    void deleteSongSheet(int index) noexcept override;
    int createSongSheet(const QString &title, const QString &newName) noexcept override;
    
private:
    void sort(QList<McSongSheetPtr> &songSheets
              , const QString &section, const QStringList &list) noexcept;
    bool isContainsName(const QString &name, const QList<McSongSheetPtr> &songSheets) const noexcept;
    int getMaxId(const QList<McSongSheetPtr> &songSheets) const noexcept;
    
private:
    MC_DECL_PRIVATE(McSongSheetService)
};

MC_DECL_METATYPE(McSongSheetService)
