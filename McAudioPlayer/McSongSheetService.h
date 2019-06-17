#ifndef _MC_SONG_SHEET_SERVICE_H_
#define _MC_SONG_SHEET_SERVICE_H_

#include <QObject>
#include "IMcSongSheetService.h"

#include "McBeanGlobal.h"

struct McSongSheetServiceData;

class IMcSongSheetDao;
class IMcNetworkMusicService;

class McSongSheetService : public QObject, public IMcSongSheetService {
	Q_OBJECT
	Q_PROPERTY(IMcSongSheetDao *songSheetDao READ getSongSheetDao WRITE setSongSheetDao USER true)
	Q_PROPERTY(IMcNetworkMusicService* networkMusicService READ getNetworkMusicService WRITE setNetworkMusicService USER true)
	MC_DECL_STATIC(McSongSheetService)

public:
	Q_INVOKABLE explicit McSongSheetService(QObject *parent = 0);
	~McSongSheetService();

	IMcSongSheetDao * getSongSheetDao() const noexcept;
	void setSongSheetDao(IMcSongSheetDao * val) noexcept;

	IMcNetworkMusicService* getNetworkMusicService() const noexcept;
	void setNetworkMusicService(IMcNetworkMusicService* val) noexcept;

	QList<McSongSheet *> getSongSheets() noexcept override;
	void deleteSongSheet(McSongSheet* songSheet) noexcept override;
	bool renameSongSheet(McSongSheet* songSheet, const QString& newName, const QList<McSongSheet*>& songSheets) noexcept override;
	McSongSheet* createSongSheet(const QString& title, const QString& newName, const QList<McSongSheet*>& songSheets) noexcept override;
	QList<McMusic*> addLocalMusics(int songSheetId, const QList<QUrl>& filePaths) noexcept override;

private:
	int getMaxId(const QList<McSongSheet*>& songSheets) const noexcept;
	bool isContainsName(const QString& name, const QList<McSongSheet*>& songSheets) noexcept;

private:
	QScopedPointer<McSongSheetServiceData> d;
};

Q_DECLARE_METATYPE(McSongSheetService *)

#endif // !_MC_SONG_SHEET_SERVICE_H_