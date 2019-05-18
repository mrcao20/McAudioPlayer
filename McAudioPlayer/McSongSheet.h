#ifndef _MC_SONG_SHEET_H_
#define _MC_SONG_SHEET_H_

#include <QObject>

class McSongSheet : public QObject {
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_id)
	Q_PROPERTY(QString title MEMBER m_title)
	Q_PROPERTY(QString songSheet MEMBER m_songSheet)

public:
	explicit McSongSheet(QObject *parent = 0)
		: QObject(parent)
	{}

	int getId() const { return m_id; }
	void setId(int val) { m_id = val; }

	QString getTitle() const { return m_title; }
	void setTitle(const QString &val) { m_title = val; }

	QString getSongSheet() const { return m_songSheet; }
	void setSongSheet(const QString &val) { m_songSheet = val; }

private:
	int m_id;
	QString m_title;
	QString m_songSheet;
};

#endif // !_MC_SONG_SHEET_H_