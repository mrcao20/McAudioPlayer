#include "McYMusic.h"

#include <qjsonvalue.h>
#include <qjsonarray.h>
#include <qjsonobject.h>

#include "McContainerGlobal.h"
#include "McNetUtils.h"
#include "McMusic.h"
#include "McAlbum.h"
#include "McArtist.h"
#include "McGlobal.h"

#define SONG_LINK "http://music.163.com/song/media/outer/url?id=%1"
#define SEARCH_SONG_POST "http://music.163.com/api/search/get"

MC_STATIC(McYMusic)
mcRegisterComponent<McYMusic*, IMcMusicApi*>("McYMusic", "yMusic");
MC_STATIC_END

McYMusic::McYMusic(QObject *parent)
	: McAbstractMusic(parent)
{
}

McYMusic::~McYMusic(){
}

QString McYMusic::getUrl(const McMusic* music) noexcept {
	QString songId = music->getSongId();
	/*
		原音乐源地址仍然可用，但无法下载
		现适应网易云音乐的加密传输，通过加密算法重新获取音乐源，已可下载
		原地址被淘汰，但仍可用，继续保留
		2018-8-31: 由于新api存在加密步骤会拖慢速度，故重新启用原歌曲api，新加密api单独被用作下载链接
	*/
	return QString(SONG_LINK).arg(songId);
}

void McYMusic::getMusics(QList<McMusic*>& musics, const QString& songName, int limit, int offset) noexcept {
	getMusics(musics, songName, limit, offset, "1", true);
}

void McYMusic::getMusics(QList<McMusic*>& musics, const QString& songName, int limit, int offset, const QString& type, bool total) noexcept {
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
		McMusic* music = new McMusic();
		music->setSongTitle(getJsonValue(jsonObject, "name").toString());
		music->setSongSrc(MC_SONG_SRC_YMUSIC);
		music->setSongId(QString::number(getJsonValue(jsonObject, "id").toInt()));
		music->setSongName(music->getSongTitle());
		music->setSongTitleHilight(music->getSongTitle());
		// 由于网易云音乐获取url甚至不需要做任何请求或计算，只需要拼接，故此处提前获取url
		music->setSongUrl(getUrl(music));
		McAlbum* album = new McAlbum();
		album->setAlbumId(QString::number(getJsonValue(jsonObject, "album.id").toInt()));
		album->setAlbumName(getJsonValue(jsonObject, "album.name").toString());
		album->setAlbumTitle(album->getAlbumName());
		album->setAlbumTitleHilight(album->getAlbumName());
		music->setAlbum(album);
		QJsonArray artistsJson = getJsonValue(jsonObject, "artists").toArray();
		for (auto aitr = artistsJson.constBegin(), aitrEnd = artistsJson.constEnd(); aitr != aitrEnd; ++aitr) {
			QJsonObject artistJsonObj = aitr->toObject();
			McArtist* artist = new McArtist();
			artist->setArtistId(QString::number(getJsonValue(artistJsonObj, "id").toInt()));
			artist->setArtistName(getJsonValue(artistJsonObj, "name").toString());
			artist->setArtistTitle(artist->getArtistName());
			artist->setArtistTitleHilight(artist->getArtistName());
			music->addArtist(artist);
		}
		musics.append(music);
	}
}
