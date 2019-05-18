#include "McMusicController.h"

#include "McContainerGlobal.h"
#include "IMcMusicService.h"
#include "McMusic.h"
#include "McJsonUtils.h"
#include "McRestResponse.h"

MC_STATIC(McMusicController)
mcRegisterComponent<McMusicController*>("McMusicController", "musicController");
MC_STATIC_END

struct McMusicControllerData {
	IMcMusicService *musicService{ nullptr };
};

McMusicController::McMusicController(QObject *parent)
	: QObject(parent)
	, d(new McMusicControllerData)
{
}

McMusicController::~McMusicController(){
}

QString McMusicController::getMusics(int songSheetId) noexcept {
	QList<McMusic *> musics = d->musicService->getMusics(songSheetId);
	QString result = McJsonUtils::responseToJson(McRestResponse<QList<McMusic *>>::ok(musics));
	qDeleteAll(musics);
	return result;
}

IMcMusicService *McMusicController::getMusicService() const noexcept {
	return d->musicService;
}

void McMusicController::setMusicService(IMcMusicService *val) noexcept {
	d->musicService = val;
}
