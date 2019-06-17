#ifndef _MC_GLOBAL_H_
#define _MC_GLOBAL_H_

#include <QtCore/qglobal.h>
#include <QxOrm.h>

#define MC_CONTROLLER_STR "Controller"
#define MC_MODEL_STR "Model"

#define MC_SONG_SRC_LOCAL "local"
#define MC_SONG_SRC_YMUSIC "ymusic"
#define MC_SONG_SRC_QQMUSIC "qqmusic"

#ifdef _BUILDING_QX_DAO
#define QX_REGISTER_HPP_QX_DAO QX_REGISTER_HPP_EXPORT_DLL
#define QX_REGISTER_CPP_QX_DAO QX_REGISTER_CPP_EXPORT_DLL
#else // _BUILDING_QX_DAO
#define QX_REGISTER_HPP_QX_DAO QX_REGISTER_HPP_IMPORT_DLL
#define QX_REGISTER_CPP_QX_DAO QX_REGISTER_CPP_IMPORT_DLL
#endif // _BUILDING_QX_DAO

namespace Mc {
template<typename Container>
bool isContains(int index, Container container) {
	if (index >= 0 && index < container.size())
		return true;
	return false;
}
}

#endif // !_MC_GLOBAL_H_

