#ifndef _MC_ARTIST_H_
#define _MC_ARTIST_H_

#include <QObject>

#include "McBeanGlobal.h"

class McArtist : public QObject {
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_id)
	Q_PROPERTY(QString artistTitle MEMBER m_artistTitle)
	MC_DECL_STATIC(McArtist)

public:
	explicit McArtist(QObject *parent = 0);

	inline McArtist* copy() const noexcept {
		McArtist* other = new McArtist();
		other->m_id = m_id;
		other->m_artistTitle = m_artistTitle;
		other->m_artistId = m_artistId;
		other->m_artistMid = m_artistMid;
		other->m_artistName = m_artistName;
		other->m_artistTitleHilight = m_artistTitleHilight;
		return other;
	}

	int getId() const { return m_id; }
	void setId(int val) { m_id = val; }

	QString getArtistTitle() const { return m_artistTitle; }
	void setArtistTitle(const QString &val) { m_artistTitle = val; }

	QString getArtistId() const { return m_artistId; }
	void setArtistId(const QString& val) { m_artistId = val; }

	QString getArtistMid() const { return m_artistMid; }
	void setArtistMid(const QString& val) { m_artistMid = val; }

	QString getArtistName() const { return m_artistName; }
	void setArtistName(const QString& val) { m_artistName = val; }

	QString getArtistTitleHilight() const { return m_artistTitleHilight; }
	void setArtistTitleHilight(const QString& val) { m_artistTitleHilight = val; }

private:
	int m_id;				// 唯一标识
	QString m_artistTitle;	// 歌手名
	QString m_artistId;
	QString m_artistMid;
	QString m_artistName;
	QString m_artistTitleHilight;
};

Q_DECLARE_METATYPE(McArtist*)

#endif // !_MC_ARTIST_H_