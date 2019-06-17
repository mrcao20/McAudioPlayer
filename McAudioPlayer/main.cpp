#include <QQmlApplicationEngine>
#include <QIcon>
#include <qdebug.h>

#include <QxOrm.h>
#include <QxOrm_Impl.h>

#include "McSingleApplication.h"
#include "McIocContainer.h"
#include "McControllerContainer.h"
#include "McModelContainer.h"
#include "McMusic.h"

QString commandLineFilePathArgument() {
	const QStringList args = QCoreApplication::arguments();
	for (const QString& arg : args.mid(1)) {
		if (!arg.startsWith(QLatin1Char('-')))
			return arg;
	}
	return "";
}

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	McSingleApplication app(argc, argv);
	if (app.isRunning())
		return 0;
	app.setOrganizationName("mrcao");
	app.setOrganizationDomain("mrcao.mc");
	app.setApplicationName("McAudioPlayer");
	QIcon icon;
	icon.addFile(QStringLiteral(":/icon/AudioPlayer.png"), QSize(), QIcon::Normal, QIcon::Off);
	app.setWindowIcon(icon);

	// Parameters to connect to database
	/*qx::QxSqlDatabase::getSingleton()->setDriverName("QMYSQL");
	qx::QxSqlDatabase::getSingleton()->setDatabaseName("temp");*/
	qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
	QString dbPath = qApp->applicationDirPath();
#ifdef QT_DEBUG
	dbPath += "/../Release";
#endif // QT_DEBUG
	QString dbName = dbPath + "/d_music.db";
	QString dataName = dbPath + "/d_music_data.db";
	if (!QFile::exists(dbName) && !QFile::exists(dataName))
		qFatal("both 'd_music.db' and 'd_music_data.db' not found!");
	if (!QFile::exists(dataName))
		QFile::copy(dbName, dataName);
	qx::QxSqlDatabase::getSingleton()->setDatabaseName(dataName);
	qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
	qx::QxSqlDatabase::getSingleton()->setPort(3306);
	qx::QxSqlDatabase::getSingleton()->setUserName("root");
	qx::QxSqlDatabase::getSingleton()->setPassword("839566521");
	qx::QxSqlDatabase::getSingleton()->setFormatSqlQueryBeforeLogging(true);

	// Only for debug purpose : assert if invalid offset detected fetching a relation
	qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true);

	McIocContainer::getInstance()->initContainer();

	qmlRegisterType<McControllerContainer>("McControllerContainer", 1, 0, "McControllerContainer");
	qmlRegisterType<McModelContainer>("McModelContainer", 1, 0, "McModelContainer");
	
	QString filePath = commandLineFilePathArgument();

	QQmlApplicationEngine engine;
	engine.addImportPath(R"(D:\soft\source\McQMLPlugin)");
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
		&app, [url, &app, filePath](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
		if (obj && obj->objectName() == "mainWindow") {
			app.mainWindow = obj;
			if (!filePath.isEmpty()) {
				McMusic* music = new McMusic();
				music->setSongTitle(QFileInfo(filePath).baseName());
				music->setSongUrl(filePath);
				QMetaObject::invokeMethod(obj, "playMusic", Q_ARG(QVariant, QVariant::fromValue(music)));
			}
		}
	}, Qt::QueuedConnection);
	QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));
	engine.load(url);

	return app.exec();
}
