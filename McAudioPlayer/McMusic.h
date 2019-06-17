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
	Q_PROPERTY(QString songTitle MEMBER m_songTitle NOTIFY signal_songTitleChanged)
	Q_PROPERTY(QString songUrl MEMBER m_songUrl)
	Q_PROPERTY(McAlbum *album MEMBER m_album)
	Q_PROPERTY(QList<McArtist *> artists MEMBER m_artists)
	MC_DECL_STATIC(McMusic)

public:
	explicit McMusic(QObject *parent = 0);
	virtual ~McMusic();

	McMusic* copy() const noexcept;

	int getId() const { return m_id; }
	void setId(int val) { m_id = val; }

	QString getSongTitle() const { return m_songTitle; }
	void setSongTitle(const QString &val) { m_songTitle = val; }

	QString getSongUrl() const { return m_songUrl; }
	void setSongUrl(const QString &val) { m_songUrl = val; }

	McAlbum * getAlbum() const { return m_album; }
	void setAlbum(McAlbum * val) { m_album = val; }

	QList<McArtist *> getArtists() const { return m_artists; }
	void setArtists(const QList<McArtist *> &val) { m_artists = val; }
	void addArtist(McArtist *val) { m_artists.append(val); }

	QString getSongSrc() const { return m_songSrc; }
	void setSongSrc(const QString& val) { m_songSrc = val; }

	QString getSongId() const { return m_songId; }
	void setSongId(const QString& val) { m_songId = val; }

	QString getSongMid() const { return m_songMid; }
	void setSongMid(const QString& val) { m_songMid = val; }

	QString getSongName() const { return m_songName; }
	void setSongName(const QString& val) { m_songName = val; }

	QString getSongTitleHilight() const { return m_songTitleHilight; }
	void setSongTitleHilight(const QString& val) { m_songTitleHilight = val; }

signals:
	void signal_songTitleChanged();

private:
	int m_id;						// Ψһ��ʶ
	QString m_songTitle;			// ������
	QString m_songUrl;				// ��������
	McAlbum *m_album{ nullptr };	// ����ר��
	QList<McArtist *> m_artists;	// ����
	QString m_songSrc;				// ����Դ(���������Ķ���ymusic? qqmusic?)
	QString m_songId;				// ԭ����id
	QString m_songMid;				// ԭ����mid
	QString m_songName;
	QString m_songTitleHilight;
};

Q_DECLARE_METATYPE(McMusic*)

#endif // !_MC_MUSIC_H_