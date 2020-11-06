#pragma once

#include <QObject>

#include <QJsonObject>

#include <McBoot/McBootGlobal.h>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

MC_FORWARD_DECL_CLASS(IMcPlaylistService);

MC_FORWARD_DECL_PRIVATE_DATA(McPlaylistController);

class McPlaylistController : public QObject {
    Q_OBJECT
    MC_DECL_INIT(McPlaylistController)
    MC_DEFINE_TYPELIST(QObject)
    MC_CONTROLLER
    MC_BEANNAME("playlist")
    MC_AUTOWIRED("playlistService")
    Q_PROPERTY(IMcPlaylistServicePtr playlistService READ playlistService WRITE setPlaylistService)
public:
    Q_INVOKABLE McPlaylistController() noexcept;
    ~McPlaylistController() noexcept;
    
    IMcPlaylistServicePtr playlistService() const noexcept;
    void setPlaylistService(IMcPlaylistServiceConstPtrRef val) noexcept;
    
    Q_INVOKABLE QAbstractItemModel *getModel() const noexcept;
    Q_INVOKABLE void loadPlaylist() noexcept;
    Q_INVOKABLE QJsonObject getMusic(int index) noexcept;
    
private:
    MC_DECL_PRIVATE(McPlaylistController)
};

MC_DECL_METATYPE(McPlaylistController)
