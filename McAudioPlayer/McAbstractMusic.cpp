#include "McAbstractMusic.h"

#include <qurl.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <QJsonArray>
#include <QRegularExpression>
#include <qdebug.h>

#include "McNetUtils.h"
#include "McMusic.h"

McAbstractMusic::McAbstractMusic(QObject *parent)
	: QObject(parent)
{
}

McAbstractMusic::~McAbstractMusic(){
}

QString McAbstractMusic::getMusicUrl(const McMusic* music) noexcept {
	QString musicUrl = getUrl(music);
	if (!McNetUtils::canConnecting(QUrl(musicUrl)))
		musicUrl = "";
	return musicUrl;
}

QList<McMusic*> McAbstractMusic::searchSong(const QString& songName, int limit, int offset) noexcept {
	QList<McMusic*> musics;
	musics.reserve(limit);
	getMusics(musics, songName, limit, offset);
	int id = -1;
	for (auto music : musics)
		music->setId(id--);
	return musics;
}

/*
����ָ����nodeName��QByteArray���ҳ���һ������������QJsonValue
*/
QJsonValue McAbstractMusic::getJsonValue(const QByteArray& json, const QString& nodeName) noexcept {
	QJsonValue nodeValue;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(json);
	if (jsonDocument.isEmpty()) {
		qInfo() << "audio link error, json value not found";
		return nodeValue;
	}
	QJsonObject root = jsonDocument.object();
	nodeValue = getJsonValue(root, nodeName);
	return nodeValue;
}

/*
����nodeName��QJsonObject���ҳ���һ������������QJsonValue
*/
QJsonValue McAbstractMusic::getJsonValue(const QJsonObject& root, const QString& nodeName) noexcept {
	QJsonValue nodeValue;
	QStringList nodeList = nodeName.split(QRegularExpression("\\."), QString::SkipEmptyParts);
	QJsonObject jsonObject = root;
	getValue(jsonObject, nodeValue, nodeList);
	return nodeValue;
}

/*
������ָ����nodelist���ص�һ������������nodeValue
*/
void McAbstractMusic::getValue(QJsonObject& root, QJsonValue& nodeValue, QStringList& nodeList) noexcept {
	QStringList list = nodeList;
	for (int i = 0; i < nodeList.size(); i++) {
		nodeValue = root.value(list.takeFirst());   // ��������ڸ�node����nodeValue��typeΪUndefined
		if (nodeValue.type() != QJsonValue::Object && nodeValue.type() != QJsonValue::Array)
			break;
		if (i == nodeList.size() - 1)
			break;
		if (nodeValue.type() == QJsonValue::Object) {
			root = nodeValue.toObject();
			continue;
		}
		QJsonArray array = nodeValue.toArray();
		for (auto itr = array.begin(); itr != array.end(); itr++) {
			root = (*itr).toObject();
			getValue(root, nodeValue, list);
			if (!nodeValue.isUndefined() && !nodeValue.isNull())
				return;
		}
	}
}
