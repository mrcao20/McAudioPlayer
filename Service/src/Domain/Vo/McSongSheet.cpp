#include "Service/Domain/Vo/McSongSheet.h"

MC_INIT(McSongSheet)
MC_REGISTER_BEAN_FACTORY(McSongSheet);
MC_INIT_END

McSongSheet::McSongSheet(QObject* parent) noexcept
    : QObject(parent)
{
}
