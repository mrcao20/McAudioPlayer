#include "Service/Controller/McSonglistController.h"

#include <QDebug>

#include "Service/Service/IMcSonglistService.h"
#include "Service/Service/IMcPlaylistService.h"
#include "Service/Domain/Vo/McMusic.h"

MC_DECL_PRIVATE_DATA(McSonglistController)
IMcSonglistServicePtr songlistService;
IMcPlaylistServicePtr playlistService;
MC_DECL_PRIVATE_DATA_END

MC_INIT(McSonglistController)
MC_REGISTER_BEAN_FACTORY(McSonglistController);
MC_REGISTER_LIST_CONVERTER(QList<int>);
MC_INIT_END

McSonglistController::McSonglistController() noexcept
{
    MC_NEW_PRIVATE_DATA(McSonglistController);
}

McSonglistController::~McSonglistController() noexcept {
}

IMcSonglistServicePtr McSonglistController::songlistService() const noexcept {
    return d->songlistService;
}

void McSonglistController::setSonglistService(IMcSonglistServiceConstPtrRef val) noexcept {
    d->songlistService = val;
}

IMcPlaylistServicePtr McSonglistController::playlistService() const noexcept {
    return d->playlistService;
}

void McSonglistController::setPlaylistService(IMcPlaylistServiceConstPtrRef val) noexcept {
    d->playlistService = val;
}

QAbstractItemModel *McSonglistController::getModel() const noexcept {
    return d->songlistService->getModel();
}

void McSonglistController::reloadMusic(int songSheetId) noexcept {
    qInfo() << "reload music. the songSheetId:" << songSheetId;
    d->songlistService->reloadMusic(songSheetId);
}

void McSonglistController::addToPlaylist(int songSheetId) noexcept {
    qInfo() << "addToPlaylist. songSheetId:" << songSheetId;
    auto musics = d->songlistService->getMusics();
    qInfo() << "songlist service get music length:" << musics.length();
    d->playlistService->setMusics(musics, songSheetId);
}

int McSonglistController::getIndex(const McMusicPtr &music) noexcept {
    qInfo() << "getIndex. id:" << music->getId()
            << "name:" << music->getSongTitle();
    return d->songlistService->getIndex(music);
}

void McSonglistController::addToSongSheet(int songSheetId, const QList<int> &indexs) noexcept {
    qInfo() << "addToSongSheet. songSheetId:" << songSheetId << "indexs:" << indexs;
    d->songlistService->addToSongSheet(songSheetId, indexs);
}

void McSonglistController::removeFromSongSheet(int songSheetId, const QList<int>& indexs) noexcept {
    qInfo() << "removeFromSongSheet. songSheetId:" << songSheetId << "indexs:" << indexs;
    d->songlistService->removeFromSongSheet(songSheetId, indexs);
}
