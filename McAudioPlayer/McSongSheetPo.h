#ifndef _MC_SONG_SHEET_PO_H_
#define _MC_SONG_SHEET_PO_H_

#include "McGlobal.h"

class McSonglistPo;

class McSongSheetPo {
	typedef std::shared_ptr<McSonglistPo> McSonglistPo_ptr;
	typedef qx::QxCollection<long, McSonglistPo_ptr> list_McSonglistPo;
public:
	long m_songlistIndex;
	QString m_songlistSection;
	QString m_songlistName;
	list_McSonglistPo m_songlist;

	virtual ~McSongSheetPo() = default;
};

QX_REGISTER_HPP_QX_DAO(McSongSheetPo, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<McSongSheetPo> McSongSheetPo_ptr;
typedef qx::QxCollection<long, McSongSheetPo_ptr> list_McSongSheetPo;

#endif // !_MC_SONG_SHEET_PO_H_