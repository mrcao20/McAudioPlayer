#include "McSongSheetDao.h"

#include <QVariant>
#include <QDebug>

#include "McContainerGlobal.h"
#include "McSongSheet.h"
#include "McSongSheetPo.h"

MC_STATIC(McSongSheetDao)
mcRegisterComponent<McSongSheetDao*, IMcSongSheetDao*>("McSongSheetDao", "songSheetDao");
MC_STATIC_END

McSongSheetDao::McSongSheetDao(QObject *parent)
	: QObject(parent)
{
}

McSongSheetDao::~McSongSheetDao(){
}

QList<McSongSheet *> McSongSheetDao::getSongSheets() noexcept {
	QList<McSongSheet *> songSheets;
	list_McSongSheetPo list_of_McSongSheetPo;
	QSqlError daoError = qx::dao::fetch_all(list_of_McSongSheetPo);
	if (daoError.type() != QSqlError::NoError) {
		qCritical() << daoError.text();
		return songSheets;
	}
	for (const auto &pair : list_of_McSongSheetPo) {
		McSongSheet * songSheet = new McSongSheet();
		songSheet->setId(pair.second->m_songlistIndex);
		songSheet->setTitle(pair.second->m_songlistSection);
		songSheet->setSongSheet(pair.second->m_songlistName);
		songSheets.append(songSheet);
	}
	return songSheets;
}

void McSongSheetDao::deleteSongSheet(McSongSheet* songSheet) noexcept {
	McSongSheetPo_ptr songSheetPo(new McSongSheetPo());
	qx::QxSqlQuery query("PRAGMA foreign_keys=ON;");	// ¿ªÆô¼¶ÁªÉ¾³ý(SQLite)
	QSqlError error = qx::dao::execute_query(query, songSheetPo);
	if (error.type() != QSqlError::NoError)
		qInfo() << error.text();
	query = "DELETE FROM t_songlist_detail_info WHERE songlist_index = :songlistIndex";
	query.bind(":songlistIndex", songSheet->getId());
	error = qx::dao::execute_query(query, songSheetPo);
	if (error.type() != QSqlError::NoError)
		qInfo() << error.text();
}

void McSongSheetDao::renameSongSheet(McSongSheet* songSheet) noexcept {
	McSongSheetPo_ptr songSheetPo(new McSongSheetPo());
	qx::QxSqlQuery query("UPDATE `t_songlist_detail_info` SET songlist_name = :songlistName WHERE songlist_index = :songlistIndex");
	query.bind(":songlistIndex", songSheet->getId());
	query.bind(":songlistName", songSheet->getSongSheet());
	QSqlError error = qx::dao::execute_query(query, songSheetPo);
	if (error.type() != QSqlError::NoError)
		qInfo() << error.text();
}

bool McSongSheetDao::insert(McSongSheet* songSheet) noexcept {
	McSongSheetPo_ptr songSheetPo(new McSongSheetPo());
	qx::QxSqlQuery query("INSERT INTO `t_songlist_detail_info` (songlist_index, songlist_section, songlist_name) VALUES(:songlistIndex, :songlistSection, :songlistName)");
	query.bind(":songlistIndex", songSheet->getId());
	query.bind(":songlistSection", songSheet->getTitle());
	query.bind(":songlistName", songSheet->getSongSheet());
	QSqlError error = qx::dao::execute_query(query, songSheetPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return false;
	}
	return true;
}
