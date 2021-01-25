#include "Service/Service/impl/McNetworkMusicService.h"

#include <QAbstractItemModel>
#include <QtConcurrent>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>

#include "Service/Requestor/IMcNetMusicRequestor.h"
#include "Service/Model/IMcNetworkMusicModel.h"
#include "Service/Dao/IMcSonglistDao.h"
#include "Service/Dao/IMcNetworkMusicDao.h"
#include "Service/Domain/Vo/McMusic.h"
#include "Service/Domain/Vo/McAlbum.h"
#include "Service/Domain/Vo/McArtist.h"
#include "Service/McGlobal.h"

MC_DECL_PRIVATE_DATA(McNetworkMusicService)
IMcNetworkMusicModelPtr model;
IMcSonglistDaoPtr songlistDao;
IMcNetworkMusicDaoPtr networkMusicDao;
QMutex networkMusicMtx{QMutex::Recursive};
IMcNetMusicRequestorPtr requestor;
MC_DECL_PRIVATE_DATA_END

MC_INIT(McNetworkMusicService)
MC_REGISTER_BEAN_FACTORY(McNetworkMusicService);
MC_INIT_END

McNetworkMusicService::McNetworkMusicService() noexcept
{
    MC_NEW_PRIVATE_DATA(McNetworkMusicService);
}

McNetworkMusicService::~McNetworkMusicService() noexcept {
}

IMcNetworkMusicModelPtr McNetworkMusicService::model() const noexcept {
    return d->model;
}

void McNetworkMusicService::setModel(IMcNetworkMusicModelConstPtrRef val) noexcept {
    d->model = val;
}

QAbstractItemModel *McNetworkMusicService::getModel() const noexcept {
    return d->model.dynamicCast<QAbstractItemModel>().data();
}

IMcSonglistDaoPtr McNetworkMusicService::songlistDao() const noexcept {
    return d->songlistDao;
}

void McNetworkMusicService::setSonglistDao(IMcSonglistDaoConstPtrRef val) noexcept {
    d->songlistDao = val;
}

IMcNetworkMusicDaoPtr McNetworkMusicService::networkMusicDao() const noexcept {
    return d->networkMusicDao;
}

void McNetworkMusicService::setNetworkMusicDao(IMcNetworkMusicDaoConstPtrRef val) noexcept {
    d->networkMusicDao = val;
}

/*!
 * \brief McNetworkMusicService::getMusics
 * 
 * 可能会造成获取的音乐为上一个歌单的音乐
 * \return 
 */
QList<McMusicPtr> McNetworkMusicService::getMusics() const noexcept {
    return d->model->getMusics();
}

QList<McMusicPtr> McNetworkMusicService::getMusics(const QList<int> &indexs) const noexcept {
    QList<McMusicPtr> ms;
    for(int index : indexs) {
        ms.append(d->model->getMusic(index));
    }
    return ms;
}

int McNetworkMusicService::getIndex(const McMusicPtr &music) noexcept {
    auto musics = d->model->getMusics();
    if (music.isNull())
        return -1;
    for (int i = 0; i < musics.size(); ++i) {
        if (music->getId() == musics.at(i)->getId())
            return i;
    }
    return -1;
}

void McNetworkMusicService::addToSongSheet(int songSheetId, const QList<int> &indexs) noexcept {
    auto musics = getMusics(indexs);
    addToSongSheet(songSheetId, musics);
}

void McNetworkMusicService::removeFromSongSheet(int songSheetId, const QList<int> &indexs) noexcept {
    Q_UNUSED(songSheetId);
    Q_UNUSED(indexs);
}

void McNetworkMusicService::addToSongSheet(int songSheetId, const QList<McMusicPtr> &musics) noexcept {
    QtConcurrent::run([this, songSheetId, musics](){
        QMutex mtx;
        QMutexLocker locker(&mtx);
        for(auto music : musics) {
            if (music->getSongSrc() == MC_SONG_SRC_LOCAL && (music->getSongUrl().isEmpty() || d->networkMusicDao->getIdIfExistsForUrl(music)))
                continue;
            if (music->getSongSrc() != MC_SONG_SRC_LOCAL && d->networkMusicDao->getIdIfExists(music))
                continue;
            int maxMusicId = d->songlistDao->getMaxMusicId();
            int maxAlbumId = d->networkMusicDao->getMaxAlbumId();
            int maxArtistId = d->networkMusicDao->getMaxArtistId();
            if (maxMusicId < 0 || maxAlbumId < 0 || maxArtistId < 0)
                continue;
            auto album = music->getAlbum();
            if (album && !d->networkMusicDao->getIdIfExists(album)) {
                // 先添加album
                album->setId(maxAlbumId + 1);
                d->networkMusicDao->addAlbum(music->getAlbum());
            }
            // 再添加artist
            auto artists = music->getArtists();
            for (auto artist : artists) {
                if (!d->networkMusicDao->getIdIfExists(artist)) {
                    artist->setId(++maxArtistId);
                    d->networkMusicDao->addArtist(artist);
                }
            }
            // 最后添加music
            music->setId(maxMusicId + 1);
            d->networkMusicDao->addMusic(music);
            d->songlistDao->addToSongSheet(songSheetId, music);
        }
    });
}

void McNetworkMusicService::getNetworkMusics(const QString &musicSrc, const QString &keyword) noexcept {
    QMutexLocker locker(&d->networkMusicMtx);
    auto ms = d->requestor->getNetworkMusics(musicSrc, keyword);
    d->model->setMusics(ms);
}

void McNetworkMusicService::getLastPageMusic() noexcept {
    QMutexLocker locker(&d->networkMusicMtx);
    auto ms = d->requestor->getLastPageMusic();
    d->model->setMusics(ms);
}

void McNetworkMusicService::getNextPageMusic() noexcept {
    QMutexLocker locker(&d->networkMusicMtx);
    auto ms = d->requestor->getNextPageMusic();
    d->model->setMusics(ms);
}

void McNetworkMusicService::clearModel() noexcept {
    
}

#include "moc_McNetworkMusicService.cpp"
