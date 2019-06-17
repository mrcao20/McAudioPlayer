#ifndef _MC_ABSTRACT_MUSIC_H_
#define _MC_ABSTRACT_MUSIC_H_

#include <QObject>
#include "IMcMusicApi.h"

class McAbstractMusic : public QObject, public IMcMusicApi {
	Q_OBJECT

public:
	McAbstractMusic(QObject *parent = 0);
	virtual ~McAbstractMusic();

	QString getMusicUrl(const McMusic* music) noexcept override final;
	QList<McMusic*> searchSong(const QString& songName, int limit = 20, int offset = 0) noexcept override final;

protected:
	virtual QString getUrl(const McMusic* music) noexcept = 0;
	virtual void getMusics(QList<McMusic*>& musics, const QString& songName, int limit, int offset) noexcept = 0;

protected:
	QJsonValue getJsonValue(const QByteArray& json, const QString& nodeName) noexcept;
	QJsonValue getJsonValue(const QJsonObject& root, const QString& nodeName) noexcept;
	void getValue(QJsonObject& root, QJsonValue& nodeValue, QStringList& nodeList) noexcept;
};

#endif // !_MC_ABSTRACT_MUSIC_H_