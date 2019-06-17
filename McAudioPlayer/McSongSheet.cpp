#include "McSongSheet.h"

MC_STATIC(McSongSheet)
mcRegisterBeanFactory<McSongSheet*>("McSongSheet");
MC_STATIC_END

McSongSheet::McSongSheet(QObject* parent)
	: QObject(parent)
{
}
