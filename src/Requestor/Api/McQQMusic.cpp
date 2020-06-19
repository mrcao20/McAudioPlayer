#include "McAudioPlayer/Requestor/Api/impl/McQQMusic.h"

#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

#include "McAudioPlayer/Domain/Vo/McMusic.h"
#include "McAudioPlayer/Utils/McNetUtils.h"
#include "McAudioPlayer/Domain/Vo/McAlbum.h"
#include "McAudioPlayer/Domain/Vo/McArtist.h"
#include "McAudioPlayer/Domain/Vo/McMusic.h"
#include "McAudioPlayer/McGlobal.h"

#define VKEY "https://c.y.qq.com/base/fcgi-bin/fcg_music_express_mobile3.fcg?g_tk=1109981464&loginUin=839566521&hostUin=0&format=json&inCharset=utf8&outCharset=utf-8&notice=0&platform=yqq&needNewCode=0&cid=205361747&uin=839566521&songmid=%1&filename=%2.m4a&guid=2054016189"
#define SONG "http://dl.stream.qqmusic.qq.com/%1.m4a?vkey=%2&guid=2054016189&uin=839566521&fromtag=66"
#define SEARCH "https://c.y.qq.com/soso/fcgi-bin/client_search_cp?ct=24&qqmusic_ver=1298&new_json=1&remoteplace=txt.yqq.song&searchid=71813867590975010&t=0&aggr=1&cr=1&catZhida=1&lossless=0&flag_qc=0&n=%1&p=%2&w=%3&g_tk=5381&jsonpCallback=MusicJsonCallback031135166293541294&loginUin=0&hostUin=0&format=jsonp&inCharset=utf8&outCharset=utf-8&notice=0&platform=yqq&needNewCode=0"

MC_DECL_PRIVATE_DATA(McQQMusic)
MC_DECL_PRIVATE_DATA_END

MC_INIT(McQQMusic)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McQQMusic));
MC_INIT_END

McQQMusic::McQQMusic() noexcept
{
    MC_NEW_PRIVATE_DATA(McQQMusic);
}

McQQMusic::~McQQMusic() noexcept {
}

QString McQQMusic::getUrl(McMusicConstPtrRef music) noexcept {
    QString songMid = music->getSongMid();
    QString fileName = "C400" + songMid;
    QString vkey = QString(VKEY).arg(songMid).arg(fileName);
    QByteArray json = McNetUtils::getNetworkData(vkey);
    QString key = getJsonValue(json, "data.items.vkey").toString();
    return QString(SONG).arg(fileName).arg(key);
}

QList<McMusicPtr> McQQMusic::getMusics(const QString& songName, int limit, int offset) noexcept {
    QList<McMusicPtr> musics;
    musics.reserve(limit);
    int page = offset / limit + 1;
    QByteArray json = McNetUtils::getNetworkData(QString(SEARCH).arg(limit).arg(page).arg(songName));
    json.replace("MusicJsonCallback031135166293541294(", "");
    json.remove(json.size() - 1, 1);
    QJsonArray jsonArray = getJsonValue(json, "data.song.list").toArray();
    for (auto itr = jsonArray.begin(); itr != jsonArray.end(); itr++) {
        QJsonObject jsonObject = itr->toObject();
        McMusicPtr music = McMusicPtr::create();
        music->setSongTitle(getJsonValue(jsonObject, "title").toString());
        music->setSongSrc(MC_SONG_SRC_QQMUSIC);
        music->setSongId(QString::number(getJsonValue(jsonObject, "id").toInt()));
        music->setSongMid(getJsonValue(jsonObject, "mid").toString());
        music->setSongName(getJsonValue(jsonObject, "name").toString());
        music->setSongTitleHilight(getJsonValue(jsonObject, "title_hilight").toString());
        // 由于QQ音乐获取音乐源时请求复杂，耗时长，故此处不预先获取url
        //music->setSongUrl(getUrl(music));
        McAlbumPtr album = McAlbumPtr::create();
        album->setAlbumId(QString::number(getJsonValue(jsonObject, "album.id").toInt()));
        album->setAlbumName(getJsonValue(jsonObject, "album.mid").toString());
        album->setAlbumName(getJsonValue(jsonObject, "album.name").toString());
        album->setAlbumTitle(getJsonValue(jsonObject, "album.title").toString());
        album->setAlbumTitleHilight(getJsonValue(jsonObject, "album.title_hilight").toString());
        music->setAlbum(album);
        QJsonArray artistsJson = getJsonValue(jsonObject, "singer").toArray();
        for (auto aitr = artistsJson.constBegin(), aitrEnd = artistsJson.constEnd(); aitr != aitrEnd; ++aitr) {
            QJsonObject artistJsonObj = aitr->toObject();
            McArtistPtr artist = McArtistPtr::create();
            artist->setArtistId(QString::number(getJsonValue(artistJsonObj, "id").toInt()));
            artist->setArtistMid(getJsonValue(jsonObject, "mid").toString());
            artist->setArtistName(getJsonValue(artistJsonObj, "name").toString());
            artist->setArtistTitle(getJsonValue(artistJsonObj, "title").toString());
            artist->setArtistTitleHilight(getJsonValue(artistJsonObj, "title_hilight").toString());
            music->addArtist(artist);
        }
        musics.append(music);
    }
    return musics;
}
