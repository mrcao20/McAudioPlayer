#include "McAudioPlayer/Utils/McNetUtils.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>

McNetUtils::McNetUtils() noexcept
{
}

QByteArray McNetUtils::getNetworkData(const QString &url, const QMap<QByteArray, QByteArray> &headers) noexcept {
	McNetUtils instance;
    QNetworkAccessManager netMan;
	QNetworkReply *reply = instance.getReply(netMan, url, headers);
	QByteArray data = instance.getNetworkData(reply);
	return data;
}

QByteArray McNetUtils::getNetworkData(const QString& url, const QByteArray& postData, const QMap<QByteArray, QByteArray>& headers) noexcept {
	McNetUtils instance;
    QNetworkAccessManager netMan;
	QNetworkReply* reply = instance.getReply(netMan, url, postData, headers);
	QByteArray data = instance.getNetworkData(reply);
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
	closeReply(reply);
	return data;
}

void McNetUtils::closeReply(QNetworkReply *reply) noexcept {
	if (!reply)
		return;
	reply->disconnect();
	if(reply->isRunning())
		reply->abort();
	reply->deleteLater();
}
