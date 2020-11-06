#include "Service/Service/impl/McMusicService.h"

#include <QCoreApplication>
#include <QDir>
#include <QDebug>

#include <McIoc/ApplicationContext/impl/McLocalPathApplicationContext.h>

#include "Service/Requestor/IMcNetMusicRequestor.h"
#include "Service/Dao/IMcMusicDao.h"
#include "Service/Domain/Vo/McMusic.h"
#include "Service/McGlobal.h"

MC_DECL_PRIVATE_DATA(McMusicService)
IMcMusicDaoPtr musicDao;
IMcNetMusicRequestorPtr requestor;
MC_DECL_PRIVATE_DATA_END

MC_INIT(McMusicService)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McMusicService));
MC_INIT_END

McMusicService::McMusicService() noexcept
{
    MC_NEW_PRIVATE_DATA(McMusicService);
    auto configPath = QDir(qApp->applicationDirPath()).filePath(MC_NET_MUSIC_REQUESTOR_CONFIG_PATH);
    configPath = QDir::cleanPath(configPath);
    qInfo() << "the net music requestor config path:" << configPath;
    auto appCxt = McLocalPathApplicationContextPtr::create(configPath);
    d->requestor = appCxt->getBean<IMcNetMusicRequestor>("requestor");
}

McMusicService::~McMusicService() noexcept {
}

IMcMusicDaoPtr McMusicService::musicDao() const noexcept {
    return d->musicDao;
}

void McMusicService::setMusicDao(IMcMusicDaoConstPtrRef val) noexcept {
    d->musicDao = val;
}

void McMusicService::acquireMusicUrl(McMusicConstPtrRef music) noexcept {
    if(music.isNull()) {
        return;
    }
    d->musicDao->getMusicUrl(music);
    //! 如果url存在并且不为网络链接则直接返回
    //! 现版本更新后url必定为本地链接，网络音乐会先下载
    if(!music->getSongUrl().isEmpty() && !music->getSongUrl().toString().startsWith("http")) {
        return;
    }
    music->setSongUrl(QUrl());
    QString songSrc = music->getSongSrc();
    if (songSrc.isEmpty()) {
        d->musicDao->getMusicDetail(music);
        songSrc = music->getSongSrc();
    }
    if (songSrc == MC_SONG_SRC_LOCAL) {
        qInfo() << "local music not exists. music name:" << music->getSongTitle();
        return;
    }
    QString url = d->requestor->getMusicUrl(music);
    music->setSongUrl(url);
}
