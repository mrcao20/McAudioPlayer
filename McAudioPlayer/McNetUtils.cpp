#include "McNetUtils.h"

#include <qcoreapplication.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qfile.h>

#include "IMcApplicationContext.h"
#include "McIocContainer.h"
#include "IMcMusicApi.h"
#include "McGlobal.h"

struct McNetUtilsData {
};

McNetUtils *McNetUtils::instance = new McNetUtils();

McNetUtils::McNetUtils(QObject *parent) 
	: QObject(qApp)
	, d(new McNetUtilsData)
{
}

IMcMusicApi* McNetUtils::getMusicApi(const QString& songSrc) noexcept {
	IMcApplicationContext* appCtx = McIocContainer::getInstance()->getApplicationContext();
	if (songSrc == MC_SONG_SRC_QQMUSIC)
		return dynamic_cast<IMcMusicApi*>(appCtx->getBean("qqMusic"));
	else if (songSrc == MC_SONG_SRC_YMUSIC)
		return dynamic_cast<IMcMusicApi*>(appCtx->getBean("yMusic"));
	return nullptr;
}

bool McNetUtils::canConnecting(const QUrl &url) noexcept {
	if (url.isLocalFile())
		return QFile::exists(url.toLocalFile());
	QNetworkAccessManager netMan;
	netMan.setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
	QNetworkReply *reply = instance->getReply(netMan, url);
	QEventLoop loop;
	bool isError = false;
	connect(reply, &QNetworkReply::redirected, [&isError, &loop](const QUrl &url) {
		if (url.url().contains("/404"))
			isError = true;
	});
	connect(reply, qOverload<QNetworkReply::NetworkError>(&QNetworkReply::error), &loop, &QEventLoop::quit);
	connect(reply, &QNetworkReply::readyRead, &loop, &QEventLoop::quit);
	connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();
	bool bReturn = false;
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (!isError && statusCode == 200)
		bReturn = true;
	instance->closeReply(reply);
	return bReturn;
}

QByteArray McNetUtils::getNetworkData(const QString &url, const QMap<QByteArray, QByteArray> &headers) noexcept {
	QNetworkAccessManager netMan;
	QNetworkReply *reply = instance->getReply(netMan, url, headers);
	QByteArray data = instance->getNetworkData(reply);
	return data;
}

QByteArray McNetUtils::getNetworkData(const QString& url, const QByteArray& postData, const QMap<QByteArray, QByteArray>& headers) noexcept {
	QNetworkAccessManager netMan;
	QNetworkReply* reply = instance->getReply(netMan, url, postData, headers);
	QByteArray data = instance->getNetworkData(reply);
	return data;
}

QNetworkReply *McNetUtils::getReply(QNetworkAccessManager& netMan, const QUrl &url, const QMap<QByteArray, QByteArray> &headers) noexcept {
	QNetworkRequest request;
	request.setUrl(url);
	for (auto itr = headers.cbegin(); itr != headers.cend(); itr++) {
		request.setRawHeader(itr.key(), itr.value());
	}
	return netMan.get(request);
}

QNetworkReply* McNetUtils::getReply(QNetworkAccessManager& netMan, const QUrl& url, const QByteArray& postData, const QMap<QByteArray, QByteArray>& headers) noexcept {
	QNetworkRequest request;
	request.setUrl(url);
	for (auto itr = headers.cbegin(); itr != headers.cend(); itr++) {
		request.setRawHeader(itr.key(), itr.value());
	}
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	request.setHeader(QNetworkRequest::ContentLengthHeader, postData.length());
	return netMan.post(request, postData);
}

QByteArray McNetUtils::getNetworkData(QNetworkReply *reply) noexcept {
	QEventLoop loop;
	connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();
	QByteArray data = reply->readAll();
	instance->closeReply(reply);
	return data;
}

void McNetUtils::preConnect(const QString &hostName, quint16 port) noexcept {

}

Q_ALWAYS_INLINE void McNetUtils::closeReply(QNetworkReply *reply) noexcept {
	if (!reply)
		return;
	reply->disconnect();
	if(reply->isRunning())
		reply->abort();
	reply->deleteLater();
}
