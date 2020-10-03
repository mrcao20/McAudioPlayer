#pragma once

#include "../IMcNetworkMusicService.h"
#include <McBoot/McBootGlobal.h>

MC_FORWARD_DECL_CLASS(IMcNetworkMusicModel);
MC_FORWARD_DECL_CLASS(IMcSonglistDao);
MC_FORWARD_DECL_CLASS(IMcNetworkMusicDao);

MC_FORWARD_DECL_PRIVATE_DATA(McNetworkMusicService);

class McNetworkMusicService : public QObject, public IMcNetworkMusicService {
    Q_OBJECT
    MC_DECL_INIT(McNetworkMusicService)
    MC_DEFINE_TYPELIST(QObject, MC_DECL_TYPELIST(IMcNetworkMusicService))
    MC_SERVICE
    MC_BEANNAME("networkMusicService")
    Q_CLASSINFO("model", "networkMusicModel")
    Q_PROPERTY(IMcNetworkMusicModelPtr model READ model WRITE setModel USER true)
    Q_PROPERTY(IMcSonglistDaoPtr songlistDao READ songlistDao WRITE setSonglistDao USER true)
    Q_PROPERTY(IMcNetworkMusicDaoPtr networkMusicDao READ networkMusicDao WRITE setNetworkMusicDao USER true)
public:
    Q_INVOKABLE McNetworkMusicService() noexcept;
    ~McNetworkMusicService() noexcept override;
    
    IMcNetworkMusicModelPtr model() const noexcept;
    void setModel(IMcNetworkMusicModelConstPtrRef val) noexcept;
    QAbstractItemModel *getModel() const noexcept override;
    
    IMcSonglistDaoPtr songlistDao() const noexcept;
    void setSonglistDao(IMcSonglistDaoConstPtrRef val) noexcept;
    
    IMcNetworkMusicDaoPtr networkMusicDao() const noexcept;
    void setNetworkMusicDao(IMcNetworkMusicDaoConstPtrRef val) noexcept;
    
    QList<McMusicPtr> getMusics() const noexcept override;
    QList<McMusicPtr> getMusics(const QList<int> &indexs) const noexcept override;
    int getIndex(const McMusicPtr &music) noexcept override;
    void addToSongSheet(int songSheetId, const QList<int> &indexs) noexcept override;
    void removeFromSongSheet(int songSheetId, const QList<int> &indexs) noexcept override;
    void addToSongSheet(int songSheetId, const QList<McMusicPtr> &musics) noexcept override;
    void getNetworkMusics(const QString &musicSrc, const QString &keyword) noexcept override;
    void getLastPageMusic() noexcept override;
    void getNextPageMusic() noexcept override;
    void clearModel() noexcept override;
    
private:
    MC_DECL_PRIVATE(McNetworkMusicService)
};

MC_DECL_METATYPE(McNetworkMusicService)
