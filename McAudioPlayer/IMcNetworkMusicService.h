#ifndef _I_MC_NETWORK_MUSIC_SERVICE_H_
#define _I_MC_NETWORK_MUSIC_SERVICE_H_

#include <qmetatype.h>
#include <QList>
#include <functional>

class McMusic;

class IMcNetworkMusicService {
public:
	virtual ~IMcNetworkMusicService() = default;

	virtual void getNetworkMusics(const std::function<void(const QList<McMusic*>&)>& callback, const QString& musicSrc, const QString& keyword) noexcept = 0;
	virtual void getLastPageMusic(const std::function<void(const QList<McMusic*>&)>& callback) noexcept = 0;
	virtual void getNextPageMusic(const std::function<void(const QList<McMusic*>&)>& callback) noexcept = 0;
	virtual void addToSongSheet(int songSheetId, const QList<McMusic*>& musics) noexcept = 0;
};

Q_DECLARE_METATYPE(IMcNetworkMusicService*)

#endif // !_I_MC_NETWORK_MUSIC_SERVICE_H_