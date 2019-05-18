#ifndef _MC_ARTIST_PO_H_
#define _MC_ARTIST_PO_H_

#include "McGlobal.h"

class McMusicPo;

class McArtistPo {
	typedef std::shared_ptr<McMusicPo> McMusicPo_ptr;
	typedef qx::QxCollection<long, McMusicPo_ptr> list_McMusicPo;
public:
	long m_artistIndex;
	QString m_artistId;
	QString m_artistMid;
	QString m_artistName;
	QString m_artistTitle;
	QString m_artistTitleHilight;
	list_McMusicPo m_musics;

	virtual ~McArtistPo() = default;
};

QX_REGISTER_HPP_QX_DAO(McArtistPo, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<McArtistPo> McArtistPo_ptr;
typedef std::vector<McArtistPo_ptr> list_McArtistPo;

#endif // !_MC_ARTIST_PO_H_