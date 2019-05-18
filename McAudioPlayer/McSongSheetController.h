#ifndef _MC_SONG_SHEET_CONTROLLER_H_
#define _MC_SONG_SHEET_CONTROLLER_H_

#include <QObject>

#include "McBeanGlobal.h"

struct McSongSheetControllerData;

class IMcSongSheetService;

class McSongSheetController : public QObject {
	Q_OBJECT
	Q_PROPERTY(IMcSongSheetService *songSheetService READ getSongSheetService WRITE setSongSheetService USER true)
	Q_CLASSINFO("Component", "Controller")
	MC_DECL_STATIC(McSongSheetController)

public:
	Q_INVOKABLE explicit McSongSheetController(QObject *parent = 0);
	~McSongSheetController();

	Q_INVOKABLE QString getSongSheets() noexcept;

	IMcSongSheetService *getSongSheetService() const noexcept;
	void setSongSheetService(IMcSongSheetService *val) noexcept;

private:
	QScopedPointer<McSongSheetControllerData> d;
};

Q_DECLARE_METATYPE(McSongSheetController *)

#endif // _MC_SONG_SHEET_CONTROLLER_H_