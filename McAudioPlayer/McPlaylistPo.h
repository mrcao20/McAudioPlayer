#ifndef _MC_PLAYLIST_PO_H_
#define _MC_PLAYLIST_PO_H_

#include "McGlobal.h"
#include "McSonglistPo.h"

class McPlaylistPo {
public:
	long m_id;
	int m_playlistIndex;
	McSonglistPo_ptr m_songlist;

	virtual ~McPlaylistPo() = default;
};

QX_REGISTER_HPP_QX_DAO(McPlaylistPo, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<McPlaylistPo> McPlaylistPo_ptr;
typedef std::vector<McPlaylistPo_ptr> list_McPlaylistPo;

#endif // !_MC_PLAYLIST_PO_H_