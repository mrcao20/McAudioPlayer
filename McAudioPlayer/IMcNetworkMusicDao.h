#ifndef _I_MC_NETWORK_MUSIC_DAO_H_
#define _I_MC_NETWORK_MUSIC_DAO_H_

#include <qmetatype.h>

class McMusic;
class McAlbum;
class McArtist;

class IMcNetworkMusicDao {
public:
	virtual ~IMcNetworkMusicDao() = default;

	virtual bool getIdIfExistsForUrl(McMusic* music) noexcept = 0;
	virtual bool getIdIfExists(McMusic* music) noexcept = 0;
	virtual bool getIdIfExists(McAlbum* album) noexcept = 0;
	virtual bool getIdIfExists(McArtist* artist) noexcept = 0;
	virtual void addAlbum(McAlbum* album) noexcept = 0;
	virtual void addArtist(McArtist* artist) noexcept = 0;
	virtual void addMusic(McMusic* music) noexcept = 0;
	virtual int getMaxAlbumId() noexcept = 0;
	virtual int getMaxArtistId() noexcept = 0;
};

Q_DECLARE_METATYPE(IMcNetworkMusicDao*)

#endif // !_I_MC_NETWORK_MUSIC_DAO_H_