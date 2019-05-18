#include "McSongSheetService.h"

#include "McContainerGlobal.h"
#include "IMcSongSheetDao.h"

MC_STATIC(McSongSheetService)
mcRegisterComponent<McSongSheetService*, IMcSongSheetService*>("McSongSheetService", "songSheetService");
MC_STATIC_END

struct McSongSheetServiceData {
	IMcSongSheetDao *songSheetDao{ nullptr };
	
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

QList<McSongSheet *> McSongSheetService::getSongSheets() noexcept {
	QList<McSongSheet *> songSheets = d->songSheetDao->getSongSheets();
	return songSheets;
}
