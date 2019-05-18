#ifndef _MC_MUSIC_PO_H_
#define _MC_MUSIC_PO_H_

#include "McGlobal.h"
#include "McSongSheetPo.h"
#include "McAlbumPo.h"
#include "McArtistPo.h"

class McMusicPo {
public:
	long m_songIndex;
	QString m_songTitle;
	QString m_songSrc;
	QString m_songUrl;
	list_McSongSheetPo m_songSheets;
	McAlbumPo_ptr m_album;
	list_McArtistPo m_artists;

	virtual ~McMusicPo() = default;
};

QX_REGISTER_HPP_QX_DAO(McMusicPo, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<McMusicPo> McMusicPo_ptr;
typedef std::vector<McMusicPo_ptr> list_McMusicPo;

#endif // !_MC_MUSIC_PO_H_