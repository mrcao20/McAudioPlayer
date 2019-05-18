#ifndef _MC_CONTROLLER_CONTAINER_H_
#define _MC_CONTROLLER_CONTAINER_H_
#pragma execution_character_set("utf-8")

#include <QObject>

#include <qmap.h>

QT_BEGIN_NAMESPACE
class QMetaMethod;
QT_END_NAMESPACE

struct McControllerContainerData;

class McControllerContainer : public QObject{
	Q_OBJECT

public:
	explicit McControllerContainer(QObject *parent = 0);
	~McControllerContainer();

	Q_INVOKABLE QString invoke(const QString &uri) noexcept;
	Q_INVOKABLE QString invoke(const QString &uri, const QString &data) noexcept;

private:
	QString invokeForUri(QObject *bean, const QString &func, const QString &param) noexcept;
	QMap<QString, QVariant> splitParam(const QString &param) noexcept;
	bool isMethodMatching(const QMetaMethod &m, const QList<QString> &argNames) noexcept;
	void removeDuplication(QList<QString> &argNames, QList<QByteArray> &paramNames, QList<QByteArray> &paramTypes = QList<QByteArray>()) noexcept;
	QString invokeForArgs(QObject *bean, const QMetaMethod &method, const QMap<QString, QVariant> &args) noexcept;
	QVariant makeValue(const QByteArray &typeName, const QMap<QString, QVariant> &args) noexcept;

private:
	QScopedPointer<McControllerContainerData> d;
};

#endif // !_MC_CONTROLLER_CONTAINER_H_