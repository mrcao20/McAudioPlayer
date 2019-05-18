#include "McAlbum.h"

MC_STATIC(McAlbum)
mcRegisterBeanFactory<McAlbum *>("McAlbum");
MC_STATIC_END

McAlbum::McAlbum(QObject *parent)
	: QObject(parent)
{
}
