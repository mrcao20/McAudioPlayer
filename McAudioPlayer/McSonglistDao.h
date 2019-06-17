#ifndef _MC_MUSIC_DAO_H_
#define _MC_MUSIC_DAO_H_

#include <QObject>
#include "IMcSonglistDao.h"

#include "McBeanGlobal.h"

class McSonglistDao : public QObject, public IMcSonglistDao {
	Q_OBJECT
	MC_DECL_STATIC(McSonglistDao)

public:
	Q_INVOKABLE explicit McSonglistDao(QObject *parent = 0);
	~McSonglistDao();

	QList<McMusic *> getMusics(int songSheetId) noexcept override;
	bool isExists(int songSheetId, McMusic* music) noexcept override;
	void addToSongSheet(int songSheetId, McMusic* music) noexcept override;
	int getSonglistId(int songSheetId, McMusic* music) noexcept override;
	void removeSonglist(int id) noexcept override;
	int getMaxMusicId() noexcept override;

private:
	int getMaxSonglistId() noexcept;
};

Q_DECLARE_METATYPE(McSonglistDao*)

#endif // !_MC_MUSIC_DAO_H_