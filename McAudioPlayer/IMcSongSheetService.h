#ifndef _I_MC_SONG_SHEET_SERVICE_H_
#define _I_MC_SONG_SHEET_SERVICE_H_

#include <qmetatype.h>
#include <QList>

class McSongSheet;

class IMcSongSheetService {
public:
	virtual ~IMcSongSheetService() = default;

	virtual QList<McSongSheet *> getSongSheets() noexcept = 0;
};

Q_DECLARE_METATYPE(IMcSongSheetService*)

#endif // _I_MC_SONG_SHEET_SERVICE_H_
