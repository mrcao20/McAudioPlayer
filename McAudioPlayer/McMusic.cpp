#include "McMusic.h"

#include "McArtist.h"
#include "McMacroGlobal.h"

MC_STATIC(McMusic)
mcRegisterBeanFactory<McMusic *>("McMusic");
mcRegisterListObjectConverter<QList<McArtist *>>();
MC_STATIC_END

McMusic::McMusic(QObject *parent)
	: QObject(parent)
{
}

McMusic::~McMusic() {
	MC_SAFE_DELETE(m_album);
	qDeleteAll(m_artists);
}