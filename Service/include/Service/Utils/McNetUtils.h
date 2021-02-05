#pragma once

#include <QObject>

#include <QMap>

QT_FORWARD_DECLARE_CLASS(QUrl)
QT_FORWARD_DECLARE_CLASS(QNetworkReply)
QT_FORWARD_DECLARE_CLASS(QNetworkAccessManager)

class McNetUtils : public QObject {
    Q_OBJECT
public:
    McNetUtils() noexcept;
    
    static QByteArray getNetworkData(const QString &url, const QMap<QByteArray, QByteArray> &headers = QMap<QByteArray, QByteArray>()) noexcept;
    static QByteArray getNetworkData(
        const QString &url,
        const QByteArray &postData,
        const QMap<QByteArray, QByteArray> &headers = QMap<QByteArray, QByteArray>()) noexcept;
    typedef QPair<QByteArray, QByteArray> RawHeaderPair;
    static QList<RawHeaderPair> getResponseHeader(
        const QUrl &url,
        const QMap<QByteArray, QByteArray> &headers = QMap<QByteArray, QByteArray>()) noexcept;
    static bool download(const QString &url, const QString &path) noexcept;

private:
	QNetworkReply* getReply(QNetworkAccessManager& netMan, const QUrl& url, const QMap<QByteArray, QByteArray>& headers = QMap<QByteArray, QByteArray>()) noexcept;
	QNetworkReply* getReply(QNetworkAccessManager& netMan, const QUrl& url, const QByteArray& postData, const QMap<QByteArray, QByteArray>& headers = QMap<QByteArray, QByteArray>()) noexcept;
    void waitForReplyFinished(QNetworkReply *reply) noexcept;
    QByteArray getNetworkData(QNetworkReply *reply) noexcept;
    void closeReply(QNetworkReply *reply) noexcept;
    
};
