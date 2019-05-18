#ifndef _MC_MUSIC_DAO_H_
#define _MC_MUSIC_DAO_H_

#include <QObject>
#include "IMcMusicDao.h"

#include "McBeanGlobal.h"

class McMusicDao : public QObject, public IMcMusicDao {
	Q_OBJECT
	MC_DECL_STATIC(McMusicDao)

public:
	Q_INVOKABLE explicit McMusicDao(QObject *parent = 0);
	~McMusicDao();

	QList<McMusic *> getMusics(int songSheetId) noexcept override;
};

Q_DECLARE_METATYPE(McMusicDao*)

#endif // !_MC_MUSIC_DAO_H_