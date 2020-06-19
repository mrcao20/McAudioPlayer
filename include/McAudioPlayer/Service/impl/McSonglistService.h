#pragma once

#include "../IMcSonglistService.h"

MC_FORWARD_DECL_CLASS(IMcSonglistModel);
MC_FORWARD_DECL_CLASS(IMcNetworkMusicService);
MC_FORWARD_DECL_CLASS(IMcSonglistDao);
MC_FORWARD_DECL_CLASS(IMcNetworkMusicDao);

MC_FORWARD_DECL_PRIVATE_DATA(McSonglistService);

class McSonglistService : public QObject, public IMcSonglistService {
    Q_OBJECT
    MC_DECL_INIT(McSonglistService)
    MC_DEFINE_TYPELIST(QObject, MC_DECL_TYPELIST(IMcSonglistService))
    Q_CLASSINFO(MC_BEANNAME, "songlistService")
    Q_CLASSINFO("model", "songlistModel")
    Q_PROPERTY(IMcSonglistModelPtr model READ model WRITE setModel)
    Q_PROPERTY(IMcNetworkMusicServicePtr networkMusicService READ networkMusicService WRITE setNetworkMusicService USER true)
    Q_PROPERTY(IMcSonglistDaoPtr songlistDao READ songlistDao WRITE setSonglistDao USER true)
    Q_PROPERTY(IMcNetworkMusicDaoPtr networkMusicDao READ networkMusicDao WRITE setNetworkMusicDao USER true)
public:
    Q_INVOKABLE McSonglistService() noexcept;
    ~McSonglistService() noexcept override;
    
    IMcSonglistModelPtr model() const noexcept;
    void setModel(IMcSonglistModelConstPtrRef val) noexcept;
    QAbstractItemModel *getModel() const noexcept override;
    
    IMcNetworkMusicServicePtr networkMusicService() const noexcept;
    void setNetworkMusicService(IMcNetworkMusicServiceConstPtrRef val) noexcept;
    
    IMcSonglistDaoPtr songlistDao() const noexcept;
    void setSonglistDao(IMcSonglistDaoConstPtrRef val) noexcept;
    
    IMcNetworkMusicDaoPtr networkMusicDao() const noexcept;
    void setNetworkMusicDao(IMcNetworkMusicDaoConstPtrRef val) noexcept;
    
    void reloadMusic(int songSheetId) noexcept override;
    QList<McMusicPtr> getMusics() const noexcept override;
    QList<McMusicPtr> getMusics(const QList<int> &indexs) const noexcept override;
    int getIndex(const McMusicPtr &music) noexcept override;
    void addToSongSheet(int songSheetId, const QList<int> &indexs) noexcept override;
    void removeFromSongSheet(int songSheetId, const QList<int> &indexs) noexcept override;
    void addNewLocalMusics(int songSheetId, const QList<QUrl> &filePaths) noexcept override;
    
protected:
    void customEvent(QEvent *e) override;
    
private:
    MC_DECL_PRIVATE(McSonglistService)
};

MC_DECL_METATYPE(McSonglistService)
