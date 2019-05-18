#ifndef _MC_ALBUM_H_
#define _MC_ALBUM_H_

#include <QObject>

#include "McBeanGlobal.h"

class McAlbum : public QObject {
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_id)
	Q_PROPERTY(QString albumName MEMBER m_albumName)
	MC_DECL_STATIC(McAlbum)

public:
	explicit McAlbum(QObject *parent = 0);

	int getId() const { return m_id; }
	void setId(int val) { m_id = val; }

	QString getAlbumName() const { return m_albumName; }
	void setAlbumName(const QString &val) { m_albumName = val; }

private:
	int m_id;				// 唯一标识
	QString m_albumName;	// 专辑名
};

Q_DECLARE_METATYPE(McAlbum*)

#endif // !_MC_ALBUM_H_