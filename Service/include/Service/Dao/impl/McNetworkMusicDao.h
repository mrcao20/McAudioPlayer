#pragma once

#include "../IMcNetworkMusicDao.h"

MC_FORWARD_DECL_PRIVATE_DATA(McNetworkMusicDao);

class McNetworkMusicDao : public QObject, public IMcNetworkMusicDao {
    Q_OBJECT
    MC_DECL_INIT(McNetworkMusicDao)
    MC_TYPELIST(QObject, IMcNetworkMusicDao)
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
    Q_INVOKABLE bool getIdIfExistsForUrl_helper(McMusicPtr music) noexcept;
    Q_INVOKABLE bool getIdIfExists_helper(McMusicPtr music) noexcept;
    Q_INVOKABLE bool getIdIfExists_helper(McAlbumPtr album) noexcept;
    Q_INVOKABLE bool getIdIfExists_helper(McArtistPtr artist) noexcept;
    Q_INVOKABLE void addAlbum_helper(McAlbumPtr album) noexcept;
    Q_INVOKABLE void addArtist_helper(McArtistPtr artist) noexcept;
    Q_INVOKABLE void addMusic_helper(McMusicPtr music) noexcept;
    Q_INVOKABLE int getMaxAlbumId_helper() noexcept;
    Q_INVOKABLE int getMaxArtistId_helper() noexcept;

private:
    MC_DECL_PRIVATE(McNetworkMusicDao)
};

MC_DECL_METATYPE(McNetworkMusicDao)
