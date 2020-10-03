#include "Service/Requestor/impl/McNetMusicRequestor.h"

#include <QDebug>

#include "Service/Requestor/Api/IMcMusicApi.h"
#include "Service/Domain/Vo/McMusic.h"

MC_DECL_PRIVATE_DATA(McNetMusicRequestor)
QMap<QString, IMcMusicApiPtr> musicApis;
QString musicSrc;
QString keyword;
int currentPage{1};
MC_PADDING_CLANG(4)
MC_DECL_PRIVATE_DATA_END

MC_INIT(McNetMusicRequestor)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McNetMusicRequestor));
MC_REGISTER_MAP_CONVERTER(McMusicApis);
MC_INIT_END

McNetMusicRequestor::McNetMusicRequestor() noexcept
{
    MC_NEW_PRIVATE_DATA(McNetMusicRequestor);
}

McNetMusicRequestor::~McNetMusicRequestor() noexcept {
}

McMusicApis McNetMusicRequestor::musicApis() const noexcept {
    return  d->musicApis;
}

void McNetMusicRequestor::setMusicApis(const McMusicApis &val) noexcept {
    d->musicApis = val;
}

QString McNetMusicRequestor::getMusicUrl(McMusicConstPtrRef music) noexcept {
    if(music.isNull()) {
        qCritical() << "music is null";
        return "";
    }
    if(!d->musicApis.contains(music->getSongSrc())) {
        qCritical() << "not contains song src api. the src:" << music->getSongSrc()
                    << "song name:" << music->getSongTitle();
        return "";
    }
    return d->musicApis[music->getSongSrc()]->getMusicUrl(music);
}

QList<McMusicPtr> McNetMusicRequestor::getNetworkMusics(const QString &musicSrc, const QString &keyword) noexcept {
    d->musicSrc = musicSrc;
    d->keyword = keyword;
    d->currentPage = 1;
    return getNetworkMusics();
}

QList<McMusicPtr> McNetMusicRequestor::getLastPageMusic() noexcept {
    if(d->currentPage > 1) {
        --d->currentPage;
    }
    return getNetworkMusics();
}

QList<McMusicPtr> McNetMusicRequestor::getNextPageMusic() noexcept {
    ++d->currentPage;
    return getNetworkMusics();
}

QList<McMusicPtr> McNetMusicRequestor::getNetworkMusics() noexcept {
    if(!d->musicApis.contains(d->musicSrc)) {
        qCritical() << "not contains music api for:" << d->musicSrc;
        return QList<McMusicPtr>();
    }
    
    int limit = 20;
    int offset = (d->currentPage - 1) * limit;
    auto api = d->musicApis[d->musicSrc];
    return api->searchSong(d->keyword, limit, offset);
}
