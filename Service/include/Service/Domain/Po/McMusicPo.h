#pragma once

#include "../../Utils/McOrmUtils.h"
#include "McAlbumPo.h"
#include "McArtistPo.h"
#include "McMusicDetailPo.h"

class McSonglistPo;

class McMusicPo {
	typedef std::shared_ptr<McSonglistPo> McSonglistPo_ptr;
	typedef qx::QxCollection<long, McSonglistPo_ptr> list_McSonglistPo;
public:
	long m_songIndex;
	QString m_songTitle;
	QString m_songUrl;
	list_McSonglistPo m_songlist;
	McAlbumPo_ptr m_album;
	list_McArtistPo m_artists;
	McMusicDetailPo_ptr m_musicDetail;

	virtual ~McMusicPo() = default;
};

QX_REGISTER_HPP_QX_DAO(McMusicPo, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<McMusicPo> McMusicPo_ptr;
typedef std::vector<McMusicPo_ptr> list_McMusicPo;
