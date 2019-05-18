#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

#include <QxOrm.h>
#include <QxOrm_Impl.h>

#include "McIocContainer.h"
#include "McControllerContainer.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);
	QIcon icon;
	icon.addFile(QStringLiteral(":/icon/AudioPlayer.png"), QSize(), QIcon::Normal, QIcon::Off);
	app.setWindowIcon(icon);

	// Parameters to connect to database
	qx::QxSqlDatabase::getSingleton()->setDriverName("QMYSQL");
	qx::QxSqlDatabase::getSingleton()->setDatabaseName("d_music_modify");
	qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
	qx::QxSqlDatabase::getSingleton()->setPort(3306);
	qx::QxSqlDatabase::getSingleton()->setUserName("root");
	qx::QxSqlDatabase::getSingleton()->setPassword("839566521");
	qx::QxSqlDatabase::getSingleton()->setFormatSqlQueryBeforeLogging(true);

	// Only for debug purpose : assert if invalid offset detected fetching a relation
	qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true);

	McIocContainer::getInstance()->initContainer();

	qmlRegisterType<McControllerContainer>("McControllerContainer", 1, 0, "McControllerContainer");
	
	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
		&app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
