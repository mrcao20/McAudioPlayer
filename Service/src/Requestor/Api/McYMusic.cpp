#include "Service/Requestor/Api/impl/McYMusic.h"

#include <QDir>
#include <QJSEngine>
#include <QJsonArray>
#include <QJsonObject>

#include "Service/Domain/Vo/McAlbum.h"
#include "Service/Domain/Vo/McArtist.h"
#include "Service/Domain/Vo/McMusic.h"
#include "Service/McGlobal.h"
#include "Service/Utils/McNetUtils.h"

#define SONG_LINK "http://music.163.com/song/media/outer/url?id=%1"
#define SONG_LINK_GET "https://music.163.com/weapi/song/enhance/player/url"
#define SEARCH_SONG_POST "http://music.163.com/api/search/get"

MC_DECL_PRIVATE_DATA(McYMusic)
QJSEngine jsEngine;
QJSValue encryptValue;
QString pubKey = "010001";
QString modulus
    = "00e0b509f6259df8642dbc35662901477df22677ec152b5ff68ace615bb7b725152b3ab17a876aea8a5aa76d2e41"
      "7629ec4ee341f56135fccf695280104e0312ecbda92557c93870114af6c9d05c4f7f0c3685b7a46bee255932575c"
      "ce10b424d813cfe4875d3e82047b97ddef52741d546b8e289dc6935b3ece0462db0a22b8e7";
QString aesKey = "0CoJUm6Qyw8W8jud";
MC_DECL_PRIVATE_DATA_END

MC_INIT(McYMusic)
MC_REGISTER_BEAN_FACTORY(McYMusic);
MC_INIT_END

McYMusic::McYMusic() noexcept
{
    MC_NEW_PRIVATE_DATA(McYMusic);

    QDir dir(":/crypto-js");
    auto fileInfos = dir.entryInfoList(QDir::Files);
    for (auto fileInfo : fileInfos) {
        auto path = fileInfo.absoluteFilePath();
        if (!path.endsWith(".js")) {
            continue;
        }
        qInfo() << "found crypto-js file:" << path;
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        d->jsEngine.evaluate(file.readAll());
    }
    auto module = d->jsEngine.importModule(":/Encrypt.mjs");
    d->encryptValue = module.property("d");
}

McYMusic::~McYMusic() noexcept {
}

QString McYMusic::getUrl(McMusicConstPtrRef music) noexcept {
    QString songId = music->getSongId();
    /*!
        原音乐源地址仍然可用，但无法下载
        现适应网易云音乐的加密传输，通过加密算法重新获取音乐源，已可下载
        原地址被淘汰，但仍可用，继续保留
        2018-8-31: 由于新api存在加密步骤会拖慢速度，故重新启用原歌曲api，新加密api单独被用作下载链接
    */
    return QString(SONG_LINK).arg(songId);
}

QString McYMusic::getDownloadLink(McMusicConstPtrRef music) noexcept
{
    return getDownloadLinkNew(music);
}

QList<McMusicPtr> McYMusic::getMusics(const QString &songName, int limit, int offset) noexcept
{
    return getMusics(songName, limit, offset, "1", true);
}

QList<McMusicPtr> McYMusic::getMusics(const QString& songName, int limit, int offset, const QString& type, bool total) noexcept {
    QList<McMusicPtr> musics;
    musics.reserve(limit);
    QByteArray postData;
    postData.append(QString("s=%1&").arg(songName));
    postData.append(QString("offset=%1&").arg(offset));
    postData.append(QString("type=%1&").arg(type));
    postData.append(QString("limit=%1&").arg(limit));
    postData.append(QString("total=%1").arg(total));
    QByteArray json = McNetUtils::getNetworkData(SEARCH_SONG_POST, postData);
    QJsonArray jsonArray = getJsonValue(json, "result.songs").toArray();
    for (auto itr = jsonArray.constBegin(), itrEnd = jsonArray.constEnd(); itr != itrEnd; ++itr) {
        QJsonObject jsonObject = itr->toObject();
        McMusicPtr music = McMusicPtr::create();
        music->setSongTitle(getJsonValue(jsonObject, "name").toString());
        music->setSongSrc(MC_SONG_SRC_YMUSIC);
        music->setSongId(QString::number(getJsonValue(jsonObject, "id").toInt()));
        music->setSongName(music->getSongTitle());
        music->setSongTitleHilight(music->getSongTitle());
        // 由于网易云音乐获取url甚至不需要做任何请求或计算，只需要拼接，故此处提前获取url
        music->setSongUrl(getUrl(music));
        McAlbumPtr album = McAlbumPtr::create();
        album->setAlbumId(QString::number(getJsonValue(jsonObject, "album.id").toInt()));
        album->setAlbumName(getJsonValue(jsonObject, "album.name").toString());
        album->setAlbumTitle(album->getAlbumName());
        album->setAlbumTitleHilight(album->getAlbumName());
        music->setAlbum(album);
        QJsonArray artistsJson = getJsonValue(jsonObject, "artists").toArray();
        for (auto aitr = artistsJson.constBegin(), aitrEnd = artistsJson.constEnd(); aitr != aitrEnd; ++aitr) {
            QJsonObject artistJsonObj = aitr->toObject();
            McArtistPtr artist = McArtistPtr::create();
            artist->setArtistId(QString::number(getJsonValue(artistJsonObj, "id").toInt()));
            artist->setArtistName(getJsonValue(artistJsonObj, "name").toString());
            artist->setArtistTitle(artist->getArtistName());
            artist->setArtistTitleHilight(artist->getArtistName());
            music->addArtist(artist);
        }
        musics.append(music);
    }
    return musics;
}

QString McYMusic::getDownloadLinkOld(McMusicConstPtrRef music) noexcept
{
    QString text = QString("{\"ids\":\"[%1]\",\"br\":128000,\"csrf_token\":\"\"}")
                       .arg(music->getSongId());
    QJSValueList args;
    args << text << d->pubKey << d->modulus << d->aesKey;
    auto result = d->encryptValue.call(args);
    QString encSecKey = result.property("encSecKey").toString();
    QString params = result.property("encText").toString();
    QMap<QByteArray, QByteArray> header;
    header["Referer"] = "https://music.163.com/";
    header["Host"] = "music.163.com";
    header["User-Agent"] = "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like "
                           "Gecko) Chrome/55.0.2883.87 Safari/537.36";
    header["cookie"]
        = "_ntes_nnid=f90ae9cb7692708641bbc58d6aa1719f,1505378239692; "
          "_ntes_nuid=f90ae9cb7692708641bbc58d6aa1719f; usertrack=c+xxC1nCJL0bNO4sAyhzAg==; "
          "vjuids=20e641b02.160df20dacd.0.00ee9d7e5eea3; vjlast=1515571961.1515571961.30; "
          "vinfo_n_f_l_n3=023c1ffb968dafb7.1.1.1514350738841.1514350745255.1515572109538; "
          "__guid=94650624.319761818276852900.1520926652843.5322; _ga=GA1.2.1299166061.1506414430; "
          "jsessionid-cpta=CNVtHPRGhOEWWbFnS3yb1DvnNnJdL%"
          "5C714f4ZiXZdn7hcDVk5P4AhVXNAlhL6LN6wTdpxaBxv1buU56ZlVci4bOnFM1iyS0r4fazhWhjN3JdZS%"
          "5Co78P%2FfGGpA%2FzkOWyGK2L%2FSf%5Cj7eay1kgUI8V8rQ1FDLfqxfk3d8HadHk1TkLXr4qJX%"
          "3A1526297054246; c98xpt_=30; NETEASE_WDA_UID=1457427762#|#1526296163428; "
          "mp_MA-9ADA-91BF1A6C9E06_hubble=%7B%22sessionReferrer%22%3A%20%22https%3A%2F%2Fcampus."
          "163.com%2Fapp%2Fcampus%2Frecruitment4campus%22%2C%22updatedTime%22%3A%201532341816860%"
          "2C%22sessionStartTime%22%3A%201532341779709%2C%22sendNumClass%22%3A%20%7B%22allNum%22%"
          "3A%203%2C%22errSendNum%22%3A%200%7D%2C%22deviceUdid%22%3A%20%22b4b50ab2-cbf3-4ca5-9a6f-"
          "65dc20a7c01e%22%2C%22persistedTime%22%3A%201532341672744%2C%22LASTEVENT%22%3A%20%7B%"
          "22eventId%22%3A%20%22da_screen%22%2C%22time%22%3A%201532341816860%7D%2C%22sessionUuid%"
          "22%3A%20%2272bb7d24-669a-4cd5-b516-a0cad35a70ce%22%7D; __f_=1533041890126; "
          "playerid=87458816; "
          "JSESSIONID-WYYY=3RksMK%2FzEnIEGz7t1UMgbk%"
          "2FaJ8zfM0y8MU5smtCNhw1qQEQCK9u9gdJ4Q3Rwgm5y8UcqVfNzYX%"
          "5CIUuYzHwXkqfVQSGNjrZGym9Sj2doVn3M%2B%5Cu93NSn9KMclJ5MvHk%2BVVPr%5C3MgtIMxVmDR%2B%"
          "5CT7mktxTA8Fs7xj8yEbgh8csMoFdBSd0%3A1535509954005; _iuqxldmzr_=32; "
          "WM_NI=yi5ZKr631w%2FGz%2FTfWOYQxrWu5eZNPVPBUoGQBLewqBG5Cg%2FyHeh9XorlOzSb2TJG%2FXq%"
          "2BJQSLiJHFTfjyqFgZZoNv6hHEFYU%2BM3t6ozEQhyw8F8c6eeMGMEtHW7ckvrGaQ28%3D; "
          "WM_NIKE="
          "9ca17ae2e6ffcda170e2e6ee95c65ab89c86abb44af187978bc44293bff7abcc6ab4efb890b36a94b681d4d5"
          "2af0fea7c3b92abbb7fbbbca7af6edff98ae4dbaf19c87d6459b8fb893d67ff7bb96afd35e949e9b90c65b82"
          "94ab98f44a85eb8d88ae738cbba8dadb65b2b4819bd26af28c86a8ae54b3f586b2d248ab9688a7d76eaaa7bf"
          "a7e6529ab18297b5648c9b8abad8218fedbcd7ee72878fa89af63486e8add7e86f8f9983a6f74495e9ad8cf5"
          "7a85bf9fd3bb37e2a3; WM_TID=hNFPe0KZYLEdcwbOXhJOFJm9drjhBQ7P; "
          "MUSIC_U="
          "294c416fff82565ad632d4f8a67c6053b57ded44bba3973b5fd6c9a693e47173b90ac4896782651e16835d5f"
          "24772e273c9f63c2381ce2d9c3061cd18d77b7a0; __remember_me=true; "
          "__csrf=86c53a2474543be2df153b4c558e3bf2; "
          "__utma=94650624.1090234970.1505378241.1535502934.1535507106.42; "
          "__utmb=94650624.27.10.1535507106; __utmc=94650624; "
          "__utmz=94650624.1535502934.41.39.utmcsr=baidu|utmccn=(organic)|utmcmd=organic; "
          "monitor_count=12";
    QByteArray postData;
    postData.append(QString("params=%1&").arg(params));
    postData.append(QString("encSecKey=%1").arg(encSecKey));
    QByteArray json = McNetUtils::getNetworkData(SONG_LINK_GET, postData, header);
    QString songLink = getJsonValue(json, "data.url").toString();
    return songLink;
}

QString McYMusic::getDownloadLinkNew(McMusicConstPtrRef music) noexcept
{
    auto headers = McNetUtils::getResponseHeader(music->getSongUrl());
    for (auto header : headers) {
        if (header.first == "Location") {
            return header.second;
        }
    }
    return "";
}
