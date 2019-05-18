#ifndef _I_MC_MUSIC_SERVICE_H_
#define _I_MC_MUSIC_SERVICE_H_

#include <qmetatype.h>
#include <QList>

class McMusic;

class IMcMusicService {
public:
	virtual ~IMcMusicService() = default;

	virtual QList<McMusic *> getMusics(int songSheetId) noexcept = 0;
};

Q_DECLARE_METATYPE(IMcMusicService*)

#endif // !_I_MC_MUSIC_SERVICE_H_