#ifndef _MC_SONG_SHEET_PO_H_
#define _MC_SONG_SHEET_PO_H_

#include "McGlobal.h"

class McMusicPo;

class McSongSheetPo {
	typedef std::shared_ptr<McMusicPo> McMusicPo_ptr;
	typedef qx::QxCollection<long, McMusicPo_ptr> list_McMusicPo;
public:
	long m_songlistIndex;
	QString m_songlistSection;
	QString m_songlistName;
	list_McMusicPo m_musics;

	virtual ~McSongSheetPo() = default;
};

QX_REGISTER_HPP_QX_DAO(McSongSheetPo, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<McSongSheetPo> McSongSheetPo_ptr;
typedef qx::QxCollection<long, McSongSheetPo_ptr> list_McSongSheetPo;

#endif // !_MC_SONG_SHEET_PO_H_