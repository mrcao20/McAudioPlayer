#include "McAudioPlayer/Service/impl/McSonglistService.h"

#include <QCoreApplication>
#include <QAbstractItemModel>
#include <QFileInfo>
#include <QtConcurrent>

#include "McAudioPlayer/Model/IMcSonglistModel.h"
#include "McAudioPlayer/Service/IMcNetworkMusicService.h"
#include "McAudioPlayer/Dao/IMcSonglistDao.h"
#include "McAudioPlayer/Dao/IMcNetworkMusicDao.h"
#include "McAudioPlayer/McGlobal.h"
#include "McAudioPlayer/Domain/Vo/McMusic.h"
#include "McAudioPlayer/Domain/Vo/McAlbum.h"
#include "McAudioPlayer/Domain/Vo/McArtist.h"

MC_DECL_PRIVATE_DATA(McSonglistService)
IMcSonglistModelPtr model;
IMcNetworkMusicServicePtr networkMusicService;
IMcSonglistDaoPtr songlistDao;
IMcNetworkMusicDaoPtr networkMusicDao;
MC_DECL_PRIVATE_DATA_END

MC_INIT(McSonglistService)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McSonglistService));
MC_INIT_END

McSonglistService::McSonglistService() noexcept
{
    MC_NEW_PRIVATE_DATA(McSonglistService);
}

McSonglistService::~McSonglistService() noexcept {
}

IMcSonglistModelPtr McSonglistService::model() const noexcept {
    return d->model;
}

void McSonglistService::setModel(IMcSonglistModelConstPtrRef val) noexcept {
    d->model = val;
}

QAbstractItemModel *McSonglistService::getModel() const noexcept {
    return d->model.dynamicCast<QAbstractItemModel>().data();
}

IMcNetworkMusicServicePtr McSonglistService::networkMusicService() const noexcept {
    return d->networkMusicService;
}

void McSonglistService::setNetworkMusicService(IMcNetworkMusicServiceConstPtrRef val) noexcept {
    d->networkMusicService = val;
}

IMcSonglistDaoPtr McSonglistService::songlistDao() const noexcept {
    return d->songlistDao;
}

void McSonglistService::setSonglistDao(IMcSonglistDaoConstPtrRef val) noexcept {
    d->songlistDao = val;
}

IMcNetworkMusicDaoPtr McSonglistService::networkMusicDao() const noexcept {
    return d->networkMusicDao;
}

void McSonglistService::setNetworkMusicDao(IMcNetworkMusicDaoConstPtrRef val) noexcept {
    d->networkMusicDao = val;
}

void McSonglistService::reloadMusic(int songSheetId) noexcept {
    qApp->postEvent(this, new McCustomEvent(QEvent::Type::User, songSheetId));
}

/*!
 * \brief McSonglistService::getMusics
 * 
 * 可能会造成获取的音乐为上一个歌单的音乐
 * \return 
 */
QList<McMusicPtr> McSonglistService::getMusics() const noexcept {
    return d->model->getMusics();
}

QList<McMusicPtr> McSonglistService::getMusics(const QList<int> &indexs) const noexcept {
    QList<McMusicPtr> ms;
    for(int index : indexs) {
        ms.append(d->model->getMusic(index));
    }
    return ms;
}

int McSonglistService::getIndex(const McMusicPtr &music) noexcept {
    auto musics = d->model->getMusics();
    if (music.isNull())
        return -1;
    for (int i = 0; i < musics.size(); ++i) {
        if (music->getId() == musics.at(i)->getId())
            return i;
    }
    return -1;
}

void McSonglistService::addToSongSheet(int songSheetId, const QList<int> &indexs) noexcept {
    QList<int> copyIndexs = indexs;
    std::sort(copyIndexs.begin(), copyIndexs.end(), std::greater<int>());	// 降序排序
    for (auto index : copyIndexs) {
        auto music = d->model->getMusic(index);
        if (music.isNull())
            continue;
        if (d->songlistDao->isExists(songSheetId, music))
            continue;
        d->songlistDao->addToSongSheet(songSheetId, music);
    }
}

void McSonglistService::removeFromSongSheet(int songSheetId, const QList<int> &indexs) noexcept {
    auto ms = d->model->takeMusics(indexs);
    QtConcurrent::run([this, songSheetId, ms] {
        for (auto music : ms) {
            int songlistId = d->songlistDao->getSonglistId(songSheetId, music);
            if (songlistId <= 0)
                continue;	// 当数据库中的自增主键为零时，表示不存在该数据，小于零时表示dao访问出错
            d->songlistDao->removeSonglist(songlistId);
        }
    });
}

void McSonglistService::addNewLocalMusics(int songSheetId, const QList<QUrl> &filePaths) noexcept {
    QList<McMusicPtr> musics;
    musics.reserve(filePaths.size());
    for(auto url : filePaths) {
        McMusicPtr music = McMusicPtr::create();
        auto songName = QFileInfo(url.toLocalFile()).baseName();
        music->setId(-1);
        music->setSongTitle(songName);
        music->setSongUrl(url.toString());
        music->setSongSrc(MC_SONG_SRC_LOCAL);
        music->setSongName(songName);
        music->setSongTitleHilight(songName);
        musics.append(music);
    }
    d->model->addMusic(musics);
    
    d->networkMusicService->addToSongSheet(songSheetId, musics);
}

void McSonglistService::customEvent(QEvent *e) {
    switch (e->type()) {
    case QEvent::Type::User: {
        auto ce = static_cast<McCustomEvent *>(e);
        auto songSheetId = ce->data().value<int>();
        QList<McMusicPtr> musics = d->songlistDao->reloadMusic(songSheetId);
        d->model->setMusics(musics);
        break;
    }
    default:
        break;
    }
}
