#include "McAudioPlayer/Domain/Vo/McArtist.h"

MC_INIT(McArtist)
MC_REGISTER_BEAN_FACTORY(McArtist);
MC_INIT_END

McArtist::McArtist(QObject *parent) noexcept
    : QObject (parent)
{
}
