#ifndef _MC_NETWORK_MUSIC_DAO_H_
#define _MC_NETWORK_MUSIC_DAO_H_

#include <QObject>
#include "IMcNetworkMusicDao.h"

#include "McBeanGlobal.h"

class McNetworkMusicDao : public QObject, public IMcNetworkMusicDao {
	Q_OBJECT
	MC_DECL_STATIC(McNetworkMusicDao)

public:
	Q_INVOKABLE explicit McNetworkMusicDao(QObject* parent = 0);
	virtual ~McNetworkMusicDao();

	bool getIdIfExistsForUrl(McMusic* music) noexcept override;
	bool getIdIfExists(McMusic* music) noexcept override;
	bool getIdIfExists(McAlbum* album) noexcept override;
	bool getIdIfExists(McArtist* artist) noexcept override;
	void addAlbum(McAlbum* album) noexcept override;
	void addArtist(McArtist* artist) noexcept override;
	void addMusic(McMusic* music) noexcept override;
	int getMaxAlbumId() noexcept override;
	int getMaxArtistId() noexcept override;
	
};

Q_DECLARE_METATYPE(McNetworkMusicDao*)

#endif // !_MC_NETWORK_MUSIC_DAO_H_