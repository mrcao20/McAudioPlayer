#ifndef _MC_SONG_SHEET_H_
#define _MC_SONG_SHEET_H_

#include <QObject>

#include "McBeanGlobal.h"

class McSongSheet : public QObject {
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_id NOTIFY signal_idChanged)
	Q_PROPERTY(QString title MEMBER m_title)
	Q_PROPERTY(QString songSheet MEMBER m_songSheet NOTIFY signal_songSheetChanged)
	MC_DECL_STATIC(McSongSheet)

public:
	explicit McSongSheet(QObject* parent = 0);

	McSongSheet* copy() noexcept {
		McSongSheet* other = new McSongSheet();
		other->m_id = m_id;
		other->m_title = m_title;
		other->m_songSheet = m_songSheet;
		return other;
	}

	int getId() const { return m_id; }
	void setId(int val) { m_id = val; }

	QString getTitle() const { return m_title; }
	void setTitle(const QString &val) { m_title = val; }

	QString getSongSheet() const { return m_songSheet; }
	void setSongSheet(const QString &val) { m_songSheet = val; }

signals:
	void signal_idChanged();
	void signal_songSheetChanged();

private:
	int m_id;
	QString m_title;
	QString m_songSheet;
};

Q_DECLARE_METATYPE(McSongSheet*)

#endif // !_MC_SONG_SHEET_H_