#include "McArtist.h"

MC_STATIC(McArtist)
mcRegisterBeanFactory<McArtist *>("McArtist");
MC_STATIC_END

McArtist::McArtist(QObject *parent)
	: QObject(parent)
{
}
