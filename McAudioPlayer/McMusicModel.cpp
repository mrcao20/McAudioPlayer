#include "McMusicModel.h"

#include <qevent.h>
#include <qcoreapplication.h>
#include <qqmlengine.h>

#include "McGlobal.h"
#include "McMusic.h"
#include "McAlbum.h"
#include "McArtist.h"

MC_STATIC(McMusicModel)
mcRegisterBeanFactory<QList<McMusic*>>();
MC_STATIC_END

struct McMusicModelData {
	QList<McMusic *> musics;
	QList<McMusic*> copyMusics;

	void setMusics(QList<McMusic *> &val) {
		clearMusics();
		//musics.swap(val);
		musics = val;
	}

	McMusic* takeMusic(int index) {
		if(copyMusics == musics)
			musics.takeAt(index);
		return copyMusics.takeAt(index);
	}

	void clearMusics() {
		qDeleteAll(musics);
		musics.clear();
	}

	~McMusicModelData() {
		clearMusics();
	}
};

McMusicModel::McMusicModel(QObject *parent)
	: QAbstractListModel(parent)
	, d(new McMusicModelData)
{
}

McMusicModel::~McMusicModel(){
}

QList<McMusic *> McMusicModel::getMusics() const noexcept {
	return d->copyMusics;
}

int McMusicModel::getIndex(McMusic* music) noexcept {
	if (!music)
		return -1;
	QList<McMusic*> musics = getMusics();
	for (int i = 0; i < musics.size(); ++i) {
		if (music->getId() == musics.at(i)->getId())
			return i;
	}
	return -1;
}

void McMusicModel::clearModel() noexcept {
	d->copyMusics.clear();
	if (rowCount() <= 0)
		return;
	qApp->postEvent(this, new QEvent(static_cast<QEvent::Type>(QEvent::User + 1)));
}

void McMusicModel::addMusics(const QList<McMusic*>& musics) noexcept {
	if (musics.isEmpty())
		return;
	for (auto music : musics) {
		QQmlEngine::setObjectOwnership(music, QQmlEngine::CppOwnership);
		d->copyMusics.prepend(music);
	}
	qApp->postEvent(this, new QEvent(static_cast<QEvent::Type>(QEvent::User + 2)));
}

int McMusicModel::rowCount(const QModelIndex &parent) const {
	return d->musics.size();
}

QVariant McMusicModel::data(const QModelIndex &index, int role) const {
	int row = index.row();
	if (row < 0 || row >= d->musics.size()) {
		return QVariant();
	}
	McMusic *music = d->musics[row];
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
		QList<McArtist *> artists = music->getArtists();
		for (int i = 0; i < artists.size(); ++i) {
			McArtist *artist = artists.at(i);
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

bool McMusicModel::event(QEvent *e) {
	if (e->type() == QEvent::User) {
		d->setMusics(d->copyMusics);
		beginInsertRows(QModelIndex(), 0, d->musics.size() - 1);
		endInsertRows();
		return true;
	}
	else if (e->type() == QEvent::User + 1) {
		beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
		d->clearMusics();
		endRemoveRows();
		return true;
	}
	else if (e->type() == QEvent::User + 2) {
		int index = d->copyMusics.size() - d->musics.size();
		d->musics = d->copyMusics;
		beginInsertRows(QModelIndex(), 0, index - 1);
		endInsertRows();
		return true;
	}
	return QAbstractListModel::event(e);
}

void McMusicModel::setMusics(const QList<McMusic *> &musics) noexcept {
	clearModel();
	if (musics.isEmpty())
		return;
	d->copyMusics = musics;
	for (auto music : d->copyMusics)	// 将所有对象的所有权设置到C++中，防止将对象暴露给QML之后被删除
		QQmlEngine::setObjectOwnership(music, QQmlEngine::CppOwnership);
	qApp->postEvent(this, new QEvent(QEvent::User));
}

McMusic* McMusicModel::getMusic(int index) const noexcept {
	QList<McMusic*> musics = getMusics();
	if (!Mc::isContains(index, musics))
		return nullptr;
	return musics.at(index);
}

McMusic* McMusicModel::takeMusic(int index) noexcept {
	if (!Mc::isContains(index, d->musics))
		return nullptr;
	beginRemoveRows(QModelIndex(), index, index);
	McMusic* music = d->takeMusic(index);
	endRemoveRows();
	return music;
}
