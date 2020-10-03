#include "Service/Controller/McNetworkMusicController.h"

#include <QDebug>

#include "Service/Service/IMcNetworkMusicService.h"
#include "Service/Service/IMcPlaylistService.h"
#include "Service/Domain/Vo/McMusic.h"

MC_DECL_PRIVATE_DATA(McNetworkMusicController)
IMcNetworkMusicServicePtr networkMusicService;
IMcPlaylistServicePtr playlistService;
MC_DECL_PRIVATE_DATA_END

MC_INIT(McNetworkMusicController)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McNetworkMusicController));
MC_INIT_END

McNetworkMusicController::McNetworkMusicController() noexcept
{
    MC_NEW_PRIVATE_DATA(McNetworkMusicController);
}

McNetworkMusicController::~McNetworkMusicController() noexcept{
}

IMcNetworkMusicServicePtr McNetworkMusicController::networkMusicService() const noexcept {
    return d->networkMusicService;
}

void McNetworkMusicController::setNetworkMusicService(IMcNetworkMusicServiceConstPtrRef val) noexcept {
    d->networkMusicService = val;
}

IMcPlaylistServicePtr McNetworkMusicController::playlistService() const noexcept {
    return d->playlistService;
}

void McNetworkMusicController::setPlaylistService(IMcPlaylistServiceConstPtrRef val) noexcept {
    d->playlistService = val;
}

QAbstractItemModel *McNetworkMusicController::getModel() const noexcept {
    return  d->networkMusicService->getModel();
}

int McNetworkMusicController::getIndex(const McMusicPtr music) const noexcept {
    qInfo() << "get network index. muisc title:" << music->getSongTitle();
    return d->networkMusicService->getIndex(music);
}

void McNetworkMusicController::getNetworkMusics(
        const QString &musicSrc, const QString &keyword) noexcept {
    
    qInfo() << "get network musics. muisc src:" << musicSrc
            << "keyword:" << keyword;
    d->networkMusicService->getNetworkMusics(musicSrc, keyword);
}

void McNetworkMusicController::addToPlaylist(const QList<int> &indexs, int songSheetId) noexcept {
    qInfo() << "addToPlaylist. indexs:" << indexs
            << "songSheetId:" << songSheetId;
    auto musics = d->networkMusicService->getMusics(indexs);
    qInfo() << "songlist service get music length:" << musics.length();
    d->playlistService->setMusics(musics, songSheetId);
}

void McNetworkMusicController::addToSongSheet(int songSheetId, const QList<int> &indexs) noexcept {
    qInfo() << "addToSongSheet. songSheetId:" << songSheetId
            << "indexs:" << indexs;
    d->networkMusicService->addToSongSheet(songSheetId, indexs);
}

void McNetworkMusicController::getLastPageMusic() noexcept {
    qInfo() << "getLastPageMusic";
    d->networkMusicService->getLastPageMusic();
}

void McNetworkMusicController::getNextPageMusic() noexcept {
    qInfo() << "getNextPageMusic";
    d->networkMusicService->getNextPageMusic();
}

void McNetworkMusicController::clearModel() noexcept {
    qInfo() << "clearModel";
    d->networkMusicService->clearModel();
}
