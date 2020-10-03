#pragma once

#include <QObject>

#include <McBoot/McBootGlobal.h>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

MC_FORWARD_DECL_CLASS(McMusic);

MC_FORWARD_DECL_CLASS(IMcNetworkMusicService);
MC_FORWARD_DECL_CLASS(IMcPlaylistService);

MC_FORWARD_DECL_PRIVATE_DATA(McNetworkMusicController);

class McNetworkMusicController : public QObject {
    Q_OBJECT
    MC_DECL_INIT(McNetworkMusicController)
    MC_DEFINE_TYPELIST(QObject)
    MC_CONTROLLER
    MC_BEANNAME("networkMusic")
    Q_PROPERTY(IMcNetworkMusicServicePtr networkMusicService READ networkMusicService WRITE setNetworkMusicService USER true)
    Q_PROPERTY(IMcPlaylistServicePtr playlistService READ playlistService WRITE setPlaylistService USER true)
public:
    Q_INVOKABLE McNetworkMusicController() noexcept;
    ~McNetworkMusicController() noexcept;
    
    IMcNetworkMusicServicePtr networkMusicService() const noexcept;
    void setNetworkMusicService(IMcNetworkMusicServiceConstPtrRef val) noexcept;
    
    IMcPlaylistServicePtr playlistService() const noexcept;
    void setPlaylistService(IMcPlaylistServiceConstPtrRef val) noexcept;
    
    Q_INVOKABLE QAbstractItemModel *getModel() const noexcept;
    Q_INVOKABLE int getIndex(const McMusicPtr music) const noexcept;
    Q_INVOKABLE void getNetworkMusics(
            const QString &musicSrc, const QString &keyword) noexcept;
    Q_INVOKABLE void addToPlaylist(const QList<int> &indexs, int songSheetId) noexcept;
    Q_INVOKABLE void addToSongSheet(int songSheetId, const QList<int> &indexs) noexcept;
    Q_INVOKABLE void getLastPageMusic() noexcept;
    Q_INVOKABLE void getNextPageMusic() noexcept;
    Q_INVOKABLE void clearModel() noexcept;
    
    
private:
    MC_DECL_PRIVATE(McNetworkMusicController)
};

MC_DECL_METATYPE(McNetworkMusicController)
