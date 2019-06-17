#include "McSongSheetService.h"

#include <QtConcurrent>

#include "McContainerGlobal.h"
#include "IMcSongSheetDao.h"
#include "IMcNetworkMusicService.h"
#include "McSongSheet.h"
#include "McMusic.h"
#include "McGlobal.h"

MC_STATIC(McSongSheetService)
mcRegisterComponent<McSongSheetService*, IMcSongSheetService*>("McSongSheetService", "songSheetService");
MC_STATIC_END

struct McSongSheetServiceData {
	IMcSongSheetDao *songSheetDao{ nullptr };
	IMcNetworkMusicService* networkMusicService{ nullptr };
};

McSongSheetService::McSongSheetService(QObject *parent)
	: QObject(parent)
	, d(new McSongSheetServiceData)
{
}

McSongSheetService::~McSongSheetService(){
}

IMcSongSheetDao *McSongSheetService::getSongSheetDao() const noexcept {
	return d->songSheetDao;
}

void McSongSheetService::setSongSheetDao(IMcSongSheetDao * val) noexcept {
	d->songSheetDao = val;
}

IMcNetworkMusicService* McSongSheetService::getNetworkMusicService() const noexcept {
	return d->networkMusicService;
}

void McSongSheetService::setNetworkMusicService(IMcNetworkMusicService* val) noexcept {
	d->networkMusicService = val;
}

QList<McSongSheet *> McSongSheetService::getSongSheets() noexcept {
	QList<McSongSheet *> songSheets = d->songSheetDao->getSongSheets();
	return songSheets;
}

void McSongSheetService::deleteSongSheet(McSongSheet* songSheet) noexcept {
	McSongSheet* copy = songSheet->copy();
	QtConcurrent::run([this, copy] {
		d->songSheetDao->deleteSongSheet(copy);
		copy->deleteLater();
	});
}

bool McSongSheetService::renameSongSheet(McSongSheet* songSheet, const QString& newName, const QList<McSongSheet*>& songSheets) noexcept {
	if (newName.contains("'")) {
		qInfo() << "song sheet name cannot contains '";
		return false;
	}
	if (isContainsName(newName, songSheets)) {
		qInfo() << QString("repeated the name of '%1'").arg(newName);
		return false;
	}
	songSheet->setSongSheet(newName);
	d->songSheetDao->renameSongSheet(songSheet);
	return true;
}

McSongSheet* McSongSheetService::createSongSheet(const QString& title, const QString& newName, const QList<McSongSheet*>& songSheets) noexcept {
	McSongSheet* songSheet = new McSongSheet();
	songSheet->setId(getMaxId(songSheets) + 1);
	songSheet->setTitle(title);
	QString name = newName;
	int i = 1;
	while (isContainsName(name, songSheets))
		name += QString::number(i++);
	songSheet->setSongSheet(name);
	if (!d->songSheetDao->insert(songSheet)) {
		songSheet->deleteLater();
		return nullptr;
	}
	return songSheet;
}

QList<McMusic*> McSongSheetService::addLocalMusics(int songSheetId, const QList<QUrl>& filePaths) noexcept {
	QList<McMusic*> musics;
	for (auto url : filePaths) {
		McMusic* music = new McMusic();
		QString songName = QFileInfo(url.toLocalFile()).baseName();
		music->setId(-1);
		music->setSongTitle(songName);
		music->setSongUrl(url.toLocalFile());
		music->setSongSrc(MC_SONG_SRC_LOCAL);
		music->setSongName(songName);
		music->setSongTitleHilight(songName);
		musics.append(music);
	}
	d->networkMusicService->addToSongSheet(songSheetId, musics);
	return musics;
}

int McSongSheetService::getMaxId(const QList<McSongSheet*>& songSheets) const noexcept {
	int id = 0;	// 默认为0，表示没有歌单
	for (auto songSheet : songSheets)
		if (songSheet->getId() > id)
			id = songSheet->getId();
	return id;
}

bool McSongSheetService::isContainsName(const QString& name, const QList<McSongSheet*>& songSheets) noexcept {
	for (auto ss : songSheets)
		if (ss->getSongSheet() == name)
			return true;
	return false;
}
