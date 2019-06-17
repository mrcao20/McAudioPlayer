#ifndef _MC_MUSIC_DETAIL_PO_H_
#define _MC_MUSIC_DETAIL_PO_H_

#include "McGlobal.h"

class McMusicPo;

class McMusicDetailPo {
	typedef std::shared_ptr<McMusicPo> McMusicPo_ptr;
public:
	long m_songIndex;
	QString m_songSrc;
	QString m_songId;
	QString m_songMid;
	QString m_songName;
	QString m_songTitleHilight;

	McMusicPo_ptr m_music;
};

QX_REGISTER_HPP_QX_DAO(McMusicDetailPo, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<McMusicDetailPo> McMusicDetailPo_ptr;
typedef std::vector<McMusicDetailPo_ptr> list_McMusicDetailPo;

#endif // !_MC_MUSIC_DETAIL_PO_H_