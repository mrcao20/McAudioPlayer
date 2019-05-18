#ifndef _MC_SONG_SHEET_SERVICE_H_
#define _MC_SONG_SHEET_SERVICE_H_

#include <QObject>
#include "IMcSongSheetService.h"

#include "McBeanGlobal.h"

struct McSongSheetServiceData;

class IMcSongSheetDao;

class McSongSheetService : public QObject, public IMcSongSheetService {
	Q_OBJECT
	Q_PROPERTY(IMcSongSheetDao *songSheetDao READ getSongSheetDao WRITE setSongSheetDao USER true)
	MC_DECL_STATIC(McSongSheetService)

public:
	Q_INVOKABLE explicit McSongSheetService(QObject *parent = 0);
	~McSongSheetService();

	IMcSongSheetDao * getSongSheetDao() const noexcept;
	void setSongSheetDao(IMcSongSheetDao * val) noexcept;

	virtual QList<McSongSheet *> getSongSheets() noexcept override;

private:
	QScopedPointer<McSongSheetServiceData> d;
};

Q_DECLARE_METATYPE(McSongSheetService *)

#endif // !_MC_SONG_SHEET_SERVICE_H_