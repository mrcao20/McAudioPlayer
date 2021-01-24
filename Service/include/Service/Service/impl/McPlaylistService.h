#pragma once

#include "../IMcPlaylistService.h"
#include <McBoot/McBootGlobal.h>

MC_FORWARD_DECL_CLASS(IMcMusicService);
MC_FORWARD_DECL_CLASS(IMcPlaylistModel);
MC_FORWARD_DECL_CLASS(IMcPlaylistDao);

MC_FORWARD_DECL_PRIVATE_DATA(McPlaylistService);

class McPlaylistService : public QObject, public IMcPlaylistService {
    Q_OBJECT
    MC_DECL_INIT(McPlaylistService)
    MC_TYPELIST(QObject, IMcPlaylistService)
    MC_SERVICE
    MC_BEANNAME("playlistService")
    MC_AUTOWIRED("musicService")
    Q_PROPERTY(IMcMusicServicePtr musicService READ musicService WRITE setMusicService)
    MC_AUTOWIRED("model = playlistModel")
    Q_PROPERTY(IMcPlaylistModelPtr model READ model WRITE setModel)
    MC_AUTOWIRED("playlistDao")
    Q_PROPERTY(IMcPlaylistDaoPtr playlistDao READ playlistDao WRITE setPlaylistDao)
public:
    Q_INVOKABLE McPlaylistService() noexcept;
    ~McPlaylistService() noexcept override;
    
    IMcMusicServicePtr musicService() const noexcept;
    void setMusicService(IMcMusicServiceConstPtrRef val) noexcept;
    
    IMcPlaylistModelPtr model() const noexcept;
    void setModel(IMcPlaylistModelConstPtrRef val) noexcept;
    QAbstractItemModel *getModel() const noexcept override;
    
    IMcPlaylistDaoPtr playlistDao() const noexcept;
    void setPlaylistDao(IMcPlaylistDaoConstPtrRef val) noexcept;
    
    void loadPlaylist() noexcept override;
    void setMusics(const QList<McMusicPtr> &musics, int songSheetId) noexcept override;
    McMusicPtr getMusic(int index) noexcept override;
    
private:
    bool isSame(const QList<McMusicPtr> &musics, const QList<McMusicPtr> &oldMusics) noexcept;
    
private:
    MC_DECL_PRIVATE(McPlaylistService)
};

MC_DECL_METATYPE(McPlaylistService)
