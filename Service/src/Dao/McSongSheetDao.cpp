#include "Service/Dao/impl/McSongSheetDao.h"

#include "Service/Domain/Vo/McSongSheet.h"
#include "Service/Domain/Po/McSongSheetPo.h"

MC_DECL_PRIVATE_DATA(McSongSheetDao)
MC_DECL_PRIVATE_DATA_END

MC_INIT(McSongSheetDao)
MC_REGISTER_BEAN_FACTORY(McSongSheetDao);
MC_INIT_END

McSongSheetDao::McSongSheetDao() noexcept
{
    MC_NEW_PRIVATE_DATA(McSongSheetDao);
}

McSongSheetDao::~McSongSheetDao() noexcept {
}

QList<McSongSheetPtr> McSongSheetDao::getSongSheets() noexcept {
    if (thread() == QThread::currentThread()) {
        return getSongSheets_helper();
    } else {
        QList<McSongSheetPtr> flag;
        QMetaObject::invokeMethod(this,
                                  MC_STRINGIFY(getSongSheets_helper),
                                  Qt::BlockingQueuedConnection,
                                  Q_RETURN_ARG(QList<McSongSheetPtr>, flag));
        return flag;
    }
}

void McSongSheetDao::renameSongSheet(McSongSheetConstPtrRef songSheet) noexcept {
    if (thread() == QThread::currentThread()) {
        renameSongSheet_helper(songSheet);
    } else {
        QMetaObject::invokeMethod(this,
                                  MC_STRINGIFY(renameSongSheet_helper),
                                  Qt::BlockingQueuedConnection,
                                  Q_ARG(McSongSheetPtr, songSheet));
    }
}

void McSongSheetDao::deleteSongSheet(McSongSheetConstPtrRef songSheet) noexcept {
    if (thread() == QThread::currentThread()) {
        deleteSongSheet_helper(songSheet);
    } else {
        QMetaObject::invokeMethod(this,
                                  MC_STRINGIFY(deleteSongSheet_helper),
                                  Qt::BlockingQueuedConnection,
                                  Q_ARG(McSongSheetPtr, songSheet));
    }
}

bool McSongSheetDao::insert(McSongSheetConstPtrRef songSheet) noexcept {
    if (thread() == QThread::currentThread()) {
        return insert_helper(songSheet);
    } else {
        bool flag = false;
        QMetaObject::invokeMethod(this,
                                  MC_STRINGIFY(insert_helper),
                                  Qt::BlockingQueuedConnection,
                                  Q_RETURN_ARG(bool, flag),
                                  Q_ARG(McSongSheetPtr, songSheet));
        return flag;
    }
}

QList<McSongSheetPtr> McSongSheetDao::getSongSheets_helper() noexcept
{
    qDebug() << "start get song sheet";
    QList<McSongSheetPtr> songSheets;
    list_McSongSheetPo list_of_McSongSheetPo;
    QSqlError daoError = qx::dao::fetch_all(list_of_McSongSheetPo);
    if (daoError.type() != QSqlError::NoError) {
        qCritical() << "featch song sheet error. type:" << daoError.type()
                    << "error str:" << daoError.text();
        return songSheets;
    }
    qInfo() << "get song sheet from database for length:" << list_of_McSongSheetPo.size();
    for (const auto &pair : list_of_McSongSheetPo) {
        McSongSheetPtr songSheet = McSongSheetPtr::create();
        songSheet->setId(pair.second->m_songlistIndex);
        songSheet->setTitle(pair.second->m_songlistSection);
        songSheet->setSongSheet(pair.second->m_songlistName);
        songSheets.append(songSheet);
    }
    return songSheets;
}

void McSongSheetDao::renameSongSheet_helper(const McSongSheetPtr &songSheet) noexcept
{
    McSongSheetPo_ptr songSheetPo(new McSongSheetPo());
    qx::QxSqlQuery query("UPDATE `t_songlist_detail_info` SET songlist_name = :songlistName WHERE "
                         "songlist_index = :songlistIndex");
    query.bind(":songlistIndex", songSheet->getId());
    query.bind(":songlistName", songSheet->getSongSheet());
    QSqlError error = qx::dao::execute_query(query, songSheetPo);
    if (error.type() != QSqlError::NoError)
        qCritical() << "execute renameSongSheet query error. type:" << error.type()
                    << "error str:" << error.text();
}

void McSongSheetDao::deleteSongSheet_helper(const McSongSheetPtr &songSheet) noexcept
{
    McSongSheetPo_ptr songSheetPo(new McSongSheetPo());
    qx::QxSqlQuery query("PRAGMA foreign_keys=ON;"); // 开启级联删除(SQLite)
    QSqlError error = qx::dao::execute_query(query, songSheetPo);
    if (error.type() != QSqlError::NoError)
        qInfo() << error.text();
    query = "DELETE FROM t_songlist_detail_info WHERE songlist_index = :songlistIndex";
    query.bind(":songlistIndex", songSheet->getId());
    error = qx::dao::execute_query(query, songSheetPo);
    if (error.type() != QSqlError::NoError)
        qCritical() << "execute deleteSongSheet query error. type:" << error.type()
                    << "error str:" << error.text();
}

bool McSongSheetDao::insert_helper(const McSongSheetPtr &songSheet) noexcept
{
    McSongSheetPo_ptr songSheetPo(new McSongSheetPo());
    qx::QxSqlQuery query("INSERT INTO `t_songlist_detail_info` (songlist_index, songlist_section, "
                         "songlist_name) VALUES(:songlistIndex, :songlistSection, :songlistName)");
    query.bind(":songlistIndex", songSheet->getId());
    query.bind(":songlistSection", songSheet->getTitle());
    query.bind(":songlistName", songSheet->getSongSheet());
    QSqlError error = qx::dao::execute_query(query, songSheetPo);
    if (error.type() != QSqlError::NoError) {
        qCritical() << "execute insert query error. type:" << error.type()
                    << "error str:" << error.text();
        return false;
    }
    return true;
}
