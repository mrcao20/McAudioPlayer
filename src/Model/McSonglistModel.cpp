#include "McAudioPlayer/Model/impl/McSonglistModel.h"

#include <QCoreApplication>
#include <QDebug>

MC_DECL_PRIVATE_DATA(McSonglistModel)
MC_DECL_PRIVATE_DATA_END

MC_INIT(McSonglistModel)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McSonglistModel))
MC_INIT_END

McSonglistModel::McSonglistModel() noexcept
{
    MC_NEW_PRIVATE_DATA(McSonglistModel);
}

McSonglistModel::~McSonglistModel() noexcept {
}

/*!
 * \brief McSonglistModel::setMusics
 * 
 * 此函数会在次线程调用，需要回到model的生存线程
 * \param musics
 */
void McSonglistModel::setMusics(const QList<McMusicPtr> &musics) noexcept {
    qApp->postEvent(this, new McUpdateMusicEvent(McUpdateMusicEvent::SetType, musics));
}

QList<McMusicPtr> McSonglistModel::getMusics() const noexcept {
    return musics();
}

McMusicPtr McSonglistModel::getMusic(int index) const noexcept {
    return music(index);
}

void McSonglistModel::addMusic(McMusicConstPtrRef music) noexcept {
    QList<McMusicPtr> musics;
    musics.append(music);
    addMusic(musics);
}

void McSonglistModel::addMusic(const QList<McMusicPtr> &musics) noexcept {
    qApp->postEvent(this, new McUpdateMusicEvent(McUpdateMusicEvent::AddType, musics));
}

QList<McMusicPtr> McSonglistModel::takeMusics(const QList<int> &indexs) noexcept {
    return McMusicModel::takeMusics(indexs);
}
