#include "McPlaylistDao.h"

#include "McContainerGlobal.h"
#include "McPlaylistPo.h"
#include "McMusic.h"
#include "McAlbum.h"
#include "McArtist.h"
#include "McMusicDetailPo.h"

MC_STATIC(McPlaylistDao)
mcRegisterComponent<McPlaylistDao*, IMcPlaylistDao*>("McPlaylistDao", "playlistDao");
MC_STATIC_END

McPlaylistDao::McPlaylistDao(QObject *parent)
	: QObject(parent)
{
}

McPlaylistDao::~McPlaylistDao(){
}

QList<McMusic *> McPlaylistDao::getPlaylist() noexcept {
	QList<McMusic *> musics;
	list_McPlaylistPo list_of_McPlaylistPo;
	qx::QxSqlQuery query("ORDER BY playlist_index");
	QSqlError daoError = qx::dao::fetch_by_query_with_relation(QStringList() << "{id}"
		<< "McSonglistPo_ptr{id}",
		query, list_of_McPlaylistPo);
	if (daoError.type() != QSqlError::NoError) {
		qCritical() << daoError.text();
		return musics;
	}
	list_McMusicPo list_of_McMusicPo;
	list_of_McMusicPo.reserve(list_of_McPlaylistPo.size());
	for (const auto &pair : list_of_McPlaylistPo) {
		if (!pair->m_songlist || !pair->m_songlist->m_music)
			continue;
		list_of_McMusicPo.push_back(pair->m_songlist->m_music);
	}
	daoError = qx::dao::fetch_by_id_with_relation(QStringList() << "{song_index, song_title}"
		<< "album_index{album_index, album_title}"
		<< "list_McArtistPo{artists_index, artists_title}",
		list_of_McMusicPo);
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

void McPlaylistDao::getSongUrl(McMusic *music) noexcept {
	McMusicPo_ptr musicPo(new McMusicPo());
	musicPo->m_songIndex = music->getId();
	qx::dao::fetch_by_id_with_relation("{song_url}", musicPo);
	music->setSongUrl(musicPo->m_songUrl);
}

void McPlaylistDao::updateMusicUrl(McMusic *music) noexcept {
	McMusicPo_ptr musicPo(new McMusicPo());
	musicPo->m_songIndex = music->getId();
	musicPo->m_songUrl = music->getSongUrl();
	qx::QxSqlQuery query("UPDATE t_music_info SET song_url = :songUrl WHERE song_index = :songIndex");
	query.bind(":songUrl", musicPo->m_songUrl);
	query.bind(":songIndex", musicPo->m_songIndex);
	qx::dao::execute_query(query, musicPo);
}

void McPlaylistDao::getMusicDetail(McMusic *music) noexcept {
	McMusicDetailPo_ptr musicDetailPo(new McMusicDetailPo());
	musicDetailPo->m_songIndex = music->getId();
	qx::dao::fetch_by_id_with_relation("{song_src, song_id, song_mid}", musicDetailPo);
	music->setSongSrc(musicDetailPo->m_songSrc);
	music->setSongId(musicDetailPo->m_songId);
	music->setSongMid(musicDetailPo->m_songMid);
}

bool McPlaylistDao::deleteAll() noexcept {
	QSqlError sqlError = qx::dao::delete_all<McPlaylistPo>();
	if (sqlError.type() != QSqlError::NoError) {
		qInfo() << "delete t_playlist_info: " << sqlError.text();
		return false;
	}
	return true;
}

void McPlaylistDao::addMusics(const QList<McMusic*>& musics, int songSheetId) noexcept {
	int playlistIndex = 1;	
	for (auto music : musics) {
		McSonglistPo_ptr songlist(new McSonglistPo);
		qx::QxSqlQuery query("WHERE t_songlist_info.songlist_index = :songlistIndex AND t_songlist_info.song_index = :songIndex");
		query.bind(":songlistIndex", songSheetId);
		query.bind(":songIndex", music->getId());
		QSqlError sqlError = qx::dao::fetch_by_query_with_relation("{id}", query, songlist);
		if (sqlError.type() != QSqlError::NoError) {
			qInfo() << "select t_songlist_info: " << sqlError.text();
			return;
		}
		McPlaylistPo_ptr playlistPo(new McPlaylistPo());
		playlistPo->m_id = songlist->m_id;
		playlistPo->m_playlistIndex = playlistIndex++;
		query = "INSERT INTO `t_playlist_info` (id, playlist_index) VALUES(:id, :playlistIndex)";
		query.bind(":id", playlistPo->m_id);
		query.bind(":playlistIndex", playlistPo->m_playlistIndex);
		qx::dao::execute_query(query, playlistPo);
		if (sqlError.type() != QSqlError::NoError) {
			qInfo() << "insert t_playlist_info: " << sqlError.text();
			return;
		}
	}
}

void McPlaylistDao::remove(int id) noexcept {
	McPlaylistPo_ptr playlistPo(new McPlaylistPo());
	qx::QxSqlQuery query("DELETE FROM t_playlist_info WHERE id = :id");
	query.bind(":id", id);
	QSqlError error = qx::dao::execute_query(query, playlistPo);
	if (error.type() != QSqlError::NoError)
		qInfo() << error.text();
}
