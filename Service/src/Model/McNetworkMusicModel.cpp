#include "Service/Model/impl/McNetworkMusicModel.h"

#include <QCoreApplication>
#include <QDebug>

MC_DECL_PRIVATE_DATA(McNetworkMusicModel)
MC_DECL_PRIVATE_DATA_END

MC_INIT(McNetworkMusicModel)
MC_REGISTER_BEAN_FACTORY(McNetworkMusicModel)
MC_INIT_END

McNetworkMusicModel::McNetworkMusicModel() noexcept
{
    MC_NEW_PRIVATE_DATA(McNetworkMusicModel);
}

McNetworkMusicModel::~McNetworkMusicModel() noexcept {
}

/*!
 * \brief McNetworkMusicModel::setMusics
 * 
 * 此函数会在次线程调用，需要回到model的生存线程
 * \param musics
 */
void McNetworkMusicModel::setMusics(const QList<McMusicPtr> &musics) noexcept {
    qApp->postEvent(this, new McUpdateMusicEvent(McUpdateMusicEvent::SetType, musics));
}

QList<McMusicPtr> McNetworkMusicModel::getMusics() const noexcept {
    return musics();
}

McMusicPtr McNetworkMusicModel::getMusic(int index) const noexcept {
    return music(index);
}

void McNetworkMusicModel::addMusic(McMusicConstPtrRef music) noexcept {
    QList<McMusicPtr> musics;
    musics.append(music);
    addMusic(musics);
}

void McNetworkMusicModel::addMusic(const QList<McMusicPtr> &musics) noexcept {
    qApp->postEvent(this, new McUpdateMusicEvent(McUpdateMusicEvent::AddType, musics));
}

QList<McMusicPtr> McNetworkMusicModel::takeMusics(const QList<int> &indexs) noexcept {
    return McMusicModel::takeMusics(indexs);
}
