#ifndef _MC_MUSIC_SERVICE_H_
#define _MC_MUSIC_SERVICE_H_

#include <QObject>
#include "IMcMusicService.h"

#include "McBeanGlobal.h"

struct McMusicServiceData;

class IMcMusicDao;

class McMusicService : public QObject, public IMcMusicService {
	Q_OBJECT
	Q_PROPERTY(IMcMusicDao *musicDao READ getMusicDao WRITE setMusicDao USER true)
	MC_DECL_STATIC(McMusicService)

public:
	Q_INVOKABLE explicit McMusicService(QObject *parent = 0);
	~McMusicService();

	IMcMusicDao * getMusicDao() const noexcept;
	void setMusicDao(IMcMusicDao * val) noexcept;

	QList<McMusic *> getMusics(int songSheetId) noexcept override;

private:
	QScopedPointer<McMusicServiceData> d;
};

Q_DECLARE_METATYPE(McMusicService*)

#endif // !_MC_MUSIC_SERVICE_H_