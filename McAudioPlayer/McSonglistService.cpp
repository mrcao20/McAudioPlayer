#include "McSonglistService.h"

#include <QtConcurrent>

#include "McContainerGlobal.h"
#include "IMcSonglistDao.h"
#include "McMusic.h"

MC_STATIC(McSonglistService)
mcRegisterComponent<McSonglistService*, IMcSonglistService*>("McSonglistService", "songlistService");
MC_STATIC_END

struct McSonglistServiceData {
	IMcSonglistDao* songlistDao{ nullptr };
};

McSonglistService::McSonglistService(QObject *parent)
	: QObject(parent)
	, d(new McSonglistServiceData)
{
}

McSonglistService::~McSonglistService(){
}

IMcSonglistDao *McSonglistService::getSonglistDao() const noexcept {
	return d->songlistDao;
}

void McSonglistService::setSonglistDao(IMcSonglistDao * val) noexcept {
	d->songlistDao = val;
}

QList<McMusic *> McSonglistService::getMusics(int songSheetId) noexcept {
	QList<McMusic *> list = d->songlistDao->getMusics(songSheetId);
	return list;
}

void McSonglistService::addToSongSheet(int songSheetId, const QList<McMusic*>& musics) noexcept {
	QList<McMusic*> copy;
	copy.reserve(musics.size());
	for (auto music : musics)
		copy.append(music->copy());
	QtConcurrent::run([this, songSheetId, copy] {
		for (auto music : copy) {
			if (d->songlistDao->isExists(songSheetId, music))
				continue;
			d->songlistDao->addToSongSheet(songSheetId, music);
		}
		qDeleteAll(copy);
	});
}

void McSonglistService::removeFromSongSheet(int songSheetId, const QList<McMusic*>& musics) noexcept {
	QList<McMusic*> copy;
	copy.reserve(musics.size());
	for (auto music : musics)
		copy.append(music->copy());
	QtConcurrent::run([this, songSheetId, copy] {
		for (auto music : copy) {
			int songlistId = d->songlistDao->getSonglistId(songSheetId, music);
			if (songlistId <= 0)
				continue;	// �����ݿ��е���������Ϊ��ʱ����ʾ�����ڸ����ݣ�С����ʱ��ʾdao���ʳ���
			d->songlistDao->removeSonglist(songlistId);
		}
		qDeleteAll(copy);
	});
}
