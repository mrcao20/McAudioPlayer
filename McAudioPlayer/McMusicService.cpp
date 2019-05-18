#include "McMusicService.h"

#include "McContainerGlobal.h"
#include "IMcMusicDao.h"

MC_STATIC(McMusicService)
mcRegisterComponent<McMusicService*, IMcMusicService*>("McMusicService", "musicService");
MC_STATIC_END

struct McMusicServiceData {
	IMcMusicDao *musicDao{ nullptr };
};

McMusicService::McMusicService(QObject *parent)
	: QObject(parent)
	, d(new McMusicServiceData)
{
}

McMusicService::~McMusicService(){
}

IMcMusicDao *McMusicService::getMusicDao() const noexcept {
	return d->musicDao;
}

void McMusicService::setMusicDao(IMcMusicDao * val) noexcept {
	d->musicDao = val;
}

QList<McMusic *> McMusicService::getMusics(int songSheetId) noexcept {
	QList<McMusic *> list = d->musicDao->getMusics(songSheetId);
	return list;
}
