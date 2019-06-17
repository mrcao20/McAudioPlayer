#ifndef _MC_SONGLIST_SERVICE_H_
#define _MC_SONGLIST_SERVICE_H_

#include <QObject>
#include "IMcSonglistService.h"

#include "McBeanGlobal.h"

struct McSonglistServiceData;

class IMcSonglistDao;

class McSonglistService : public QObject, public IMcSonglistService {
	Q_OBJECT
	Q_PROPERTY(IMcSonglistDao *songlistDao READ getSonglistDao WRITE setSonglistDao USER true)
	MC_DECL_STATIC(McSonglistService)

public:
	Q_INVOKABLE explicit McSonglistService(QObject *parent = 0);
	~McSonglistService();

	IMcSonglistDao * getSonglistDao() const noexcept;
	void setSonglistDao(IMcSonglistDao * val) noexcept;

	QList<McMusic *> getMusics(int songSheetId) noexcept override;
	void addToSongSheet(int songSheetId, const QList<McMusic*>& musics) noexcept override;
	void removeFromSongSheet(int songSheetId, const QList<McMusic*>& musics) noexcept override;

private:
	QScopedPointer<McSonglistServiceData> d;
};

Q_DECLARE_METATYPE(McSonglistService*)

#endif // !_MC_SONGLIST_SERVICE_H_