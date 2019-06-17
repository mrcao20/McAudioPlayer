#include "McPlaylistService.h"

#include <qurl.h>
#include <QtConcurrent>
#include <qdebug.h>

#include "McContainerGlobal.h"
#include "IMcPlaylistDao.h"
#include "McMusic.h"
#include "McNetUtils.h"
#include "IMcMusicApi.h"
#include "McGlobal.h"

MC_STATIC(McPlaylistService)
mcRegisterComponent<McPlaylistService*, IMcPlaylistService*>("McPlaylistService", "playlistService");
MC_STATIC_END

struct McPlaylistServiceData {
	IMcPlaylistDao *playlistDao{ nullptr };
};

McPlaylistService::McPlaylistService(QObject *parent)
	: QObject(parent)
	, d(new McPlaylistServiceData)
{
}

McPlaylistService::~McPlaylistService(){
}

IMcPlaylistDao *McPlaylistService::getPlaylistDao() const noexcept {
	return d->playlistDao;
}

void McPlaylistService::setPlaylistDao(IMcPlaylistDao *val) noexcept {
	d->playlistDao = val;
}

QList<McMusic *> McPlaylistService::getPlaylist() noexcept {
	QList<McMusic *> musics = d->playlistDao->getPlaylist();
	return musics;
}

void McPlaylistService::getSongUrl(McMusic *music) noexcept {
	d->playlistDao->getSongUrl(music);
	if (canConnecting(music->getSongUrl()))
		return;
	music->setSongUrl("");
	QString songSrc = music->getSongSrc();
	if (songSrc.isEmpty()) {
		d->playlistDao->getMusicDetail(music);
		songSrc = music->getSongSrc();
	}
	if (songSrc == MC_SONG_SRC_LOCAL) {
		qInfo() << QString("本地音乐'%1'不存在").arg(music->getSongTitle());
		return;
	}
	IMcMusicApi *api = McNetUtils::getMusicApi(songSrc);
	if (!api) {
		qDebug() << QString("无法获取音乐源为'%1'的api对象").arg(music->getSongSrc());
		return;
	}
	QString url = api->getMusicUrl(music);
	music->setSongUrl(url);
	d->playlistDao->updateMusicUrl(music);
}

QList<McMusic*> McPlaylistService::addMusics(const QList<McMusic*>& musics, int songSheetId) noexcept {
	static QMutex mtx;
	QList<McMusic*> ms;
	for (auto music : musics) {
		ms.append(music->copy());
	}
	QtConcurrent::run([this, ms, songSheetId] {
		QMutexLocker locker(&mtx);
		if (!d->playlistDao->deleteAll())	// 发生错误
			return;
		d->playlistDao->addMusics(ms, songSheetId);
	});
	return ms;
}

bool McPlaylistService::canConnecting(const QString &uri) noexcept {
	if (uri.isEmpty())
		return false;
	QUrl url;
	if (uri.startsWith("http"))
		url = QUrl(uri);
	else {
		url = QUrl::fromLocalFile(uri);
	}
	return McNetUtils::canConnecting(url);
}
