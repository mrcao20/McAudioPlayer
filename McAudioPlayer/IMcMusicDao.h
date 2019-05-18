#ifndef _I_MC_MUSIC_DAO_H_
#define _I_MC_MUSIC_DAO_H_

#include <qmetatype.h>
#include <QList>

class McMusic;

class IMcMusicDao {
public:
	virtual ~IMcMusicDao() = default;

	virtual QList<McMusic *> getMusics(int songSheetId) noexcept = 0;
};

Q_DECLARE_METATYPE(IMcMusicDao*)

#endif // !_I_MC_MUSIC_DAO_H_