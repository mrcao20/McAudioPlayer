#ifndef _MC_ARTIST_H_
#define _MC_ARTIST_H_

#include <QObject>

#include "McBeanGlobal.h"

class McArtist : public QObject {
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_id)
	Q_PROPERTY(QString artistName MEMBER m_artistName)
	MC_DECL_STATIC(McArtist)

public:
	explicit McArtist(QObject *parent = 0);

	int getId() const { return m_id; }
	void setId(int val) { m_id = val; }

	QString getArtistName() const { return m_artistName; }
	void setArtistName(const QString &val) { m_artistName = val; }

private:
	int m_id;				// 唯一标识
	QString m_artistName;	// 歌手名
};

Q_DECLARE_METATYPE(McArtist*)

#endif // !_MC_ARTIST_H_