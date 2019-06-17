#include "McNetworkMusicModel.h"

#include "McContainerGlobal.h"
#include "IMcNetworkMusicService.h"

MC_STATIC(McNetworkMusicModel)
mcRegisterComponent<McNetworkMusicModel*>("McNetworkMusicModel", "networkMusicModel");
MC_STATIC_END

struct McNetworkMusicModelData {
	IMcNetworkMusicService* networkMusicService{ nullptr };
};

McNetworkMusicModel::McNetworkMusicModel(QObject* parent) 
	: McMusicModel(parent)
	, d(new McNetworkMusicModelData)
{
}

McNetworkMusicModel::~McNetworkMusicModel() {
}

IMcNetworkMusicService* McNetworkMusicModel::getNetworkMusicService() const noexcept {
	return d->networkMusicService;
}

void McNetworkMusicModel::setNetworkMusicService(IMcNetworkMusicService* val) noexcept {
	d->networkMusicService = val;
}

void McNetworkMusicModel::getNetworkMusics(const QString& musicSrc, const QString& keyword) noexcept {
	clearModel();
	d->networkMusicService->getNetworkMusics([this](const QList<McMusic*>& musics) {
		setMusics(musics);
	}, musicSrc, keyword);
}

void McNetworkMusicModel::getLastPageMusic() noexcept {
	clearModel();
	d->networkMusicService->getLastPageMusic([this](const QList<McMusic*>& musics) {
		setMusics(musics);
	});
}

void McNetworkMusicModel::getNextPageMusic() noexcept {
	clearModel();
	d->networkMusicService->getNextPageMusic([this](const QList<McMusic*>& musics) {
		setMusics(musics);
	});
}

void McNetworkMusicModel::addToSongSheet(int songSheetId, const QList<int>& indexs) noexcept {
	QList<int> copyIndexs = indexs;
	std::sort(copyIndexs.begin(), copyIndexs.end(), std::greater<int>());	// Ωµ–Ú≈≈–Ú
	QList<McMusic*> musics;
	for (auto index : copyIndexs) {
		McMusic* music = getMusic(index);
		if (!music)
			continue;
		musics.append(music);
	}
	d->networkMusicService->addToSongSheet(songSheetId, musics);
}

QList<McMusic*> McNetworkMusicModel::getMusics(const QList<int>& indexs) const noexcept {
	QList<McMusic*> musics;
	for (auto index : indexs) {
		McMusic* music = getMusic(index);
		if (!music)
			continue;
		musics.append(music);
	}
	return musics;
}
