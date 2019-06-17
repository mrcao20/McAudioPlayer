#ifndef _I_MC_MUSIC_API_H_
#define _I_MC_MUSIC_API_H_

#include <QList>

class McMusic;

class IMcMusicApi {
public:
	virtual ~IMcMusicApi() = default;

	virtual QString getMusicUrl(const McMusic* music) noexcept = 0;
	virtual QList<McMusic*> searchSong(const QString& songName, int limit = 20, int offset = 0) noexcept = 0;
};

Q_DECLARE_METATYPE(IMcMusicApi*)

#endif // !_I_MC_MUSIC_API_H_