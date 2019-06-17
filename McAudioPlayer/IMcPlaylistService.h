#ifndef _I_MC_PLAYLIST_SERVICE_H_
#define _I_MC_PLAYLIST_SERVICE_H_

#include <qmetatype.h>
#include <QList>

class McMusic;

class IMcPlaylistService {
public:
	virtual ~IMcPlaylistService() = default;

	virtual QList<McMusic *> getPlaylist() noexcept = 0;
	virtual void getSongUrl(McMusic *music) noexcept = 0;
	virtual QList<McMusic*> addMusics(const QList<McMusic*>& musics, int songSheetId) noexcept = 0;
};

Q_DECLARE_METATYPE(IMcPlaylistService*)

#endif // !_I_MC_PLAYLIST_SERVICE_H_