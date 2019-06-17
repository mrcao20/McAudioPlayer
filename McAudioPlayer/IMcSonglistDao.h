#ifndef _I_MC_MUSIC_DAO_H_
#define _I_MC_MUSIC_DAO_H_

#include <qmetatype.h>
#include <QList>

class McMusic;

class IMcSonglistDao {
public:
	virtual ~IMcSonglistDao() = default;

	virtual QList<McMusic *> getMusics(int songSheetId) noexcept = 0;
	virtual bool isExists(int songSheetId, McMusic* music) noexcept = 0;
	virtual void addToSongSheet(int songSheetId, McMusic* music) noexcept = 0;
	// �õ�t_songlist_info���е�id�ֶ�
	virtual int getSonglistId(int songSheetId, McMusic* music) noexcept = 0;
	// ��t_songlist_info�����Ƴ�idΪ'id'������
	virtual void removeSonglist(int id) noexcept = 0;
	virtual int getMaxMusicId() noexcept = 0;
};

Q_DECLARE_METATYPE(IMcSonglistDao*)

#endif // !_I_MC_MUSIC_DAO_H_