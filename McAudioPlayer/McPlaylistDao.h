#ifndef _MC_PLAYLIST_DAO_H_
#define _MC_PLAYLIST_DAO_H_

#include <QObject>
#include "IMcPlaylistDao.h"

#include "McBeanGlobal.h"

class McPlaylistDao : public QObject, public IMcPlaylistDao {
	Q_OBJECT
	MC_DECL_STATIC(McPlaylistDao)

public:
	Q_INVOKABLE explicit McPlaylistDao(QObject *parent = 0);
	~McPlaylistDao();

	QList<McMusic *> getPlaylist() noexcept override;
	void getSongUrl(McMusic *music) noexcept override;
	void updateMusicUrl(McMusic *music) noexcept override;
	void getMusicDetail(McMusic *music) noexcept override;
	bool deleteAll() noexcept override;
	void addMusics(const QList<McMusic*>& musics, int songSheetId) noexcept override;
	void remove(int id) noexcept override;
};

Q_DECLARE_METATYPE(McPlaylistDao*)

#endif // !_MC_PLAYLIST_DAO_H_