#ifndef _I_MC_PLAYLIST_DAO_H_
#define _I_MC_PLAYLIST_DAO_H_

#include <qmetatype.h>
#include <QList>

class McMusic;

class IMcPlaylistDao {
public:
	virtual ~IMcPlaylistDao() = default;

	virtual QList<McMusic *> getPlaylist() noexcept = 0;
	virtual void getSongUrl(McMusic *music) noexcept = 0;
	virtual void updateMusicUrl(McMusic *music) noexcept = 0;
	virtual void getMusicDetail(McMusic *music) noexcept = 0;
	virtual bool deleteAll() noexcept = 0;
	virtual void addMusics(const QList<McMusic*>& musics, int songSheetId) noexcept = 0;
	virtual void remove(int id) noexcept = 0;
};

Q_DECLARE_METATYPE(IMcPlaylistDao*)

#endif // !_I_MC_PLAYLIST_DAO_H_