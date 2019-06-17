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
根据指定的nodeName从QByteArray中找出第一个满足条件的QJsonValue
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
根据nodeName从QJsonObject中找出第一个满足条件的QJsonValue
*/
QJsonValue McAbstractMusic::getJsonValue(const QJsonObject& root, const QString& nodeName) noexcept {
	QJsonValue nodeValue;
	QStringList nodeList = nodeName.split(QRegularExpression("\\."), QString::SkipEmptyParts);
	QJsonObject jsonObject = root;
	getValue(jsonObject, nodeValue, nodeList);
	return nodeValue;
}

/*
根据所指定的nodelist返回第一个满足条件的nodeValue
*/
void McAbstractMusic::getValue(QJsonObject& root, QJsonValue& nodeValue, QStringList& nodeList) noexcept {
	QStringList list = nodeList;
	for (int i = 0; i < nodeList.size(); i++) {
		nodeValue = root.value(list.takeFirst());   // 如果不存在该node，则nodeValue的type为Undefined
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
