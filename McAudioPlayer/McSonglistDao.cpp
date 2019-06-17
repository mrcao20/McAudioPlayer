#include "McSonglistDao.h"

#include "McContainerGlobal.h"
#include "McMusicPo.h"
#include "McSonglistPo.h"
#include "McMusic.h"
#include "McAlbum.h"
#include "McArtist.h"

MC_STATIC(McSonglistDao)
mcRegisterComponent<McSonglistDao*, IMcSonglistDao*>("McSonglistDao", "songlistDao");
MC_STATIC_END

McSonglistDao::McSonglistDao(QObject *parent)
	: QObject(parent)
{
}

McSonglistDao::~McSonglistDao(){
}

QList<McMusic *> McSonglistDao::getMusics(int songSheetId) noexcept {
	QList<McMusic *> musics;
	list_McMusicPo list_of_McMusicPo;
	qx::QxSqlQuery query("WHERE t_songlist_info.songlist_index = :songlistIndex ORDER BY t_songlist_info.id DESC");
	query.bind(":songlistIndex", songSheetId);
	QSqlError daoError = qx::dao::fetch_by_query_with_relation(QStringList() << "{song_index, song_title}"
		<< "list_McSonglistPo{id}"
		<< "album_index{album_index, album_title}"
		<< "list_McArtistPo{artists_index, artists_title}", 
		query, list_of_McMusicPo);
	if (daoError.type() != QSqlError::NoError) {
		qCritical() << daoError.text();
		return musics;
	}
	musics.reserve(list_of_McMusicPo.size());
	for (const auto &pair : list_of_McMusicPo) {
		McMusic *music = new McMusic();
		music->setId(pair->m_songIndex);
		music->setSongTitle(pair->m_songTitle);
		McAlbum *album = new McAlbum();
		int albumId = -1;
		QString albumName = "";
		if (pair->m_album != nullptr) {
			albumId = pair->m_album->m_albumIndex;
			albumName = pair->m_album->m_albumTitle;
		}
		album->setId(albumId);
		album->setAlbumTitle(albumName);
		music->setAlbum(album);
		list_McArtistPo list_of_McArtistPo = pair->m_artists;
		for (const auto &artistPo : list_of_McArtistPo) {
			McArtist *artist = new McArtist();
			artist->setId(artistPo->m_artistIndex);
			artist->setArtistTitle(artistPo->m_artistTitle);
			music->addArtist(artist);
		}
		musics.append(music);
	}
	return musics;
}

bool McSonglistDao::isExists(int songSheetId, McMusic* music) noexcept {
	McSonglistPo_ptr songlistPo(new McSonglistPo());
	qx::QxSqlQuery query("SELECT id FROM t_songlist_info WHERE songlist_index = :songlistIndex AND song_index = :songIndex");
	query.bind(":songlistIndex", songSheetId);
	query.bind(":songIndex", music->getId());
	QSqlError error = qx::dao::execute_query(query, songlistPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return true;	// 如果发生错误则返回true，表示不允许进行后续操作
	}
	return songlistPo->m_id != 0;
}

void McSonglistDao::addToSongSheet(int songSheetId, McMusic* music) noexcept {
	int maxId = getMaxSonglistId();
	if (maxId < 0)
		return;	// 当最大值小于零，说明发生了错误，直接返回
	McSonglistPo_ptr songlistPo(new McSonglistPo());
	qx::QxSqlQuery query("INSERT INTO `t_songlist_info` (id, songlist_index, song_index) VALUES(:id, :songlistIndex, :songIndex)");
	query.bind(":id", maxId + 1);
	query.bind(":songlistIndex", songSheetId);
	query.bind(":songIndex", music->getId());
	QSqlError error = qx::dao::execute_query(query, songlistPo);
	if (error.type() != QSqlError::NoError)
		qInfo() << error.text();
}

int McSonglistDao::getSonglistId(int songSheetId, McMusic* music) noexcept {
	McSonglistPo_ptr songlistPo(new McSonglistPo());
	qx::QxSqlQuery query("SELECT id FROM t_songlist_info WHERE songlist_index = :songlistIndex AND song_index = :songIndex");
	query.bind(":songlistIndex", songSheetId);
	query.bind(":songIndex", music->getId());
	QSqlError error = qx::dao::execute_query(query, songlistPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return -1;	// 当发生错误，返回-1，表示不允许继续操作
	}
	return songlistPo->m_id;
}

void McSonglistDao::removeSonglist(int id) noexcept {
	McSonglistPo_ptr songlistPo(new McSonglistPo());
	qx::QxSqlQuery query("PRAGMA foreign_keys=ON;");	// 开启级联删除(SQLite)
	QSqlError error = qx::dao::execute_query(query, songlistPo);
	if (error.type() != QSqlError::NoError)
		qInfo() << error.text();
	query = "DELETE FROM t_songlist_info WHERE id = :id";
	query.bind(":id", id);
	error = qx::dao::execute_query(query, songlistPo);
	if (error.type() != QSqlError::NoError)
		qInfo() << error.text();
}

int McSonglistDao::getMaxMusicId() noexcept {
	McMusicPo_ptr musicPo(new McMusicPo());
	qx::QxSqlQuery query("SELECT MAX(song_index) AS song_index FROM `t_music_info`");
	QSqlError error = qx::dao::execute_query(query, musicPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return -1;	// 如果发生错误则返回-1，表示不允许进行后续操作
	}
	return musicPo->m_songIndex;
}

int McSonglistDao::getMaxSonglistId() noexcept {
	McSonglistPo_ptr songlistPo(new McSonglistPo());
	qx::QxSqlQuery query("SELECT MAX(id) as id FROM t_songlist_info");
	QSqlError error = qx::dao::execute_query(query, songlistPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return -1;	// 当发生错误，返回-1，表示不允许继续操作
	}
	return songlistPo->m_id;
}
