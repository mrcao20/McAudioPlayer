#include "McMusicDao.h"

#include "McContainerGlobal.h"
#include "McMusicPo.h"
#include "McMusic.h"
#include "McAlbum.h"
#include "McArtist.h"

MC_STATIC(McMusicDao)
mcRegisterComponent<McMusicDao*, IMcMusicDao*>("McMusicDao", "musicDao");
MC_STATIC_END

McMusicDao::McMusicDao(QObject *parent)
	: QObject(parent)
{
}

McMusicDao::~McMusicDao(){
}

#include <qdebug.h>
#include <qdatetime.h>
QList<McMusic *> McMusicDao::getMusics(int songSheetId) noexcept {
	QList<McMusic *> musics;
	list_McMusicPo list_of_McMusicPo;
	qx::QxSqlQuery query("WHERE t_songlist_detail_info.songlist_index = :songlistIndex");
	query.bind(":songlistIndex", songSheetId);
	auto start = QDateTime::currentMSecsSinceEpoch();
	QSqlError daoError = qx::dao::fetch_by_query_with_relation("*", query, list_of_McMusicPo);
	qDebug() << QDateTime::currentMSecsSinceEpoch() - start;
	if (daoError.type() != QSqlError::NoError) {
		qCritical() << daoError.text();
		return musics;
	}
	for (const auto &pair : list_of_McMusicPo) {
		McMusic *music = new McMusic();
		music->setId(pair->m_songIndex);
		music->setSongName(pair->m_songTitle);
		McAlbum *album = new McAlbum();
		int albumId = -1;
		QString albumName = "";
		if (pair->m_album != nullptr) {
			albumId = pair->m_album->m_albumIndex;
			albumName = pair->m_album->m_albumTitle;
		}
		album->setId(albumId);
		album->setAlbumName(albumName);
		music->setAlbum(album);
		list_McArtistPo list_of_McArtistPo = pair->m_artists;
		for (const auto &artistPo : list_of_McArtistPo) {
			McArtist *artist = new McArtist();
			artist->setId(artistPo->m_artistIndex);
			artist->setArtistName(artistPo->m_artistTitle);
			music->addArtist(artist);
		}
		musics.append(music);
	}
	return musics;
}
