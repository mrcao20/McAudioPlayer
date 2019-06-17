#ifndef _MC_ALBUM_H_
#define _MC_ALBUM_H_

#include <QObject>

#include "McBeanGlobal.h"

class McAlbum : public QObject {
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_id)
	Q_PROPERTY(QString albumTitle MEMBER m_albumTitle)
	MC_DECL_STATIC(McAlbum)

public:
	explicit McAlbum(QObject *parent = 0);

	inline McAlbum* copy() const noexcept {
		McAlbum* other = new McAlbum();
		other->m_id = m_id;
		other->m_albumTitle = m_albumTitle;
		other->m_albumId = m_albumId;
		other->m_albumMid = m_albumMid;
		other->m_albumName = m_albumName;
		other->m_albumTitleHilight = m_albumTitleHilight;
		return other;
	}

	int getId() const { return m_id; }
	void setId(int val) { m_id = val; }

	QString getAlbumTitle() const { return m_albumTitle; }
	void setAlbumTitle(const QString &val) { m_albumTitle = val; }

	QString getAlbumId() const { return m_albumId; }
	void setAlbumId(const QString& val) { m_albumId = val; }

	QString getAlbumMid() const { return m_albumMid; }
	void setAlbumMid(const QString& val) { m_albumMid = val; }

	QString getAlbumName() const { return m_albumName; }
	void setAlbumName(const QString& val) { m_albumName = val; }

	QString getAlbumTitleHilight() const { return m_albumTitleHilight; }
	void setAlbumTitleHilight(const QString& val) { m_albumTitleHilight = val; }

private:
	int m_id;				// 唯一标识
	QString m_albumTitle;	// 专辑名
	QString m_albumId;
	QString m_albumMid;
	QString m_albumName;
	QString m_albumTitleHilight;
};

Q_DECLARE_METATYPE(McAlbum*)

#endif // !_MC_ALBUM_H_