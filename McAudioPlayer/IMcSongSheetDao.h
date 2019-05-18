#ifndef _I_MC_SONG_SHEET_DAO_H_
#define _I_MC_SONG_SHEET_DAO_H_

#include <qglobal.h>
#include <QList>

class McSongSheet;

class IMcSongSheetDao {
public:
	virtual ~IMcSongSheetDao() = default;

	virtual QList<McSongSheet *> getSongSheets() noexcept = 0;
};

Q_DECLARE_METATYPE(IMcSongSheetDao*)

#endif // !_I_MC_SONG_SHEET_DAO_H_