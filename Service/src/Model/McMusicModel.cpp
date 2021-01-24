#include "Service/Model/impl/McMusicModel.h"

#include <QThread>
#include <QReadWriteLock>
#include <QReadLocker>
#include <QWriteLocker>
#include <QDebug>

#include "Service/Domain/Vo/McMusic.h"
#include "Service/Domain/Vo/McAlbum.h"
#include "Service/Domain/Vo/McArtist.h"
#include "Service/McGlobal.h"

McUpdateMusicEvent::McUpdateMusicEvent(MusicType type, const QList<McMusicPtr> &musics) noexcept
    : QEvent (static_cast<QEvent::Type>(type))
    , m_musics(musics)
{
}

McUpdateMusicEvent::~McUpdateMusicEvent() noexcept {
}

MC_DECL_PRIVATE_DATA(McMusicModel)
QList<McMusicPtr> musics;
QReadWriteLock readWriteLock {QReadWriteLock::Recursive};

void clearMusics() noexcept {
    musics.clear();
}
MC_DECL_PRIVATE_DATA_END

MC_INIT(McMusicModel)
MC_REGISTER_BEAN_FACTORY(McMusicModel);
MC_REGISTER_LIST_CONVERTER(QList<McMusicPtr>);
MC_INIT_END

McMusicModel::McMusicModel() noexcept
{
    MC_NEW_PRIVATE_DATA(McMusicModel);
}

McMusicModel::~McMusicModel() noexcept {
}

int McMusicModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
	return d->musics.length();
}

QVariant McMusicModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    if (row < 0 || row >= d->musics.size()) {
        return QVariant();
    }
    McMusicPtr music = d->musics[row];
    switch (role) {
    case SongNameRole:
        return music->getSongTitle();
    case AlbumNamesRole:
        if (music->getAlbum())
            return music->getAlbum()->getAlbumTitle();
        else
            return "";
    case ArtistNamesRole:
        QString result;
        QList<McArtistPtr> artists = music->getArtists();
        for (int i = 0; i < artists.size(); ++i) {
            McArtistPtr artist = artists.at(i);
            result += artist->getArtistTitle();
            if (i < artists.size() - 1)
                result += '/';
        }
        return result;
    }

    return QVariant();
}

QHash<int, QByteArray> McMusicModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[SongNameRole] = "songName";
	roles[AlbumNamesRole] = "album";
	roles[ArtistNamesRole] = "artist";
	return roles;
}

void McMusicModel::customEvent(QEvent *event) {
    switch (static_cast<int>(event->type())) {
    case McUpdateMusicEvent::SetType:
        doSetMusics(static_cast<McUpdateMusicEvent *>(event)->musics());
        break;
    case McUpdateMusicEvent::AddType:
        doAddMusics(static_cast<McUpdateMusicEvent *>(event)->musics());
        break;
    default:
        break;
    }
}

QList<McMusicPtr> McMusicModel::musics() const noexcept {
    QScopedPointer<QReadLocker> locker;
    if(QThread::currentThread() != thread()) {
        locker.reset(new QReadLocker(&d->readWriteLock));
    }
    return d->musics;
}

QList<McMusicPtr> McMusicModel::takeMusics(const QList<int> &indexs) noexcept {
    if(QThread::currentThread() == thread()) {
        return doTakeMusics(indexs);
    }else{
        QList<McMusicPtr> ms;
        QMetaObject::invokeMethod(this, "doTakeMusics"
                                  , Qt::BlockingQueuedConnection
                                  , Q_RETURN_ARG(QList<McMusicPtr>, ms)
                                  , Q_ARG(QList<int>, indexs));
        return ms;
    }
}

McMusicPtr McMusicModel::music(int index) const noexcept {
    if(index < 0) {
        qCritical() << "the index less than 0 when get music. index:" << index;
        return McMusicPtr();
    }
    auto ms = musics();
    if(index >= ms.length()) {
        qCritical() << "the index more than music length. index:" << index
                    << "the music length:" << ms.length();
        return McMusicPtr();
    }
    return ms.at(index);
}

void McMusicModel::doSetMusics(const QList<McMusicPtr> &musics) noexcept {
    doClear();
    if(musics.isEmpty()) {
        return;
    }
    QScopedPointer<QWriteLocker> locker;
    if(QThread::currentThread() != thread()) {
        locker.reset(new QWriteLocker(&d->readWriteLock));
    }
    beginInsertRows(QModelIndex(), 0, musics.length() - 1);
    d->musics = musics;
    endInsertRows();
}

void McMusicModel::doAddMusics(const QList<McMusicPtr> &musics) noexcept {
    if(musics.isEmpty()) {
        return;
    }
    QScopedPointer<QWriteLocker> locker;
    if(QThread::currentThread() != thread()) {
        locker.reset(new QWriteLocker(&d->readWriteLock));
    }
    beginInsertRows(QModelIndex(), 0, musics.length() - 1);
    for(int i = musics.length() - 1; i >= 0; --i) {
        d->musics.prepend(musics.at(i));
    }
    endInsertRows();
}

void McMusicModel::doClear() noexcept {
    QScopedPointer<QWriteLocker> locker;
    if(QThread::currentThread() != thread()) {
        locker.reset(new QWriteLocker(&d->readWriteLock));
    }
    if(rowCount() <= 0) {
        return;
    }
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    d->clearMusics();
    endRemoveRows();
}

QList<McMusicPtr> McMusicModel::doTakeMusics(const QList<int> &indexs) noexcept {
    QScopedPointer<QWriteLocker> locker;
    if(QThread::currentThread() != thread()) {
        locker.reset(new QWriteLocker(&d->readWriteLock));
    }
    QList<int> copyIndexs = indexs;
    std::sort(copyIndexs.begin(), copyIndexs.end());	// 默认升序排序
    int offset = 0;
    QList<McMusicPtr> ms;
    for(int index : indexs) {
        //! 由于项被take之后index会减一，所以这里需要减去之前被take出的项数量
        auto i = index - offset;
        if(!Mc::isContains(i, d->musics)) {
            qInfo() << "takeMusics. index not in music length. index:" << i
                    << "length:" << d->musics.length();
            continue;
        }
        beginRemoveRows(QModelIndex(), i, i);
        auto m = d->musics.takeAt(i);
        ++offset;	// 当项被成功take之后，项数量加一
        endRemoveRows();
        ms.append(m);
    }
    return ms;
}
