#include "McAudioPlayer/Domain/Po/McMusicDetailPo.h"

#include "McAudioPlayer/Domain/Po/McMusicPo.h"

QX_REGISTER_CPP_QX_DAO(McMusicDetailPo)

namespace qx {
	template<> void register_class(QxClass<McMusicDetailPo> &t) {
		t.setName("t_music_detail_info");

		t.id(&McMusicDetailPo::m_songIndex, "song_index");
		t.data(&McMusicDetailPo::m_songSrc, "song_src");
		t.data(&McMusicDetailPo::m_songId, "song_id");
		t.data(&McMusicDetailPo::m_songMid, "song_mid");
		t.data(&McMusicDetailPo::m_songName, "song_name");
		t.data(&McMusicDetailPo::m_songTitleHilight, "song_title_hilight");

		t.relationOneToOne(&McMusicDetailPo::m_music, "McMusicPo_ptr");
	}
}
