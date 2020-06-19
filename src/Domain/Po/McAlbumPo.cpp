#include "McAudioPlayer/Domain/Po/McAlbumPo.h"

#include "McAudioPlayer/Domain/Po/McMusicPo.h"

QX_REGISTER_CPP_QX_DAO(McAlbumPo)

namespace qx {
	template<> void register_class(QxClass<McAlbumPo> &t) {
		t.setName("t_album_detail_info");

		t.id(&McAlbumPo::m_albumIndex, "album_index");
		t.data(&McAlbumPo::m_albumId, "album_id");
		t.data(&McAlbumPo::m_albumMid, "album_mid");
		t.data(&McAlbumPo::m_albumName, "album_name");
		t.data(&McAlbumPo::m_albumTitle, "album_title");
		t.data(&McAlbumPo::m_albumTitleHilight, "album_title_hilight");

		t.relationOneToMany(&McAlbumPo::m_musics, "list_McAlbumPo", "album_index");
	}
}
