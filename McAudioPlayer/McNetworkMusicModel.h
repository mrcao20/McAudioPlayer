#ifndef _MC_NETWORK_MUSIC_MODEL_H_
#define _MC_NETWORK_MUSIC_MODEL_H_

#include "McMusicModel.h"

#include "McGlobal.h"
#include "McBeanGlobal.h"

struct McNetworkMusicModelData;

class IMcNetworkMusicService;

class McNetworkMusicModel : public McMusicModel {
	Q_OBJECT
	Q_PROPERTY(IMcNetworkMusicService* networkMusicService READ getNetworkMusicService WRITE setNetworkMusicService USER true)
	Q_CLASSINFO("Component", MC_MODEL_STR)
	MC_DECL_STATIC(McNetworkMusicModel)

public:
	using McMusicModel::getMusics;

	Q_INVOKABLE explicit McNetworkMusicModel(QObject* parent = 0);
	~McNetworkMusicModel();

	IMcNetworkMusicService* getNetworkMusicService() const noexcept;
	void setNetworkMusicService(IMcNetworkMusicService* val) noexcept;

	Q_INVOKABLE void getNetworkMusics(const QString& musicSrc, const QString& keyword) noexcept;
	Q_INVOKABLE void getLastPageMusic() noexcept;
	Q_INVOKABLE void getNextPageMusic() noexcept;
	Q_INVOKABLE void addToSongSheet(int songSheetId, const QList<int>& indexs) noexcept;
	Q_INVOKABLE QList<McMusic*> getMusics(const QList<int>& indexs) const noexcept;

private:
	QScopedPointer<McNetworkMusicModelData> d;
};

Q_DECLARE_METATYPE(McNetworkMusicModel*)

#endif // !_MC_NETWORK_MUSIC_MODEL_H_