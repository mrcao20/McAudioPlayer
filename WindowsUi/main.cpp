#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QIcon>
#include <QFileInfo>
#include <QDir>

#include <McBoot/McQuickBoot.h>

#include <Service/McGlobal.h>
#include <Service/McVersion.h>

#include "McLog/McLogManager.h"
#include "McLog/Configurator/McXMLConfigurator.h"

#include "McExceptionFilter.h"

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
#ifndef QT_DEBUG
    SetUnhandledExceptionFilter(ExceptionFilter);
#endif
    
    McQuickBoot::setPreInitFunc([](QCoreApplication *app){
        QString logPath = QDir(app->applicationDirPath()).filePath(MC_LOG_CONFIG_PATH);
#ifndef QT_DEBUG
        McXMLConfigurator::configure(logPath);
        McLogManager::installQtMessageHandler();
#endif
        
        qInfo() << "log config path" << logPath;
    });
    McQuickBoot::setAfterInitFunc([](QCoreApplication *app, QQmlApplicationEngine *engine){
        McAudioPlayerService::load();
        
        app->setOrganizationName("mrcao");
        app->setOrganizationDomain("mrcao.mc");
        app->setApplicationName("McAudioPlayer");
        app->setApplicationVersion(VERSION_STR);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/AudioPlayer.png"), QSize(), QIcon::Normal, QIcon::Off);
        static_cast<QGuiApplication *>(app)->setWindowIcon(icon);
        
        QObject::connect(engine, SIGNAL(quit()), app, SLOT(quit()));
    });
    return McQuickBoot::singleRun(argc, argv);
}
