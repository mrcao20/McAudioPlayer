#include "McNetworkMusicService.h"

#include <QtConcurrent>
#include <qdebug.h>

#include "McContainerGlobal.h"
#include "IMcNetworkMusicDao.h"
#include "IMcSonglistDao.h"
#include "McNetUtils.h"
#include "IMcMusicApi.h"
#include "McMusic.h"
#include "McAlbum.h"
#include "McArtist.h"
#include "McGlobal.h"

MC_STATIC(McNetworkMusicService)
mcRegisterComponent<McNetworkMusicService*, IMcNetworkMusicService*>("McNetworkMusicService", "networkMusicService");
MC_STATIC_END

struct McNetworkMusicServiceData {
	IMcNetworkMusicDao* networkMusicDao{ nullptr };
	IMcSonglistDao* songlistDao{ nullptr };

	QString musicSrc;
	QString keyword;
	int currentPage{ 1 };
};

McNetworkMusicService::McNetworkMusicService(QObject* parent)
	: QObject(parent)
	, d(new McNetworkMusicServiceData)
{
}

McNetworkMusicService::~McNetworkMusicService() {
}

IMcNetworkMusicDao* McNetworkMusicService::getNetworkMusicDao() const noexcept {
	return d->networkMusicDao;
}

void McNetworkMusicService::setNetworkMusicDao(IMcNetworkMusicDao* val) noexcept {
	d->networkMusicDao = val;
}

IMcSonglistDao* McNetworkMusicService::getSonglistDao() const noexcept {
	return d->songlistDao;
}

void McNetworkMusicService::setSonglistDao(IMcSonglistDao* val) noexcept {
	d->songlistDao = val;
}

void McNetworkMusicService::getNetworkMusics(const std::function<void(const QList<McMusic*>&)>& callback, const QString& musicSrc, const QString& keyword) noexcept {
	d->musicSrc = musicSrc;
	d->keyword = keyword;
	d->currentPage = 1;
	getNetworkMusics(callback);
}

void McNetworkMusicService::getLastPageMusic(const std::function<void(const QList<McMusic*>&)>& callback) noexcept {
	if (d->currentPage == 1)
		return;
	--d->currentPage;
	getNetworkMusics(callback);
}

void McNetworkMusicService::getNextPageMusic(const std::function<void(const QList<McMusic*>&)>& callback) noexcept {
	++d->currentPage;
	getNetworkMusics(callback);
}

void McNetworkMusicService::addToSongSheet(int songSheetId, const QList<McMusic*>& musics) noexcept {
	QList<McMusic*> copy;
	copy.reserve(musics.size());
	for (auto music : musics)
		copy.append(music->copy());
	QtConcurrent::run([this, songSheetId, copy] {
		for (auto music : copy) {
			if (music->getSongSrc() == MC_SONG_SRC_LOCAL && (music->getSongUrl().isEmpty() || d->networkMusicDao->getIdIfExistsForUrl(music)))
				continue;
			if (music->getSongSrc() != MC_SONG_SRC_LOCAL && d->networkMusicDao->getIdIfExists(music))
				continue;
			int maxMusicId = d->songlistDao->getMaxMusicId();
			int maxAlbumId = d->networkMusicDao->getMaxAlbumId();
			int maxArtistId = d->networkMusicDao->getMaxArtistId();
			if (maxMusicId < 0 || maxAlbumId < 0 || maxArtistId < 0)
				continue;
			McAlbum* album = music->getAlbum();
			if (album && !d->networkMusicDao->getIdIfExists(album)) {
				// 先添加album
				album->setId(maxAlbumId + 1);
				d->networkMusicDao->addAlbum(music->getAlbum());
			}
			// 再添加artist
			auto artists = music->getArtists();
			for (auto artist : artists) {
				if (!d->networkMusicDao->getIdIfExists(artist)) {
					artist->setId(++maxArtistId);
					d->networkMusicDao->addArtist(artist);
				}
			}
			// 最后添加music
			music->setId(maxMusicId + 1);
			d->networkMusicDao->addMusic(music);
			d->songlistDao->addToSongSheet(songSheetId, music);
		}
		qDeleteAll(copy);
	});
}

void McNetworkMusicService::getNetworkMusics(const std::function<void(const QList<McMusic*>&)>& callback) noexcept {
	static QFuture<void> futrue;
	if (futrue.isRunning())
		return;
	futrue = QtConcurrent::run([this, callback] {
		QList<McMusic*> musics;
		IMcMusicApi* api = McNetUtils::getMusicApi(d->musicSrc);
		if (!api)
			qDebug() << QString("music source '%1' does not exist").arg(d->musicSrc);
		int limit = 20;
		int offset = (d->currentPage - 1) * limit;
		musics = api->searchSong(d->keyword, limit, offset);
		callback(musics);
	});
}
