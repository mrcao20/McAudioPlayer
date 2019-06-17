#ifndef _I_MC_SONGLIST_SERVICE_H_
#define _I_MC_SONGLIST_SERVICE_H_

#include <qmetatype.h>
#include <QList>

class McMusic;

class IMcSonglistService {
public:
	virtual ~IMcSonglistService() = default;

	virtual QList<McMusic *> getMusics(int songSheetId) noexcept = 0;
	virtual void addToSongSheet(int songSheetId, const QList<McMusic*>& musics) noexcept = 0;
	virtual void removeFromSongSheet(int songSheetId, const QList<McMusic*>& musics) noexcept = 0;
};

Q_DECLARE_METATYPE(IMcSonglistService*)

#endif // !_I_MC_SONGLIST_SERVICE_H_