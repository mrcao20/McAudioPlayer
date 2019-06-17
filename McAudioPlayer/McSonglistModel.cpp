#include "McSonglistModel.h"

#include "McContainerGlobal.h"
#include "IMcSonglistService.h"
#include "McMusic.h"

MC_STATIC(McSonglistModel)
mcRegisterComponent<McSonglistModel*>("McSonglistModel", "songlistModel");
MC_STATIC_END

struct McSonglistModelData {
	IMcSonglistService *songlistService{ nullptr };
};

McSonglistModel::McSonglistModel(QObject *parent)
	: McMusicModel(parent)
	, d(new McSonglistModelData)
{
}

McSonglistModel::~McSonglistModel(){
}

IMcSonglistService *McSonglistModel::getSonglistService() const noexcept {
	return d->songlistService;
}

void McSonglistModel::setSonglistService(IMcSonglistService *val) noexcept {
	d->songlistService = val;
}

void McSonglistModel::updateMusic(int songSheetId) noexcept {
	QList<McMusic *> musics = d->songlistService->getMusics(songSheetId);
	setMusics(musics);
}

void McSonglistModel::addToSongSheet(int songSheetId, const QList<int>& indexs) noexcept {
	QList<int> copyIndexs = indexs;
	std::sort(copyIndexs.begin(), copyIndexs.end(), std::greater<int>());	// 降序排序
	QList<McMusic*> musics;
	for (auto index : copyIndexs) {
		McMusic* music = getMusic(index);
		if (!music)
			continue;
		musics.append(music);
	}
	d->songlistService->addToSongSheet(songSheetId, musics);
}

void McSonglistModel::removeFromSongSheet(int songSheetId, const QList<int>& indexs) noexcept {
	QList<int> copyIndexs = indexs;
	std::sort(copyIndexs.begin(), copyIndexs.end());	// 默认升序排序
	QList<McMusic*> musics;
	int offset = 0;
	for (auto index : copyIndexs) {
		// 由于项被take之后index会减一，所以这里需要减去之前被take出的项数量
		McMusic* music = takeMusic(index - offset);
		if (!music)
			continue;
		++offset;	// 当项被成功take之后，项数量加一
		musics.append(music);
	}
	d->songlistService->removeFromSongSheet(songSheetId, musics);
	qDeleteAll(musics);
}
