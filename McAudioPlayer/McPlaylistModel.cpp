#include "McPlaylistModel.h"

#include "McContainerGlobal.h"
#include "IMcPlaylistService.h"
#include "McMusic.h"

MC_STATIC(McPlaylistModel)
mcRegisterComponent<McPlaylistModel*>("McPlaylistModel", "playlistModel");
MC_STATIC_END

struct McPlaylistModelData {
	IMcPlaylistService *playlistService{ nullptr };
};

McPlaylistModel::McPlaylistModel(QObject *parent)
	: McMusicModel(parent)
	, d(new McPlaylistModelData)
{
}

McPlaylistModel::~McPlaylistModel(){
}

IMcPlaylistService *McPlaylistModel::getPlaylistService() const noexcept {
	return d->playlistService;
}

void McPlaylistModel::setPlaylistService(IMcPlaylistService *val) noexcept {
	d->playlistService = val;
}

void McPlaylistModel::loadPlaylist() noexcept {
	QList<McMusic *> musics = d->playlistService->getPlaylist();
	setMusics(musics);
}

McMusic* McPlaylistModel::getMusic(int index) noexcept {
	QList<McMusic*> musics = getMusics();
	if (!Mc::isContains(index, musics))
		return nullptr;
	McMusic* music = musics.at(index);
	if (music->getSongUrl().isEmpty())
		d->playlistService->getSongUrl(music);
	qInfo() << "获取到的音乐链接" << music->getSongUrl();
	return music;
}

void McPlaylistModel::addMusics(const QList<McMusic*>& musics, int songSheetId) noexcept{
	if (isSame(musics))
		return;
	QList<McMusic*> ms = d->playlistService->addMusics(musics, songSheetId);
	setMusics(ms);
}

bool McPlaylistModel::isSame(const QList<McMusic*>& musics) noexcept {
	QList<McMusic*> cur = getMusics();
	if (cur.size() != musics.size())
		return false;
	for (int i = 0; i < cur.size(); ++i) {
		auto curMusic = cur.at(i);
		auto music = musics.at(i);
		if (curMusic->getId() != music->getId() || curMusic->getId() <= 0 || music->getId() <= 0)
			return false;
	}
	return true;
}
