#ifndef _MC_NETWORK_MUSIC_SERVICE_H_
#define _MC_NETWORK_MUSIC_SERVICE_H_

#include <QObject>
#include "IMcNetworkMusicService.h"

#include "McBeanGlobal.h"

struct McNetworkMusicServiceData;

class IMcNetworkMusicDao;
class IMcSonglistDao;

class McNetworkMusicService : public QObject, public IMcNetworkMusicService {
	Q_OBJECT
	Q_PROPERTY(IMcNetworkMusicDao* networkMusicDao READ getNetworkMusicDao WRITE setNetworkMusicDao USER true)
	Q_PROPERTY(IMcSonglistDao* songlistDao READ getSonglistDao WRITE setSonglistDao USER true)
	MC_DECL_STATIC(McNetworkMusicService)

public:
	Q_INVOKABLE explicit McNetworkMusicService(QObject* parent = 0);
	~McNetworkMusicService();

	IMcNetworkMusicDao* getNetworkMusicDao() const noexcept;
	void setNetworkMusicDao(IMcNetworkMusicDao* val) noexcept;

	IMcSonglistDao* getSonglistDao() const noexcept;
	void setSonglistDao(IMcSonglistDao* val) noexcept;

	void getNetworkMusics(const std::function<void(const QList<McMusic*>&)>& callback, const QString& musicSrc, const QString& keyword) noexcept override;
	void getLastPageMusic(const std::function<void(const QList<McMusic*>&)>& callback) noexcept override;
	void getNextPageMusic(const std::function<void(const QList<McMusic*>&)>& callback) noexcept override;
	void addToSongSheet(int songSheetId, const QList<McMusic*>& musics) noexcept override;

private:
	void getNetworkMusics(const std::function<void(const QList<McMusic*>&)>& callback) noexcept;

private:
	QScopedPointer<McNetworkMusicServiceData> d;
};

Q_DECLARE_METATYPE(McNetworkMusicService*)

#endif // !_MC_NETWORK_MUSIC_SERVICE_H_