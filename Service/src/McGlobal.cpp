#include "Service/McGlobal.h"

#include <QxOrm.h>
#include <QxOrm_Impl.h>

namespace McAudioPlayerService {

void load() noexcept
{
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
}

}
