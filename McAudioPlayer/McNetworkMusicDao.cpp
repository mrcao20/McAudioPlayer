#include "McNetworkMusicDao.h"

#include "McContainerGlobal.h"
#include "McMusicPo.h"
#include "McMusicDetailPo.h"
#include "McMusic.h"
#include "McAlbum.h"
#include "McArtist.h"
#include "McSonglistPo.h"

MC_STATIC(McNetworkMusicDao)
mcRegisterComponent<McNetworkMusicDao*, IMcNetworkMusicDao*>("McNetworkMusicDao", "networkMusicDao");
MC_STATIC_END

McNetworkMusicDao::McNetworkMusicDao(QObject* parent)
	: QObject(parent)
{
}

McNetworkMusicDao::~McNetworkMusicDao() {
}

bool McNetworkMusicDao::getIdIfExistsForUrl(McMusic* music) noexcept {
	music->setId(-1);
	if (music->getSongUrl().isEmpty()) {
		qInfo() << "song url cannot be empty";
		return true;	// ������ֵ�url�����ڣ���ֱ�ӱ�������true����ʾ��ֹ��������
	}
	McMusicPo_ptr musicPo(new McMusicPo());
	qx::QxSqlQuery query("SELECT song_index FROM `t_music_info` WHERE song_url = :songUrl");
	query.bind(":songUrl", music->getSongUrl());
	QSqlError error = qx::dao::execute_query(query, musicPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return true;	// ������������򷵻�true����ʾ��������к�������
	}
	if (musicPo->m_songIndex == 0)
		return false;
	else {
		music->setId(musicPo->m_songIndex);
		return true;
	}
}

bool McNetworkMusicDao::getIdIfExists(McMusic* music) noexcept {
	music->setId(-1);
	McMusicDetailPo_ptr musicDetailPo(new McMusicDetailPo());
	qx::QxSqlQuery query("SELECT song_index FROM `t_music_detail_info` WHERE song_src = :songSrc AND (song_id IS NULL OR song_id = :songId) AND (song_mid IS NULL OR song_mid = :songMid)");
	query.bind(":songSrc", music->getSongSrc());
	query.bind(":songId", music->getSongId());
	query.bind(":songMid", music->getSongMid());
	QSqlError error = qx::dao::execute_query(query, musicDetailPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return true;	// ������������򷵻�true����ʾ��������к�������
	}
	if (musicDetailPo->m_songIndex == 0)
		return false;
	else {
		music->setId(musicDetailPo->m_songIndex);
		return true;
	}
}

bool McNetworkMusicDao::getIdIfExists(McAlbum* album) noexcept {
	album->setId(-1);
	McAlbumPo_ptr albumPo(new McAlbumPo());
	qx::QxSqlQuery query("SELECT album_index FROM `t_album_detail_info` WHERE (album_id IS NULL OR album_id = :albumId) AND (album_mid IS NULL OR album_mid = :albumMid)");
	query.bind(":albumId", album->getAlbumId());
	query.bind(":albumMid", album->getAlbumMid());
	QSqlError error = qx::dao::execute_query(query, albumPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return true;	// ������������򷵻�true����ʾ��������к�������
	}
	if (albumPo->m_albumIndex == 0)
		return false;
	else {
		album->setId(albumPo->m_albumIndex);
		return true;
	}
}

bool McNetworkMusicDao::getIdIfExists(McArtist* artist) noexcept {
	artist->setId(-1);
	McArtistPo_ptr artistPo(new McArtistPo());
	qx::QxSqlQuery query("SELECT artists_index FROM `t_artists_detail_info` WHERE (artists_id IS NULL OR artists_id = :artistId) AND (artists_mid IS NULL OR artists_mid = :artistMid)");
	query.bind(":artistId", artist->getArtistId());
	query.bind(":artistMid", artist->getArtistMid());
	QSqlError error = qx::dao::execute_query(query, artistPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return true;	// ������������򷵻�true����ʾ��������к�������
	}
	if (artistPo->m_artistIndex == 0)
		return false;
	else {
		artist->setId(artistPo->m_artistIndex);
		return true;
	}
}

void McNetworkMusicDao::addAlbum(McAlbum* album) noexcept {
	McAlbumPo_ptr albumPo(new McAlbumPo());
	qx::QxSqlQuery query("INSERT INTO `t_album_detail_info` (album_index, album_id, album_mid, album_name, album_title, album_title_hilight) "
		"VALUES(:albumIndex, :albumId, :albumMid, :albumName, :albumTitle, :albumTitleHilight)");
	query.bind(":albumIndex", album->getId());
	query.bind(":albumId", album->getAlbumId());
	query.bind(":albumMid", album->getAlbumMid());
	query.bind(":albumName", album->getAlbumName());
	query.bind(":albumTitle", album->getAlbumTitle());
	query.bind(":albumTitleHilight", album->getAlbumTitleHilight());
	QSqlError error = qx::dao::execute_query(query, albumPo);
	if (error.type() != QSqlError::NoError)
		qInfo() << error.text();
}

void McNetworkMusicDao::addMusic(McMusic* music) noexcept {
	McMusicPo_ptr musicPo(new McMusicPo());
	qx::QxSqlQuery query("INSERT INTO `t_music_info` (song_index, song_title, song_url) "
		"VALUES(:songIndex, :songTitle, :songUrl)");
	query.bind(":songIndex", music->getId());
	query.bind(":songTitle", music->getSongTitle());
	query.bind(":songUrl", music->getSongUrl());
	QSqlError error = qx::dao::execute_query(query, musicPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return;	// ������������򷵻أ���ʾ��������к�������
	}
	McMusicDetailPo_ptr musicDetailPo(new McMusicDetailPo());
	query = "INSERT INTO `t_music_detail_info` (song_index, song_src, song_id, song_mid, song_name, song_title_hilight) "
		"VALUES(:songIndex, :songSrc, :songId, :songMid, :songName, :songTitleHilight)";
	query.bind(":songIndex", music->getId());
	query.bind(":songSrc", music->getSongSrc());
	query.bind(":songId", music->getSongId());
	query.bind(":songMid", music->getSongMid());
	query.bind(":songName", music->getSongName());
	query.bind(":songTitleHilight", music->getSongTitleHilight());
	error = qx::dao::execute_query(query, musicDetailPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return;	// ������������򷵻أ���ʾ��������к�������
	}

	McAlbum* album = music->getAlbum();
	if (album) {
		query = "UPDATE `t_music_info` SET album_index = :albumIndex WHERE song_index = :songIndex";
		query.bind(":albumIndex", album->getId());
		query.bind(":songIndex", music->getId());
		error = qx::dao::execute_query(query, musicPo);
		if (error.type() != QSqlError::NoError) {
			qInfo() << error.text();
			return;	// ������������򷵻أ���ʾ��������к�������
		}
	}
	QList<McArtist*> artists = music->getArtists();
	McArtistPo_ptr artistPo(new McArtistPo());
	for (auto artist : artists) {
		query = "INSERT INTO `t_artists_info` (song_index, artists_index) "
			"VALUES(:songIndex, :artistIndex)";
		query.bind(":songIndex", music->getId());
		query.bind(":artistIndex", artist->getId());
		error = qx::dao::execute_query(query, artistPo);
		if (error.type() != QSqlError::NoError) {
			qInfo() << error.text();
			return;	// ������������򷵻أ���ʾ��������к�������
		}
	}

	/*McMusicPo_ptr musicPo(new McMusicPo());
	musicPo->m_songIndex = music->getId();
	musicPo->m_songTitle = music->getSongTitle();
	musicPo->m_songUrl = music->getSongUrl();
	McAlbumPo_ptr albumPo(new McAlbumPo());
	McAlbum* album = music->getAlbum();
	albumPo->m_albumIndex = album->getId();
	albumPo->m_albumId = album->getAlbumId();
	albumPo->m_albumMid = album->getAlbumMid();
	albumPo->m_albumName = album->getAlbumName();
	albumPo->m_albumTitle = album->getAlbumTitle();
	albumPo->m_albumTitleHilight = album->getAlbumTitleHilight();
	musicPo->m_album = albumPo;
	QList<McArtist*> artists = music->getArtists();
	list_McArtistPo list_of_McArtistPo;
	for (auto artist : artists) {
		McArtistPo_ptr artistPo(new McArtistPo());
		artistPo->m_artistIndex = artist->getId();
		artistPo->m_artistId = artist->getArtistId();
		artistPo->m_artistMid = artist->getArtistMid();
		artistPo->m_artistName = artist->getArtistName();
		artistPo->m_artistTitle = artist->getArtistTitle();
		artistPo->m_artistTitleHilight = artist->getArtistTitleHilight();
		list_of_McArtistPo.push_back(artistPo);
	}
	musicPo->m_artists = list_of_McArtistPo;
	McMusicDetailPo_ptr musicDetailPo(new McMusicDetailPo());
	musicDetailPo->m_songIndex = music->getId();
	musicDetailPo->m_songSrc = music->getSongSrc();
	musicDetailPo->m_songId = music->getSongId();
	musicDetailPo->m_songMid = music->getSongMid();
	musicDetailPo->m_songName = music->getSongName();
	musicDetailPo->m_songTitleHilight = music->getSongTitleHilight();
	musicPo->m_musicDetail = musicDetailPo;
	QSqlError error = qx::dao::insert_with_relation(QStringList() << "{*}"
		<< "album_index{*}"
		<< "list_McArtistPo{*}"
		<< "McMusicDetailPo_ptr{*}"
		, musicPo);
	if (error.type() != QSqlError::NoError)
		qInfo() << error.text();*/
}

void McNetworkMusicDao::addArtist(McArtist* artist) noexcept {
	McArtistPo_ptr artistPo(new McArtistPo());
	qx::QxSqlQuery query("INSERT INTO `t_artists_detail_info` (artists_index, artists_id, artists_mid, artists_name, artists_title, artists_title_hilight) "
		"VALUES(:artistIndex, :artistId, :artistMid, :artistName, :artistTitle, :artistTitleHilight)");
	query.bind(":artistIndex", artist->getId());
	query.bind(":artistId", artist->getArtistId());
	query.bind(":artistMid", artist->getArtistMid());
	query.bind(":artistName", artist->getArtistName());
	query.bind(":artistTitle", artist->getArtistTitle());
	query.bind(":artistTitleHilight", artist->getArtistTitleHilight());
	QSqlError error = qx::dao::execute_query(query, artistPo);
	if (error.type() != QSqlError::NoError)
		qInfo() << error.text();
}

int McNetworkMusicDao::getMaxAlbumId() noexcept {
	McAlbumPo_ptr albumPo(new McAlbumPo());
	qx::QxSqlQuery query("SELECT MAX(album_index) AS album_index FROM `t_album_detail_info`");
	QSqlError error = qx::dao::execute_query(query, albumPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return -1;	// ������������򷵻�-1����ʾ��������к�������
	}
	return albumPo->m_albumIndex;
}

int McNetworkMusicDao::getMaxArtistId() noexcept {
	McArtistPo_ptr artistPo(new McArtistPo());
	qx::QxSqlQuery query("SELECT MAX(artists_index) AS artists_index FROM `t_artists_detail_info`");
	QSqlError error = qx::dao::execute_query(query, artistPo);
	if (error.type() != QSqlError::NoError) {
		qInfo() << error.text();
		return -1;	// ������������򷵻�-1����ʾ��������к�������
	}
	return artistPo->m_artistIndex;
}
