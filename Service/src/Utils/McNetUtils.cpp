#include "Service/Utils/McNetUtils.h"

#include <QEventLoop>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

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

bool McNetUtils::download(const QString &url, const QString &path) noexcept
{
    if (url.isEmpty()) {
        return false;
    }
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "cannot open file:" << path << "error" << file.error()
                    << "error str:" << file.errorString();
        return false;
    }
    McNetUtils instance;
    QNetworkAccessManager netMan;
    QNetworkReply *reply = instance.getReply(netMan, url, QMap<QByteArray, QByteArray>());
    QEventLoop loop;
    connect(reply, &QNetworkReply::readyRead, [reply, &file]() { file.write(reply->readAll()); });
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->error() != QNetworkReply::NoError) {
        qCritical() << "http  request occurred error:" << reply->error()
                    << "error str:" << reply->errorString();
        return false;
    }
    instance.closeReply(reply);
    return true;
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
    if(reply->error() != QNetworkReply::NoError) {
        qCritical() << "http  request occurred error:" << reply->error()
                    << "error str:" << reply->errorString();
    }
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
