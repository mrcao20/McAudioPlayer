#ifndef _MC_MUSIC_H_
#define _MC_MUSIC_H_

#include <QObject>

#include <QList>

#include "McBeanGlobal.h"

class McAlbum;
class McArtist;

class McMusic : public QObject {
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_id)
	Q_PROPERTY(QString songName MEMBER m_songName)
	Q_PROPERTY(McAlbum *album MEMBER m_album)
	Q_PROPERTY(QList<McArtist *> artists MEMBER m_artists)
	MC_DECL_STATIC(McMusic)

public:
	explicit McMusic(QObject *parent = 0);
	~McMusic();

	int getId() const { return m_id; }
	void setId(int val) { m_id = val; }

	QString getSongName() const { return m_songName; }
	void setSongName(const QString &val) { m_songName = val; }

	McAlbum * getAlbum() const { return m_album; }
	void setAlbum(McAlbum * val) { m_album = val; }

	QList<McArtist *> getArtists() const { return m_artists; }
	void setArtists(const QList<McArtist *> &val) { m_artists = val; }
	void addArtist(McArtist *val) { m_artists.append(val); }

private:
	int m_id;						// 唯一标识
	QString m_songName;				// 歌曲名
	McAlbum *m_album{ nullptr };	// 所属专辑
	QList<McArtist *> m_artists;	// 歌手
};

Q_DECLARE_METATYPE(McMusic*)

#endif // !_MC_MUSIC_H_