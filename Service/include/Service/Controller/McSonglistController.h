#pragma once

#include <QObject>

#include <McBoot/McBootGlobal.h>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

MC_FORWARD_DECL_CLASS(McMusic);
MC_FORWARD_DECL_CLASS(IMcSonglistService);
MC_FORWARD_DECL_CLASS(IMcPlaylistService);

MC_FORWARD_DECL_PRIVATE_DATA(McSonglistController);

class McSonglistController : public QObject {
    Q_OBJECT
    MC_DECL_INIT(McSonglistController)
    MC_DEFINE_TYPELIST(QObject)
    MC_CONTROLLER
    MC_BEANNAME("songlist")
    MC_AUTOWIRED("songlistService")
    Q_PROPERTY(IMcSonglistServicePtr songlistService READ songlistService WRITE setSonglistService)
    MC_AUTOWIRED("playlistService")
    Q_PROPERTY(IMcPlaylistServicePtr playlistService READ playlistService WRITE setPlaylistService)
public:
    Q_INVOKABLE McSonglistController() noexcept;
    ~McSonglistController() noexcept;
    
    IMcSonglistServicePtr songlistService() const noexcept;
    void setSonglistService(IMcSonglistServiceConstPtrRef val) noexcept;
    
    IMcPlaylistServicePtr playlistService() const noexcept;
    void setPlaylistService(IMcPlaylistServiceConstPtrRef val) noexcept;
    
    Q_INVOKABLE QAbstractItemModel *getModel() const noexcept;
    Q_INVOKABLE void reloadMusic(int songSheetId) noexcept;
    Q_INVOKABLE void addToPlaylist(int songSheetId) noexcept;
    Q_INVOKABLE int getIndex(const McMusicPtr &music) noexcept;
    Q_INVOKABLE void addToSongSheet(int songSheetId, const QList<int> &indexs) noexcept;
    Q_INVOKABLE void removeFromSongSheet(int songSheetId, const QList<int>& indexs) noexcept;
    
private:
    MC_DECL_PRIVATE(McSonglistController)
};

MC_DECL_METATYPE(McSonglistController)
