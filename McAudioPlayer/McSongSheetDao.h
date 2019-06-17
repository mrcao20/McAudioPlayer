#ifndef _MC_SONG_SHEET_DAO_H_
#define _MC_SONG_SHEET_DAO_H_
#pragma execution_character_set("utf-8")

#include <QObject>
#include "IMcSongSheetDao.h"

#include "McBeanGlobal.h"

class McSongSheetDao : public QObject, public IMcSongSheetDao {
	Q_OBJECT
	MC_DECL_STATIC(McSongSheetDao)

public:
	Q_INVOKABLE explicit McSongSheetDao(QObject *parent = 0);
	~McSongSheetDao();

	QList<McSongSheet *> getSongSheets() noexcept override;
	void deleteSongSheet(McSongSheet* songSheet) noexcept override;
	void renameSongSheet(McSongSheet* songSheet) noexcept override;
	bool insert(McSongSheet* songSheet) noexcept override;
};

Q_DECLARE_METATYPE(McSongSheetDao*)

#endif // !_MC_SONG_SHEET_DAO_H_