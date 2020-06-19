#include "McAudioPlayer/Domain/Vo/McAlbum.h"

MC_INIT(McAlbum)
MC_REGISTER_BEAN_FACTORY(McAlbum);
MC_INIT_END

McAlbum::McAlbum(QObject *parent) noexcept
    : QObject (parent)
{
}
