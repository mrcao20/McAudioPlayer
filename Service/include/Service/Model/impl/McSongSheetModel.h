#pragma once

#include "../IMcSongSheetModel.h"
#include <QAbstractListModel>

#include <McBoot/McBootGlobal.h>

MC_FORWARD_DECL_PRIVATE_DATA(McSongSheetModel);

class McSongSheetModel : public QAbstractListModel
        , public IMcSongSheetModel {
    
    Q_OBJECT
    MC_DECL_INIT(McSongSheetModel)
    MC_DEFINE_TYPELIST(QAbstractListModel, MC_DECL_TYPELIST(IMcSongSheetModel))
    MC_MODEL
    MC_BEANNAME("songSheetModel")
public:
    enum Roles {
        TitleRole = Qt::UserRole + 1,
        SongSheetRole
    };
    Q_INVOKABLE McSongSheetModel() noexcept;
    ~McSongSheetModel() noexcept override;
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    
    QList<McSongSheetPtr> getSongSheets() const noexcept override;
    void setSongSheets(const QList<McSongSheetPtr> &songSheets) noexcept override;
    void updateSongSheet(int index, McSongSheetConstPtrRef songSheet) noexcept override;
    void deleteSongSheet(int index) noexcept override;
    void addSongSheet(McSongSheetConstPtrRef songSheet) noexcept override;
    
protected:
    void customEvent(QEvent *event) override;
    
private:
    void doReload(const QList<McSongSheetPtr> &songSheets) noexcept;
    void doUpdate(int index, McSongSheetConstPtrRef &songSheet) noexcept;
    void doDelete(int index) noexcept;
    void doAdd(McSongSheetConstPtrRef &songSheet) noexcept;
    
private:
    MC_DECL_PRIVATE(McSongSheetModel)
};

MC_DECL_METATYPE(McSongSheetModel)
