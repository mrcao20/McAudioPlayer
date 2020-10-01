#pragma once

#include <QObject>

#include <QList>
#include <QUrl>

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McAlbum);
MC_FORWARD_DECL_CLASS(McArtist);

class McMusic : public QObject {
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_id)
	Q_PROPERTY(QString songTitle MEMBER m_songTitle)
	Q_PROPERTY(QUrl songUrl MEMBER m_songUrl)
	Q_PROPERTY(McAlbumPtr album MEMBER m_album)
	Q_PROPERTY(QList<McArtistPtr> artists MEMBER m_artists)
	MC_DECL_INIT(McMusic)
public:
	Q_INVOKABLE explicit McMusic(QObject *parent = nullptr) noexcept;
	virtual ~McMusic() noexcept;

	int getId() const { return m_id; }
	void setId(int val) { m_id = val; }

	QString getSongTitle() const { return m_songTitle; }
	void setSongTitle(const QString &val) { m_songTitle = val; }

	QUrl getSongUrl() const { return m_songUrl; }
	void setSongUrl(const QUrl &val) { m_songUrl = val; }

	McAlbumPtr getAlbum() const { return m_album; }
	void setAlbum(McAlbumConstPtrRef val) { m_album = val; }

	QList<McArtistPtr> getArtists() const { return m_artists; }
	void setArtists(const QList<McArtistPtr> &val) { m_artists = val; }
	void addArtist(McArtistConstPtrRef val) { m_artists.append(val); }

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

private:
	int m_id;						//!< 唯一标识
	QString m_songTitle;			//!< 歌曲名
	QUrl m_songUrl;                 //!< 歌曲链接
	McAlbumPtr m_album;             //!< 所属专辑
	QList<McArtistPtr> m_artists;	//!< 歌手
	QString m_songSrc;				//!< 音乐源(音乐来自哪儿，ymusic? qqmusic?)
	QString m_songId;				//!< 原厂商id
	QString m_songMid;				//!< 原厂商mid
	QString m_songName;
	QString m_songTitleHilight;
};

MC_DECL_METATYPE(McMusic)
