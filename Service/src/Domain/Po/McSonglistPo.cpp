#include "Service/Domain/Po/McSonglistPo.h"

#include "Service/Domain/Po/McPlaylistPo.h"

QX_REGISTER_CPP_QX_DAO(McSonglistPo)

namespace qx {
	template<> void register_class(QxClass<McSonglistPo> &t) {
		t.setName("t_songlist_info");

		t.id(&McSonglistPo::m_id, "id");

		t.relationManyToOne(&McSonglistPo::m_songSheet, "songlist_index");
		t.relationManyToOne(&McSonglistPo::m_music, "song_index");
		t.relationOneToOne(&McSonglistPo::m_playlist, "McPlaylistPo_ptr");
	}
}
