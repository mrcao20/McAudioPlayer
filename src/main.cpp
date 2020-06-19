#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#else
#endif

#include <QIcon>
#include <QFileInfo>

#include <QxOrm.h>
#include <QxOrm_Impl.h>

#include <McBoot/McIocBoot.h>

#include "McLog/McLogManager.h"
#include "McLog/Configurator/McXMLConfigurator.h"

#include "McAudioPlayer/version.h"
#include "McAudioPlayer/McGlobal.h"

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
    return McIocBoot::singleRun<McSingleApplication>(argc, argv, QUrl(QStringLiteral("qrc:/main.qml"))
        , [](McSingleApplication *app, QQmlApplicationEngine *engine){
        
        // Parameters to connect to database
        /*qx::QxSqlDatabase::getSingleton()->setDriverName("QMYSQL");
        qx::QxSqlDatabase::getSingleton()->setDatabaseName("temp");*/
        qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
        QString dbPath = qApp->applicationDirPath() + "/db";
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
        qx::QxSqlDatabase::getSingleton()->setTraceSqlQuery(false);
//        qx::QxSqlDatabase::getSingleton()->setFormatSqlQueryBeforeLogging(true);
    
        // Only for debug purpose : assert if invalid offset detected fetching a relation
        qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true);
        
        app->setOrganizationName("mrcao");
        app->setOrganizationDomain("mrcao.mc");
        app->setApplicationName("McAudioPlayer");
        app->setApplicationVersion(VERSION_STR);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/AudioPlayer.png"), QSize(), QIcon::Normal, QIcon::Off);
        app->setWindowIcon(icon);
        
        QObject::connect(engine, SIGNAL(quit()), app, SLOT(quit()));
    }
    , [](McSingleApplication *app){
        QString logPath = QDir(app->applicationDirPath()).filePath(MC_LOG_CONFIG_PATH);
        McLogManager::installQtMessageHandler();
        McXMLConfigurator::configure(logPath);
        
        qInfo() << "log config path" << logPath;
    });
}
