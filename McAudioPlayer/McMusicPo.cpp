#include "McMusicPo.h"

QX_REGISTER_CPP_QX_DAO(McMusicPo)

namespace qx {
	template<> void register_class(QxClass<McMusicPo> &t) {
		t.setName("t_music_info");

		t.id(&McMusicPo::m_songIndex, "song_index");
		t.data(&McMusicPo::m_songTitle, "song_title");
		t.data(&McMusicPo::m_songSrc, "song_src");
		t.data(&McMusicPo::m_songUrl, "song_url");

		t.relationManyToMany(&McMusicPo::m_songSheets, "list_McSongSheetPo", "t_songlist_info", "song_index", "songlist_index");
		t.relationManyToOne(&McMusicPo::m_album, "album_index");
		t.relationManyToMany(&McMusicPo::m_artists, "list_McArtistPo", "t_artists_info", "song_index", "artists_index");
	}
}