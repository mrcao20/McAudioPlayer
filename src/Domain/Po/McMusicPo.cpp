#include "McAudioPlayer/Domain/Po/McMusicPo.h"

#include "McAudioPlayer/Domain/Po/McSonglistPo.h"

QX_REGISTER_CPP_QX_DAO(McMusicPo)

namespace qx {
	template<> void register_class(QxClass<McMusicPo> &t) {
		t.setName("t_music_info");

		t.id(&McMusicPo::m_songIndex, "song_index");
		t.data(&McMusicPo::m_songTitle, "song_title");
		t.data(&McMusicPo::m_songUrl, "song_url");

		t.relationOneToMany(&McMusicPo::m_songlist, "list_McSonglistPo", "song_index");
		t.relationManyToOne(&McMusicPo::m_album, "album_index");
		t.relationManyToMany(&McMusicPo::m_artists, "list_McArtistPo", "t_artists_info", "song_index", "artists_index");
		t.relationOneToOne(&McMusicPo::m_musicDetail, "McMusicDetailPo_ptr");
	}
}
