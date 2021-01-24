#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McMusic);
MC_FORWARD_DECL_CLASS(McAlbum);
MC_FORWARD_DECL_CLASS(McArtist);

class IMcNetworkMusicDao {
    MC_TYPELIST()
public:
    virtual ~IMcNetworkMusicDao() noexcept = default;
    
    virtual bool getIdIfExistsForUrl(McMusicPtr music) noexcept = 0;
    virtual bool getIdIfExists(McMusicPtr music) noexcept = 0;
    virtual bool getIdIfExists(McAlbumPtr album) noexcept = 0;
    virtual bool getIdIfExists(McArtistPtr artist) noexcept = 0;
    virtual void addAlbum(McAlbumPtr album) noexcept = 0;
    virtual void addArtist(McArtistPtr artist) noexcept = 0;
    virtual void addMusic(McMusicPtr music) noexcept = 0;
    virtual int getMaxAlbumId() noexcept = 0;
    virtual int getMaxArtistId() noexcept = 0;
};

MC_DECL_METATYPE(IMcNetworkMusicDao)
