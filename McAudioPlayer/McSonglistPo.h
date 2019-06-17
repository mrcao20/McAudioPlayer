#ifndef _MC_SONGLIST_PO_H_
#define _MC_SONGLIST_PO_H_

#include "McGlobal.h"
#include "McSongSheetPo.h"
#include "McMusicPo.h"

class McPlaylistPo;

class McSonglistPo {
	typedef std::shared_ptr<McPlaylistPo> McPlaylistPo_ptr;
public:
	long m_id;
	McSongSheetPo_ptr m_songSheet;
	McMusicPo_ptr m_music;
	McPlaylistPo_ptr m_playlist;

	virtual ~McSonglistPo() = default;
};

QX_REGISTER_HPP_QX_DAO(McSonglistPo, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<McSonglistPo> McSonglistPo_ptr;
typedef std::vector<McSonglistPo_ptr> list_McSonglistPo;

#endif // !_MC_SONGLIST_PO_H_