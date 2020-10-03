#pragma once

#include <QObject>

#include <QUrl>
#include <QJsonArray>

#include <McBoot/McBootGlobal.h>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

MC_FORWARD_DECL_CLASS(IMcSongSheetService);
MC_FORWARD_DECL_CLASS(IMcSonglistService);

MC_FORWARD_DECL_PRIVATE_DATA(McSongSheetController);

class McSongSheetController : public QObject {
    Q_OBJECT
    MC_DECL_INIT(McSongSheetController)
    MC_DEFINE_TYPELIST(QObject)
    MC_CONTROLLER
    MC_BEANNAME("songSheet")
    Q_PROPERTY(IMcSongSheetServicePtr songSheetService READ songSheetService WRITE setSongSheetService USER true)
    Q_PROPERTY(IMcSonglistServicePtr songlistService READ songlistService WRITE setSonglistService USER true)
public:
    Q_INVOKABLE McSongSheetController() noexcept;
    ~McSongSheetController() noexcept;
    
    IMcSongSheetServicePtr songSheetService() const noexcept;
    void setSongSheetService(IMcSongSheetServiceConstPtrRef val) noexcept;
    
    IMcSonglistServicePtr songlistService() const noexcept;
    void setSonglistService(IMcSonglistServiceConstPtrRef val) noexcept;
    
    Q_INVOKABLE QAbstractItemModel *getModel() const noexcept;
    Q_INVOKABLE QJsonArray loadSongSheets(const QString &section
                                          , const QStringList &list) noexcept;
    Q_INVOKABLE void addLocalMusics(int index, const QList<QUrl> &filePaths) noexcept;
    Q_INVOKABLE bool rename(int index, const QString &newText) noexcept;
    Q_INVOKABLE void deleteSongSheet(int index) noexcept;
    Q_INVOKABLE int createNewSongSheet(const QString &title, const QString &newName) noexcept;
    
private:
    MC_DECL_PRIVATE(McSongSheetController)
};

MC_DECL_METATYPE(McSongSheetController)
