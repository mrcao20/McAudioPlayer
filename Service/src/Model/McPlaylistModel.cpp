#include "Service/Model/impl/McPlaylistModel.h"

#include <QCoreApplication>
#include <QDebug>

MC_DECL_PRIVATE_DATA(McPlaylistModel)
MC_DECL_PRIVATE_DATA_END

MC_INIT(McPlaylistModel)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McPlaylistModel))
MC_INIT_END

McPlaylistModel::McPlaylistModel() noexcept
{
    MC_NEW_PRIVATE_DATA(McPlaylistModel);
}

McPlaylistModel::~McPlaylistModel() noexcept {
}

/*!
 * \brief McPlaylistModel::setMusics
 * 
 * 此函数会在次线程调用，需要回到model的生存线程
 * \param musics
 */
void McPlaylistModel::setMusics(const QList<McMusicPtr> &musics) noexcept {
    qApp->postEvent(this, new McUpdateMusicEvent(McUpdateMusicEvent::SetType, musics));
}

QList<McMusicPtr> McPlaylistModel::getMusics() const noexcept {
    return musics();
}

McMusicPtr McPlaylistModel::getMusic(int index) const noexcept {
    return music(index);
}

void McPlaylistModel::addMusic(McMusicConstPtrRef music) noexcept {
    QList<McMusicPtr> musics;
    musics.append(music);
    addMusic(musics);
}

void McPlaylistModel::addMusic(const QList<McMusicPtr> &musics) noexcept {
    qApp->postEvent(this, new McUpdateMusicEvent(McUpdateMusicEvent::AddType, musics));
}

QList<McMusicPtr> McPlaylistModel::takeMusics(const QList<int> &indexs) noexcept {
    return McMusicModel::takeMusics(indexs);
}
