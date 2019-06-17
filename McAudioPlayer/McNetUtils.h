#ifndef _MC_NET_UTILS_H_
#define _MC_NET_UTILS_H_

#include <qobject.h>

#include <qmap.h>

struct McNetUtilsData;

class IMcMusicApi;

QT_FORWARD_DECLARE_CLASS(QUrl)
QT_FORWARD_DECLARE_CLASS(QNetworkReply)
QT_FORWARD_DECLARE_CLASS(QNetworkAccessManager)

class McNetUtils : public QObject {
	Q_OBJECT

public:
	explicit McNetUtils(QObject *parent = 0);

	static IMcMusicApi* getMusicApi(const QString& songSrc) noexcept;
	static bool canConnecting(const QUrl &url) noexcept;
	static QByteArray getNetworkData(const QString &url, const QMap<QByteArray, QByteArray> &headers = QMap<QByteArray, QByteArray>()) noexcept;
	static QByteArray getNetworkData(const QString& url, const QByteArray& postData, const QMap<QByteArray, QByteArray>& headers = QMap<QByteArray, QByteArray>()) noexcept;

private:
	QNetworkReply* getReply(QNetworkAccessManager& netMan, const QUrl& url, const QMap<QByteArray, QByteArray>& headers = QMap<QByteArray, QByteArray>()) noexcept;
	QNetworkReply* getReply(QNetworkAccessManager& netMan, const QUrl& url, const QByteArray& postData, const QMap<QByteArray, QByteArray>& headers = QMap<QByteArray, QByteArray>()) noexcept;
	QByteArray getNetworkData(QNetworkReply *reply) noexcept;
	void preConnect(const QString &hostName, quint16 port = 80) noexcept;
	Q_ALWAYS_INLINE void closeReply(QNetworkReply *reply) noexcept;

private:
	static McNetUtils *instance;

	QScopedPointer<McNetUtilsData> d;
};

#endif // !_MC_NET_UTILS_H_