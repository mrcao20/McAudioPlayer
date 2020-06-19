#pragma once

#include "../../Utils/McOrmUtils.h"

class McMusicPo;

class McAlbumPo {
	typedef std::shared_ptr<McMusicPo> McMusicPo_ptr;
	typedef qx::QxCollection<long, McMusicPo_ptr> list_McMusicPo;
public:
	long m_albumIndex;
	QString m_albumId;
	QString m_albumMid;
	QString m_albumName;
	QString m_albumTitle;
	QString m_albumTitleHilight;
	list_McMusicPo m_musics;

	virtual ~McAlbumPo() = default;
};

QX_REGISTER_HPP_QX_DAO(McAlbumPo, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<McAlbumPo> McAlbumPo_ptr;
typedef qx::QxCollection<long, McAlbumPo_ptr> list_McAlbumPo;
