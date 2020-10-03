#pragma once

#include "../IMcNetworkMusicDao.h"

MC_FORWARD_DECL_PRIVATE_DATA(McNetworkMusicDao);

class McNetworkMusicDao : public QObject, public IMcNetworkMusicDao {
    Q_OBJECT
    MC_DECL_INIT(McNetworkMusicDao)
    MC_DEFINE_TYPELIST(QObject, MC_DECL_TYPELIST(IMcNetworkMusicDao))
    MC_COMPONENT
    MC_BEANNAME("networkMusicDao")
public:
    Q_INVOKABLE McNetworkMusicDao() noexcept;
    ~McNetworkMusicDao() noexcept override;
    
    bool getIdIfExistsForUrl(McMusicPtr music) noexcept override;
    bool getIdIfExists(McMusicPtr music) noexcept override;
    bool getIdIfExists(McAlbumPtr album) noexcept override;
    bool getIdIfExists(McArtistPtr artist) noexcept override;
    void addAlbum(McAlbumPtr album) noexcept override;
    void addArtist(McArtistPtr artist) noexcept override;
    void addMusic(McMusicPtr music) noexcept override;
    int getMaxAlbumId() noexcept override;
    int getMaxArtistId() noexcept override;
    
private:
    MC_DECL_PRIVATE(McNetworkMusicDao)
};

MC_DECL_METATYPE(McNetworkMusicDao)
