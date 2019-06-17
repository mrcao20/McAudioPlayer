#ifndef _MC_PLAYLIST_SERVICE_H_
#define _MC_PLAYLIST_SERVICE_H_
#pragma execution_character_set("utf-8")

#include <QObject>
#include "IMcPlaylistService.h"

#include "McBeanGlobal.h"

struct McPlaylistServiceData;

class IMcPlaylistDao;

class McPlaylistService : public QObject, public IMcPlaylistService {
	Q_OBJECT
	Q_PROPERTY(IMcPlaylistDao *playlistDao READ getPlaylistDao WRITE setPlaylistDao USER true)
	MC_DECL_STATIC(McPlaylistService)

public:
	Q_INVOKABLE explicit McPlaylistService(QObject *parent = 0);
	~McPlaylistService();

	IMcPlaylistDao *getPlaylistDao() const noexcept;
	void setPlaylistDao(IMcPlaylistDao *val) noexcept;

	QList<McMusic *> getPlaylist() noexcept override;
	void getSongUrl(McMusic *music) noexcept override;
	QList<McMusic*> addMusics(const QList<McMusic*>& musics, int songSheetId) noexcept override;

private:
	bool canConnecting(const QString &uri) noexcept;

private:
	QScopedPointer<McPlaylistServiceData> d;
};

Q_DECLARE_METATYPE(McPlaylistService*)

#endif // !_MC_PLAYLIST_SERVICE_H_