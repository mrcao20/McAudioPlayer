#include "McAudioPlayer/Domain/Po/McArtistPo.h"

#include "McAudioPlayer/Domain/Po/McMusicPo.h"

QX_REGISTER_CPP_QX_DAO(McArtistPo)

namespace qx {
	template<> void register_class(QxClass<McArtistPo> &t) {
		t.setName("t_artists_detail_info");

		t.id(&McArtistPo::m_artistIndex, "artists_index");
		t.data(&McArtistPo::m_artistId, "artists_id");
		t.data(&McArtistPo::m_artistMid, "artists_mid");
		t.data(&McArtistPo::m_artistName, "artists_name");
		t.data(&McArtistPo::m_artistTitle, "artists_title");
		t.data(&McArtistPo::m_artistTitleHilight, "artists_title_hilight");

		t.relationManyToMany(&McArtistPo::m_musics, "list_McMusicPo", "t_artists_info", "artists_index", "song_index");
	}
}
