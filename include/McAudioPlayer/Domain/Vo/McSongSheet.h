#pragma once

#include <QObject>

#include <McIoc/McGlobal.h>

class McSongSheet : public QObject {
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_id)
	Q_PROPERTY(QString title MEMBER m_title)
	Q_PROPERTY(QString songSheet MEMBER m_songSheet)
    MC_DECL_INIT(McSongSheet)
public:
	Q_INVOKABLE explicit McSongSheet(QObject *parent = nullptr) noexcept;

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

MC_DECL_METATYPE(McSongSheet)
