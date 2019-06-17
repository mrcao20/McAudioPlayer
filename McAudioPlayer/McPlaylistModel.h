#ifndef _MC_PLAYLIST_MODEL_H_
#define _MC_PLAYLIST_MODEL_H_
#pragma execution_character_set("utf-8")

#include "McMusicModel.h"

#include "McGlobal.h"
#include "McBeanGlobal.h"

struct McPlaylistModelData;

class IMcPlaylistService;

class McPlaylistModel : public McMusicModel {
	Q_OBJECT
	Q_PROPERTY(IMcPlaylistService *playlistService READ getPlaylistService WRITE setPlaylistService USER true)
	Q_CLASSINFO("Component", MC_MODEL_STR)
	MC_DECL_STATIC(McPlaylistModel)

public:
	Q_INVOKABLE explicit McPlaylistModel(QObject *parent = 0);
	~McPlaylistModel();

	IMcPlaylistService *getPlaylistService() const noexcept;
	void setPlaylistService(IMcPlaylistService *val) noexcept;

	Q_INVOKABLE void loadPlaylist() noexcept;
	Q_INVOKABLE McMusic* getMusic(int index) noexcept;
	Q_INVOKABLE void addMusics(const QList<McMusic*>& musics, int songSheetId) noexcept;

private:
	bool isSame(const QList<McMusic*>& musics) noexcept;

private:
	QScopedPointer<McPlaylistModelData> d;
};

Q_DECLARE_METATYPE(McPlaylistModel*)

#endif // !_MC_PLAYLIST_MODEL_H_