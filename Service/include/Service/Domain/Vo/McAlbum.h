#pragma once

#include <QObject>

#include <McIoc/McGlobal.h>

class McAlbum : public QObject {
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_id)
	Q_PROPERTY(QString albumTitle MEMBER m_albumTitle)
	MC_DECL_INIT(McAlbum)
public:
	Q_INVOKABLE explicit McAlbum(QObject *parent = nullptr) noexcept;

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
	int m_id;				//!< 唯一标识
	QString m_albumTitle;	//!< 专辑名
	QString m_albumId;
	QString m_albumMid;
	QString m_albumName;
	QString m_albumTitleHilight;
};

MC_DECL_METATYPE(McAlbum)
