#include "Service/Dao/impl/McNetworkMusicDao.h"

#include "Service/Domain/Po/McAlbumPo.h"
#include "Service/Domain/Po/McArtistPo.h"
#include "Service/Domain/Po/McMusicPo.h"
#include "Service/Domain/Vo/McAlbum.h"
#include "Service/Domain/Vo/McArtist.h"
#include "Service/Domain/Vo/McMusic.h"

MC_DECL_PRIVATE_DATA(McNetworkMusicDao)
MC_DECL_PRIVATE_DATA_END

MC_INIT(McNetworkMusicDao)
MC_REGISTER_BEAN_FACTORY(McNetworkMusicDao);
MC_INIT_END

McNetworkMusicDao::McNetworkMusicDao() noexcept
{
    MC_NEW_PRIVATE_DATA(McNetworkMusicDao);
}

McNetworkMusicDao::~McNetworkMusicDao() noexcept {
}

bool McNetworkMusicDao::getIdIfExistsForUrl(McMusicPtr music) noexcept {
    //    if (thread() == QThread::currentThread()) {
    return getIdIfExistsForUrl_helper(music);
    //    } else {
    //        bool flag = false;
    //        QMetaObject::invokeMethod(this,
    //                                  MC_STRINGIFY(getIdIfExistsForUrl_helper),
    //                                  Qt::BlockingQueuedConnection,
    //                                  Q_RETURN_ARG(bool, flag),
    //                                  Q_ARG(McMusicPtr, music));
    //        return flag;
    //    }
}

bool McNetworkMusicDao::getIdIfExists(McMusicPtr music) noexcept {
    //    if (thread() == QThread::currentThread()) {
    return getIdIfExists_helper(music);
    //    } else {
    //        bool flag = false;
    //        QMetaObject::invokeMethod(this,
    //                                  MC_STRINGIFY(getIdIfExists_helper),
    //                                  Qt::BlockingQueuedConnection,
    //                                  Q_RETURN_ARG(bool, flag),
    //                                  Q_ARG(McMusicPtr, music));
    //        return flag;
    //    }
}

bool McNetworkMusicDao::getIdIfExists(McAlbumPtr album) noexcept {
    //    if (thread() == QThread::currentThread()) {
    return getIdIfExists_helper(album);
    //    } else {
    //        bool flag = false;
    //        QMetaObject::invokeMethod(this,
    //                                  MC_STRINGIFY(getIdIfExists_helper),
    //                                  Qt::BlockingQueuedConnection,
    //                                  Q_RETURN_ARG(bool, flag),
    //                                  Q_ARG(McAlbumPtr, album));
    //        return flag;
    //    }
}

bool McNetworkMusicDao::getIdIfExists(McArtistPtr artist) noexcept {
    //    if (thread() == QThread::currentThread()) {
    return getIdIfExists_helper(artist);
    //    } else {
    //        bool flag = false;
    //        QMetaObject::invokeMethod(this,
    //                                  MC_STRINGIFY(getIdIfExists_helper),
    //                                  Qt::BlockingQueuedConnection,
    //                                  Q_RETURN_ARG(bool, flag),
    //                                  Q_ARG(McArtistPtr, artist));
    //        return flag;
    //    }
}

void McNetworkMusicDao::addAlbum(McAlbumPtr album) noexcept {
    //    if (thread() == QThread::currentThread()) {
    addAlbum_helper(album);
    //    } else {
    //        QMetaObject::invokeMethod(this,
    //                                  MC_STRINGIFY(addAlbum_helper),
    //                                  Qt::BlockingQueuedConnection,
    //                                  Q_ARG(McAlbumPtr, album));
    //    }
}

void McNetworkMusicDao::addArtist(McArtistPtr artist) noexcept
{
    //    if (thread() == QThread::currentThread()) {
    addArtist_helper(artist);
    //    } else {
    //        QMetaObject::invokeMethod(this,
    //                                  MC_STRINGIFY(addArtist_helper),
    //                                  Qt::BlockingQueuedConnection,
    //                                  Q_ARG(McArtistPtr, artist));
    //    }
}

void McNetworkMusicDao::addMusic(McMusicPtr music) noexcept
{
    //    if (thread() == QThread::currentThread()) {
    addMusic_helper(music);
    //    } else {
    //        QMetaObject::invokeMethod(this,
    //                                  MC_STRINGIFY(addMusic_helper),
    //                                  Qt::BlockingQueuedConnection,
    //                                  Q_ARG(McMusicPtr, music));
    //    }
}

int McNetworkMusicDao::getMaxAlbumId() noexcept
{
    //    if (thread() == QThread::currentThread()) {
    return getMaxAlbumId_helper();
    //    } else {
    //        int flag = 0;
    //        QMetaObject::invokeMethod(this,
    //                                  MC_STRINGIFY(getMaxAlbumId_helper),
    //                                  Qt::BlockingQueuedConnection,
    //                                  Q_RETURN_ARG(int, flag));
    //        return flag;
    //    }
}

int McNetworkMusicDao::getMaxArtistId() noexcept
{
    //    if (thread() == QThread::currentThread()) {
    return getMaxArtistId_helper();
    //    } else {
    //        int flag = 0;
    //        QMetaObject::invokeMethod(this,
    //                                  MC_STRINGIFY(getMaxArtistId_helper),
    //                                  Qt::BlockingQueuedConnection,
    //                                  Q_RETURN_ARG(int, flag));
    //        return flag;
    //    }
}

bool McNetworkMusicDao::getIdIfExistsForUrl_helper(McMusicPtr music) noexcept
{
    music->setId(-1);
    if (music->getSongUrl().isEmpty()) {
        qInfo() << "song url cannot be empty";
        return true; // 如果音乐的url不存在，则直接报错并返回true，表示阻止后续操作
    }
    McMusicPo_ptr musicPo(new McMusicPo());
    qx::QxSqlQuery query("SELECT song_index FROM `t_music_info` WHERE song_url = :songUrl");
    query.bind(":songUrl", music->getSongUrl());
    QSqlError error = qx::dao::execute_query(query, musicPo);
    if (error.type() != QSqlError::NoError) {
        qCritical() << "getIdIfExistsForUrl exec query error. type:" << error.type()
                    << "str:" << error.text();
        return true; // 如果发生错误则返回true，表示不允许进行后续操作
    }
    if (musicPo->m_songIndex == 0)
        return false;
    else {
        music->setId(musicPo->m_songIndex);
        return true;
    }
}

bool McNetworkMusicDao::getIdIfExists_helper(McMusicPtr music) noexcept
{
    music->setId(-1);
    McMusicDetailPo_ptr musicDetailPo(new McMusicDetailPo());
    qx::QxSqlQuery query(
        "SELECT song_index FROM `t_music_detail_info` WHERE song_src = :songSrc AND (song_id IS "
        "NULL OR song_id = :songId) AND (song_mid IS NULL OR song_mid = :songMid)");
    query.bind(":songSrc", music->getSongSrc());
    query.bind(":songId", music->getSongId());
    query.bind(":songMid", music->getSongMid());
    QSqlError error = qx::dao::execute_query(query, musicDetailPo);
    if (error.type() != QSqlError::NoError) {
        qCritical() << "getIdIfExists exec query error. type:" << error.type()
                    << "str:" << error.text();
        return true; // 如果发生错误则返回true，表示不允许进行后续操作
    }
    if (musicDetailPo->m_songIndex == 0)
        return false;
    else {
        music->setId(musicDetailPo->m_songIndex);
        return true;
    }
}

bool McNetworkMusicDao::getIdIfExists_helper(McAlbumPtr album) noexcept
{
    album->setId(-1);
    McAlbumPo_ptr albumPo(new McAlbumPo());
    qx::QxSqlQuery query("SELECT album_index FROM `t_album_detail_info` WHERE (album_id IS NULL OR "
                         "album_id = :albumId) AND (album_mid IS NULL OR album_mid = :albumMid)");
    query.bind(":albumId", album->getAlbumId());
    query.bind(":albumMid", album->getAlbumMid());
    QSqlError error = qx::dao::execute_query(query, albumPo);
    if (error.type() != QSqlError::NoError) {
        qCritical() << "getIdIfExists exec query error. type:" << error.type()
                    << "str:" << error.text();
        return true; // 如果发生错误则返回true，表示不允许进行后续操作
    }
    if (albumPo->m_albumIndex == 0)
        return false;
    else {
        album->setId(albumPo->m_albumIndex);
        return true;
    }
}

bool McNetworkMusicDao::getIdIfExists_helper(McArtistPtr artist) noexcept
{
    artist->setId(-1);
    McArtistPo_ptr artistPo(new McArtistPo());
    qx::QxSqlQuery query(
        "SELECT artists_index FROM `t_artists_detail_info` WHERE (artists_id IS NULL OR artists_id "
        "= :artistId) AND (artists_mid IS NULL OR artists_mid = :artistMid)");
    query.bind(":artistId", artist->getArtistId());
    query.bind(":artistMid", artist->getArtistMid());
    QSqlError error = qx::dao::execute_query(query, artistPo);
    if (error.type() != QSqlError::NoError) {
        qCritical() << "getIdIfExists exec query error. type:" << error.type()
                    << "str:" << error.text();
        return true; // 如果发生错误则返回true，表示不允许进行后续操作
    }
    if (artistPo->m_artistIndex == 0)
        return false;
    else {
        artist->setId(artistPo->m_artistIndex);
        return true;
    }
}

void McNetworkMusicDao::addAlbum_helper(McAlbumPtr album) noexcept
{
    McAlbumPo_ptr albumPo(new McAlbumPo());
    qx::QxSqlQuery query(
        "INSERT INTO `t_album_detail_info` (album_index, album_id, album_mid, album_name, "
        "album_title, album_title_hilight) "
        "VALUES(:albumIndex, :albumId, :albumMid, :albumName, :albumTitle, :albumTitleHilight)");
    query.bind(":albumIndex", album->getId());
    query.bind(":albumId", album->getAlbumId());
    query.bind(":albumMid", album->getAlbumMid());
    query.bind(":albumName", album->getAlbumName());
    query.bind(":albumTitle", album->getAlbumTitle());
    query.bind(":albumTitleHilight", album->getAlbumTitleHilight());
    QSqlError error = qx::dao::execute_query(query, albumPo);
    if (error.type() != QSqlError::NoError)
        qCritical() << "addAlbum exec query error. type:" << error.type() << "str:" << error.text();
}

void McNetworkMusicDao::addArtist_helper(McArtistPtr artist) noexcept
{
    McArtistPo_ptr artistPo(new McArtistPo());
    qx::QxSqlQuery query("INSERT INTO `t_artists_detail_info` (artists_index, artists_id, "
                         "artists_mid, artists_name, artists_title, artists_title_hilight) "
                         "VALUES(:artistIndex, :artistId, :artistMid, :artistName, :artistTitle, "
                         ":artistTitleHilight)");
    query.bind(":artistIndex", artist->getId());
    query.bind(":artistId", artist->getArtistId());
    query.bind(":artistMid", artist->getArtistMid());
    query.bind(":artistName", artist->getArtistName());
    query.bind(":artistTitle", artist->getArtistTitle());
    query.bind(":artistTitleHilight", artist->getArtistTitleHilight());
    QSqlError error = qx::dao::execute_query(query, artistPo);
    if (error.type() != QSqlError::NoError)
        qCritical() << "addArtist exec query error. type:" << error.type()
                    << "str:" << error.text();
}

void McNetworkMusicDao::addMusic_helper(McMusicPtr music) noexcept
{
    McMusicPo_ptr musicPo(new McMusicPo());
    qx::QxSqlQuery query("INSERT INTO `t_music_info` (song_index, song_title, song_url) "
                         "VALUES(:songIndex, :songTitle, :songUrl)");
    query.bind(":songIndex", music->getId());
    query.bind(":songTitle", music->getSongTitle());
    query.bind(":songUrl", music->getSongUrl());
    QSqlError error = qx::dao::execute_query(query, musicPo);
    if (error.type() != QSqlError::NoError) {
        qCritical() << "addMusic exec query error. type:" << error.type() << "str:" << error.text();
        return; // 如果发生错误则返回，表示不允许进行后续操作
    }
    McMusicDetailPo_ptr musicDetailPo(new McMusicDetailPo());
    query = "INSERT INTO `t_music_detail_info` (song_index, song_src, song_id, song_mid, "
            "song_name, song_title_hilight) "
            "VALUES(:songIndex, :songSrc, :songId, :songMid, :songName, :songTitleHilight)";
    query.bind(":songIndex", music->getId());
    query.bind(":songSrc", music->getSongSrc());
    query.bind(":songId", music->getSongId());
    query.bind(":songMid", music->getSongMid());
    query.bind(":songName", music->getSongName());
    query.bind(":songTitleHilight", music->getSongTitleHilight());
    error = qx::dao::execute_query(query, musicDetailPo);
    if (error.type() != QSqlError::NoError) {
        qCritical() << "addMusic exec query error. type:" << error.type() << "str:" << error.text();
        return; // 如果发生错误则返回，表示不允许进行后续操作
    }

    McAlbumPtr album = music->getAlbum();
    if (album) {
        query = "UPDATE `t_music_info` SET album_index = :albumIndex WHERE song_index = :songIndex";
        query.bind(":albumIndex", album->getId());
        query.bind(":songIndex", music->getId());
        error = qx::dao::execute_query(query, musicPo);
        if (error.type() != QSqlError::NoError) {
            qCritical() << "addMusic exec query error. type:" << error.type()
                        << "str:" << error.text();
            return; // 如果发生错误则返回，表示不允许进行后续操作
        }
    }
    QList<McArtistPtr> artists = music->getArtists();
    McArtistPo_ptr artistPo(new McArtistPo());
    for (auto artist : artists) {
        query = "INSERT INTO `t_artists_info` (song_index, artists_index) "
                "VALUES(:songIndex, :artistIndex)";
        query.bind(":songIndex", music->getId());
        query.bind(":artistIndex", artist->getId());
        error = qx::dao::execute_query(query, artistPo);
        if (error.type() != QSqlError::NoError) {
            qCritical() << "addMusic exec query error. type:" << error.type()
                        << "str:" << error.text();
            return; // 如果发生错误则返回，表示不允许进行后续操作
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

int McNetworkMusicDao::getMaxAlbumId_helper() noexcept
{
    McAlbumPo_ptr albumPo(new McAlbumPo());
    qx::QxSqlQuery query("SELECT MAX(album_index) AS album_index FROM `t_album_detail_info`");
    QSqlError error = qx::dao::execute_query(query, albumPo);
    if (error.type() != QSqlError::NoError) {
        qCritical() << "getMaxAlbumId exec query error. type:" << error.type()
                    << "str:" << error.text();
        return -1; // 如果发生错误则返回-1，表示不允许进行后续操作
    }
    return albumPo->m_albumIndex;
}

int McNetworkMusicDao::getMaxArtistId_helper() noexcept
{
    McArtistPo_ptr artistPo(new McArtistPo());
    qx::QxSqlQuery query("SELECT MAX(artists_index) AS artists_index FROM `t_artists_detail_info`");
    QSqlError error = qx::dao::execute_query(query, artistPo);
    if (error.type() != QSqlError::NoError) {
        qCritical() << "getMaxArtistId exec query error. type:" << error.type()
                    << "str:" << error.text();
        return -1; // 如果发生错误则返回-1，表示不允许进行后续操作
    }
    return artistPo->m_artistIndex;
}
