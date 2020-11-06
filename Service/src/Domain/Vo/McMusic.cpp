#include "Service/Domain/Vo/McMusic.h"

#include "Service/Domain/Vo/McArtist.h"

MC_INIT(McMusic)
MC_REGISTER_BEAN_FACTORY(McMusic)
MC_REGISTER_LIST_CONVERTER(QList<McArtistPtr>);
MC_INIT_END

McMusic::McMusic(QObject *parent) noexcept
    : QObject(parent)
{
}

McMusic::~McMusic() noexcept {
}
