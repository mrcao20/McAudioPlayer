#ifndef _MC_SONGLIST_CONTROLLER_H_
#define _MC_SONGLIST_CONTROLLER_H_

#include <QObject>

#include "McBeanGlobal.h"

struct McMusicControllerData;

class IMcMusicService;

class McMusicController : public QObject {
	Q_OBJECT
	Q_PROPERTY(IMcMusicService *musicService READ getMusicService WRITE setMusicService USER true)
	Q_CLASSINFO("Component", "Controller")
	MC_DECL_STATIC(McMusicController)

public:
	Q_INVOKABLE explicit McMusicController(QObject *parent = 0);
	~McMusicController();

	Q_INVOKABLE QString getMusics(int songSheetId) noexcept;

	IMcMusicService *getMusicService() const noexcept;
	void setMusicService(IMcMusicService *val) noexcept;

private:
	QScopedPointer<McMusicControllerData> d;
};

Q_DECLARE_METATYPE(McMusicController*)

#endif // !_MC_SONGLIST_CONTROLLER_H_