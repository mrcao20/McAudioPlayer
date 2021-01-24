#include "Service/Controller/McPlaylistController.h"

#include <QDebug>

#include <McBoot/Utils/McJsonUtils.h>

#include "Service/Service/IMcPlaylistService.h"
#include "Service/Domain/Vo/McMusic.h"

MC_DECL_PRIVATE_DATA(McPlaylistController)
IMcPlaylistServicePtr playlistService;
MC_DECL_PRIVATE_DATA_END

MC_INIT(McPlaylistController)
MC_REGISTER_BEAN_FACTORY(McPlaylistController);
MC_INIT_END

McPlaylistController::McPlaylistController() noexcept
{
    MC_NEW_PRIVATE_DATA(McPlaylistController);
}

McPlaylistController::~McPlaylistController() noexcept {
}

IMcPlaylistServicePtr McPlaylistController::playlistService() const noexcept {
    return d->playlistService;
}

void McPlaylistController::setPlaylistService(IMcPlaylistServiceConstPtrRef val) noexcept {
    d->playlistService = val;
}

QAbstractItemModel *McPlaylistController::getModel() const noexcept {
    return  d->playlistService->getModel();
}

void McPlaylistController::loadPlaylist() noexcept {
    qInfo() << "loadPlaylist";
    d->playlistService->loadPlaylist();
}

QJsonObject McPlaylistController::getMusic(int index) noexcept {
    qInfo() << "get playlist music. index:" << index;
    McMusicPtr music = d->playlistService->getMusic(index);
    if(music) {
        qInfo() << "getted music. id:" << music->getId()
                << "name:" << music->getSongTitle()
                << "url:" << music->getSongUrl();
    }
    return McJsonUtils::toJson(music);
}
