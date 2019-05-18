#include "McSongSheetController.h"

#include "McContainerGlobal.h"
#include "IMcSongSheetService.h"
#include "McJsonUtils.h"
#include "McRestResponse.h"
#include "McSongSheet.h"

MC_STATIC(McSongSheetController)
mcRegisterComponent<McSongSheetController*>("McSongSheetController", "songSheetController");
MC_STATIC_END

struct McSongSheetControllerData {
	IMcSongSheetService *songSheetService{ nullptr };
};

McSongSheetController::McSongSheetController(QObject *parent)
	: QObject(parent)
	, d(new McSongSheetControllerData)
{
}

McSongSheetController::~McSongSheetController(){
}

IMcSongSheetService *McSongSheetController::getSongSheetService() const noexcept {
	return d->songSheetService;
}

void McSongSheetController::setSongSheetService(IMcSongSheetService *val) noexcept {
	d->songSheetService = val;
}

QString McSongSheetController::getSongSheets() noexcept {
	QList<McSongSheet *> songSheets = d->songSheetService->getSongSheets();
	QString result = McJsonUtils::responseToJson(McRestResponse<QList<McSongSheet *>>::ok(songSheets));
	qDeleteAll(songSheets);
	return result;
}
