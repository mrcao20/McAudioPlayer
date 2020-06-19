#include "McAudioPlayer/Domain/Po/McSongSheetPo.h"

#include "McAudioPlayer/Domain/Po/McSonglistPo.h"

QX_REGISTER_CPP_QX_DAO(McSongSheetPo)

namespace qx {
	template<> void register_class(QxClass<McSongSheetPo> &t) {
		t.setName("t_songlist_detail_info");

		t.id(&McSongSheetPo::m_songlistIndex, "songlist_index");
		t.data(&McSongSheetPo::m_songlistSection, "songlist_section");
		t.data(&McSongSheetPo::m_songlistName, "songlist_name");

		t.relationOneToMany(&McSongSheetPo::m_songlist, "list_McSonglistPo", "songlist_index");
	}
}
