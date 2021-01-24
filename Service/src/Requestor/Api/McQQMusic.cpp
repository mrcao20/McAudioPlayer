#include "Service/Requestor/Api/impl/McQQMusic.h"

#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJSEngine>
#include <QTextStream>
#include <QFile>

#include "Service/Domain/Vo/McMusic.h"
#include "Service/Utils/McNetUtils.h"
#include "Service/Domain/Vo/McAlbum.h"
#include "Service/Domain/Vo/McArtist.h"
#include "Service/Domain/Vo/McMusic.h"
#include "Service/McGlobal.h"

#define VKEY R"(https://u.y.qq.com/cgi-bin/musics.fcg?-=getplaysongvkey9598309114468244&g_tk=1319104027&sign=%1&loginUin=839566521&hostUin=0&format=json&inCharset=utf8&outCharset=utf-8&notice=0&platform=yqq.json&needNewCode=0&data=%2)"
#define SEARCH "https://c.y.qq.com/soso/fcgi-bin/client_search_cp?ct=24&qqmusic_ver=1298&new_json=1&remoteplace=txt.yqq.top&searchid=31493809849558127&t=0&aggr=1&cr=1&catZhida=1&lossless=0&flag_qc=0&n=%1&p=%2&w=%3&g_tk_new_20200303=1319104027&g_tk=1319104027&loginUin=839566521&hostUin=0&format=json&inCharset=utf8&outCharset=utf-8&notice=0&platform=yqq.json&needNewCode=0"

MC_DECL_PRIVATE_DATA(McQQMusic)
MC_DECL_PRIVATE_DATA_END

MC_INIT(McQQMusic)
MC_REGISTER_BEAN_FACTORY(McQQMusic);
MC_INIT_END

McQQMusic::McQQMusic() noexcept
{
    MC_NEW_PRIVATE_DATA(McQQMusic);
}

McQQMusic::~McQQMusic() noexcept {
}

QString McQQMusic::getUrl(McMusicConstPtrRef music) noexcept {
    QString songMid = music->getSongMid();
    QString data = QString(R"({"req_0":{"module":"vkey.GetVkeyServer","method":"CgiGetVkey","param":{"guid":"7176926105","songmid":["%1"],"songtype":[0],"uin":"839566521","loginflag":1,"platform":"20"}},"comm":{"uin":839566521,"format":"json","ct":24,"cv":0}})")
            .arg(songMid);
    QJSEngine jsEngine;
    QFile file(":/QQSignGenerator.mjs");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    QString js = stream.readAll();
    jsEngine.evaluate(js);
    auto funcValue = jsEngine.globalObject().property("getSign");
    auto jsValue = funcValue.call(QJSValueList() << data);
    auto reqUrl = QString(VKEY).arg(jsValue.toString(), data.toLocal8Bit().toPercentEncoding());
    QByteArray json = McNetUtils::getNetworkData(reqUrl);
    if(json.isEmpty()) {
        qInfo() << "get qq music url returned empty";
        return "";
    }
    auto dataObj = getJsonValue(json, "req_0.data").toObject();
    auto midurlinfo = getJsonValue(dataObj, "midurlinfo").toArray();
    auto purl = getJsonValue(midurlinfo.first().toObject(), "purl").toString();
    auto filename = getJsonValue(midurlinfo.first().toObject(), "filename").toString();
    auto sip = getJsonValue(dataObj, "sip").toArray().first().toString();
    QString url;
    if(purl.isEmpty()) {
        url = sip + filename;
    } else {
        url = sip + purl;
    }
    return url;
}

QString McQQMusic::getDownloadLink(McMusicConstPtrRef music) noexcept
{
    return getUrl(music);
}

QList<McMusicPtr> McQQMusic::getMusics(const QString& songName, int limit, int offset) noexcept {
    QList<McMusicPtr> musics;
    musics.reserve(limit);
    int page = offset / limit + 1;
    QString searchUrl = QString(SEARCH).arg(limit).arg(page).arg(songName);
    QByteArray json = McNetUtils::getNetworkData(searchUrl);
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
