#pragma once

#include <QObject>

#include <McIoc/McGlobal.h>

class McArtist : public QObject {
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_id)
	Q_PROPERTY(QString artistTitle MEMBER m_artistTitle)
	MC_DECL_INIT(McArtist)
public:
	Q_INVOKABLE explicit McArtist(QObject *parent = nullptr) noexcept;

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
	int m_id;				//!< 唯一标识
	QString m_artistTitle;	//!< 歌手名
	QString m_artistId;
	QString m_artistMid;
	QString m_artistName;
	QString m_artistTitleHilight;
};

MC_DECL_METATYPE(McArtist)
