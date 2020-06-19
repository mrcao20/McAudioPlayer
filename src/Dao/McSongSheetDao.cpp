#include "McAudioPlayer/Dao/impl/McSongSheetDao.h"

#include "McAudioPlayer/Domain/Vo/McSongSheet.h"
#include "McAudioPlayer/Domain/Po/McSongSheetPo.h"

MC_DECL_PRIVATE_DATA(McSongSheetDao)
MC_DECL_PRIVATE_DATA_END

MC_INIT(McSongSheetDao)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McSongSheetDao));
MC_INIT_END

McSongSheetDao::McSongSheetDao() noexcept
{
    MC_NEW_PRIVATE_DATA(McSongSheetDao);
}

McSongSheetDao::~McSongSheetDao() noexcept {
}

QList<McSongSheetPtr> McSongSheetDao::getSongSheets() noexcept {
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

void McSongSheetDao::renameSongSheet(McSongSheetConstPtrRef songSheet) noexcept {
    McSongSheetPo_ptr songSheetPo(new McSongSheetPo());
    qx::QxSqlQuery query("UPDATE `t_songlist_detail_info` SET songlist_name = :songlistName WHERE songlist_index = :songlistIndex");
    query.bind(":songlistIndex", songSheet->getId());
    query.bind(":songlistName", songSheet->getSongSheet());
    QSqlError error = qx::dao::execute_query(query, songSheetPo);
    if (error.type() != QSqlError::NoError)
        qCritical() << "execute renameSongSheet query error. type:" << error.type()
                    << "error str:" << error.text();
}

void McSongSheetDao::deleteSongSheet(McSongSheetConstPtrRef songSheet) noexcept {
    McSongSheetPo_ptr songSheetPo(new McSongSheetPo());
    qx::QxSqlQuery query("PRAGMA foreign_keys=ON;");	// 开启级联删除(SQLite)
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

bool McSongSheetDao::insert(McSongSheetConstPtrRef songSheet) noexcept {
    McSongSheetPo_ptr songSheetPo(new McSongSheetPo());
    qx::QxSqlQuery query("INSERT INTO `t_songlist_detail_info` (songlist_index, songlist_section, songlist_name) VALUES(:songlistIndex, :songlistSection, :songlistName)");
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
