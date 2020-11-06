#include "Service/Domain/Po/McPlaylistPo.h"

QX_REGISTER_CPP_QX_DAO(McPlaylistPo)

namespace qx {
	template<> void register_class(QxClass<McPlaylistPo> &t) {
		t.setName("t_playlist_info");

		t.id(&McPlaylistPo::m_id, "id");
		
		t.data(&McPlaylistPo::m_playlistIndex, "playlist_index");

		t.relationOneToOne(&McPlaylistPo::m_songlist, "McSonglistPo_ptr");
	}
}
