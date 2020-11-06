#include "Service/Dao/impl/McPlaylistDao.h"

#include <QMutex>
#include <QMutexLocker>

#include "Service/Domain/Po/McMusicDetailPo.h"
#include "Service/Domain/Po/McPlaylistPo.h"
#include "Service/Domain/Vo/McMusic.h"
#include "Service/Domain/Vo/McAlbum.h"
#include "Service/Domain/Vo/McArtist.h"

MC_DECL_PRIVATE_DATA(McPlaylistDao)
QMutex mtx;
MC_DECL_PRIVATE_DATA_END

MC_INIT(McPlaylistDao)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McPlaylistDao));
MC_INIT_END

McPlaylistDao::McPlaylistDao() noexcept
{
    MC_NEW_PRIVATE_DATA(McPlaylistDao);
}

McPlaylistDao::~McPlaylistDao() noexcept {
}

QList<McMusicPtr> McPlaylistDao::reloadMusic() noexcept {
    qDebug() << "start reload music";
    QList<McMusicPtr> musics;
    list_McPlaylistPo list_of_McPlaylistPo;
    qx::QxSqlQuery query("ORDER BY playlist_index");
    QSqlError daoError = qx::dao::fetch_by_query_with_relation(QStringList() << "{id}"
        << "McSonglistPo_ptr{id}",
        query, list_of_McPlaylistPo);
    if (daoError.type() != QSqlError::NoError) {
        qCritical() << "fetch playlist failure. error:" << daoError.type()
                    << "error str:" << daoError.text();
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
        qCritical() << "fetch music detail failure. error:" << daoError.type()
                    << "error str:" << daoError.text();
        return musics;
    }
    musics.reserve(static_cast<int>(list_of_McMusicPo.size()));
    for (const auto &pair : list_of_McMusicPo) {
        McMusicPtr music = McMusicPtr::create();
        music->setId(pair->m_songIndex);
        music->setSongTitle(pair->m_songTitle);
        McAlbumPtr album = McAlbumPtr::create();
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
            McArtistPtr artist = McArtistPtr::create();
            artist->setId(artistPo->m_artistIndex);
            artist->setArtistTitle(artistPo->m_artistTitle);
            music->addArtist(artist);
        }
        musics.append(music);
    }
    qDebug() << "end reload music";
    return musics;
}

bool McPlaylistDao::deleteAll() noexcept {
    QMutexLocker locker(&d->mtx);
    QSqlError sqlError = qx::dao::delete_all<McPlaylistPo>();
    if (sqlError.type() != QSqlError::NoError) {
        qCritical() << "delete t_playlist_info: " << sqlError.text();
        return false;
    }
    return true;
}

void McPlaylistDao::setMusics(const QList<McMusicPtr> &musics, int songSheetId) noexcept {
    QMutexLocker locker(&d->mtx);
    int playlistIndex = 1;	
    for (auto music : musics) {
        McSonglistPo_ptr songlist(new McSonglistPo);
        qx::QxSqlQuery query("WHERE t_songlist_info.songlist_index = :songlistIndex AND t_songlist_info.song_index = :songIndex");
        query.bind(":songlistIndex", songSheetId);
        query.bind(":songIndex", music->getId());
        QSqlError sqlError = qx::dao::fetch_by_query_with_relation("{id}", query, songlist);
        if (sqlError.type() != QSqlError::NoError) {
            qCritical() << "select t_songlist_info: " << sqlError.text();
            return;
        }
        McPlaylistPo_ptr playlistPo(new McPlaylistPo());
        playlistPo->m_id = songlist->m_id;
        playlistPo->m_playlistIndex = playlistIndex++;
        query = "INSERT INTO `t_playlist_info` (id, playlist_index) VALUES(:id, :playlistIndex)";
        query.bind(":id", static_cast<qlonglong>(playlistPo->m_id));
        query.bind(":playlistIndex", playlistPo->m_playlistIndex);
        qx::dao::execute_query(query, playlistPo);
        if (sqlError.type() != QSqlError::NoError) {
            qCritical() << "insert t_playlist_info: " << sqlError.text();
            return;
        }
    }
}
