#ifndef _I_MC_SONG_SHEET_SERVICE_H_
#define _I_MC_SONG_SHEET_SERVICE_H_

#include <qmetatype.h>
#include <QList>

class McSongSheet;
class McMusic;

class IMcSongSheetService {
public:
	virtual ~IMcSongSheetService() = default;

	virtual QList<McSongSheet *> getSongSheets() noexcept = 0;
	virtual void deleteSongSheet(McSongSheet* songSheet) noexcept = 0;
	virtual bool renameSongSheet(McSongSheet* songSheet, const QString& newName, const QList<McSongSheet*>& songSheets) noexcept = 0;
	virtual McSongSheet* createSongSheet(const QString& title, const QString& newName, const QList<McSongSheet*>& songSheets) noexcept = 0;
	virtual QList<McMusic*> addLocalMusics(int songSheetId, const QList<QUrl>& filePaths) noexcept = 0;
};

Q_DECLARE_METATYPE(IMcSongSheetService*)

#endif // _I_MC_SONG_SHEET_SERVICE_H_
