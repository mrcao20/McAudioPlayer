#include "McAudioPlayer/Service/impl/McPlaylistService.h"

#include <QAbstractItemModel>
#include <QtConcurrent>
#include <QDebug>

#include "McAudioPlayer/Service/IMcMusicService.h"
#include "McAudioPlayer/Model/IMcPlaylistModel.h"
#include "McAudioPlayer/Dao/IMcPlaylistDao.h"
#include "McAudioPlayer/Domain/Vo/McMusic.h"

MC_DECL_PRIVATE_DATA(McPlaylistService)
IMcMusicServicePtr musicService;
IMcPlaylistModelPtr model;
IMcPlaylistDaoPtr playlistDao;
MC_DECL_PRIVATE_DATA_END

MC_INIT(McPlaylistService)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McPlaylistService));
MC_INIT_END

McPlaylistService::McPlaylistService() noexcept
{
    MC_NEW_PRIVATE_DATA(McPlaylistService);
}

McPlaylistService::~McPlaylistService() noexcept {
}

IMcMusicServicePtr McPlaylistService::musicService() const noexcept {
    return d->musicService;
}

void McPlaylistService::setMusicService(IMcMusicServiceConstPtrRef val) noexcept {
    d->musicService = val;
}

IMcPlaylistModelPtr McPlaylistService::model() const noexcept {
    return d->model;
}

void McPlaylistService::setModel(IMcPlaylistModelConstPtrRef val) noexcept {
    d->model = val;
}

QAbstractItemModel *McPlaylistService::getModel() const noexcept {
    return d->model.dynamicCast<QAbstractItemModel>().data();
}

IMcPlaylistDaoPtr McPlaylistService::playlistDao() const noexcept {
    return d->playlistDao;
}

void McPlaylistService::setPlaylistDao(IMcPlaylistDaoConstPtrRef val) noexcept {
    d->playlistDao = val;
}

void McPlaylistService::loadPlaylist() noexcept {
    QList<McMusicPtr> musics = d->playlistDao->reloadMusic();
    d->model->setMusics(musics);
}

void McPlaylistService::setMusics(const QList<McMusicPtr> &musics, int songSheetId) noexcept {
    auto oldMusics = d->model->getMusics();
    if (isSame(musics, oldMusics))
        return;
    d->model->setMusics(musics);
    QtConcurrent::run([this, musics, songSheetId] {
        if (!d->playlistDao->deleteAll())	// 发生错误
            return;
        d->playlistDao->setMusics(musics, songSheetId);
    });
}

McMusicPtr McPlaylistService::getMusic(int index) noexcept {
    auto music = d->model->getMusic(index);
    d->musicService->acquireMusicUrl(music);
    if(!music.isNull()) {
        qInfo() << "getted music url:" << music->getSongUrl();
        if(music->getSongUrl().isEmpty()) {
            qInfo() << "get empty music url. song name:" << music->getSongTitle();
            music.reset();
        }
    }
    return music;
}

bool McPlaylistService::isSame(const QList<McMusicPtr> &musics, const QList<McMusicPtr> &oldMusics) noexcept {
    if (oldMusics.length() != musics.length())
        return false;
    for (int i = 0; i < oldMusics.length(); ++i) {
        auto curMusic = oldMusics.at(i);
        auto music = musics.at(i);
        if (curMusic->getId() != music->getId() || curMusic->getId() <= 0 || music->getId() <= 0)
            return false;
    }
    return true;
}
