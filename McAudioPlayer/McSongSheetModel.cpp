#include "McSongSheetModel.h"

#include <qqmlengine.h>

#include "McContainerGlobal.h"
#include "IMcSongSheetService.h"
#include "McSongSheet.h"
#include "McMusic.h"

MC_STATIC(McSongSheetModel)
mcRegisterComponent<McSongSheetModel*>("McSongSheetModel", "songSheetModel");
mcRegisterBeanFactory<QList<McSongSheet*>>();
MC_STATIC_END

struct McSongSheetModelData {
	IMcSongSheetService *songSheetService{ nullptr };
	QList<McSongSheet *> songSheets;

	void clearSongSheet() {
		qDeleteAll(songSheets);
		songSheets.clear();
	}
};

McSongSheetModel::McSongSheetModel(QObject *parent)
	: QAbstractListModel(parent)
	, d(new McSongSheetModelData)
{
}

McSongSheetModel::~McSongSheetModel(){
}

IMcSongSheetService *McSongSheetModel::getSongSheetService() const noexcept {
	return d->songSheetService;
}

void McSongSheetModel::setSongSheetService(IMcSongSheetService *val) noexcept {
	d->songSheetService = val;
}

void McSongSheetModel::loadSongSheets(const QString &section, const QStringList &list) noexcept {
	QList<McSongSheet *> songSheets = d->songSheetService->getSongSheets();
	if (songSheets.isEmpty())
		return;
	sort(songSheets, section, list);
	beginInsertRows(QModelIndex(), 0, songSheets.size() - 1);
	d->songSheets = songSheets;
	endInsertRows();
}

QList<McSongSheet*> McSongSheetModel::getSongSheets() noexcept {
	return d->songSheets;
}

McSongSheet* McSongSheetModel::get(int row) noexcept {
	if (!Mc::isContains(row, d->songSheets))
		return nullptr;
	McSongSheet *songSheet = d->songSheets.at(row);
	if (!songSheet->parent())
		songSheet->setParent(this);
	return songSheet;
}

void McSongSheetModel::deleteSongSheet(int index) noexcept {
	if (!Mc::isContains(index, d->songSheets))
		return;
	beginRemoveRows(QModelIndex(), index, index);
	McSongSheet* songSheet = d->songSheets.takeAt(index);
	endRemoveRows();
	d->songSheetService->deleteSongSheet(songSheet);
	songSheet->deleteLater();
}

bool McSongSheetModel::rename(int index, const QString& newName) noexcept {
	if (!Mc::isContains(index, d->songSheets))
		return false;
	McSongSheet* songSheet = d->songSheets.at(index);
	if (!d->songSheetService->renameSongSheet(songSheet, newName, d->songSheets))
		return false;
	songSheet->setSongSheet(newName);
	return true;
}

int McSongSheetModel::createNewSongSheet(const QString& title, const QString& newName) noexcept {
	McSongSheet* songSheet = d->songSheetService->createSongSheet(title, newName, d->songSheets);
	if (!songSheet)
		return -1;
	int newIndex = d->songSheets.size();
	beginInsertRows(QModelIndex(), newIndex, newIndex);
	d->songSheets.append(songSheet);
	endInsertRows();
	return newIndex;
}

QList<McMusic*> McSongSheetModel::addLocalMusics(int index, const QList<QUrl>& filePaths) noexcept {
	if (!Mc::isContains(index, d->songSheets))
		return QList<McMusic*>();
	int songSheetId = d->songSheets.at(index)->getId();
	QList<McMusic*> musics = d->songSheetService->addLocalMusics(songSheetId, filePaths);
	// 此处不设置McMusic的所有权，即它会在没有任何后续操作时自动在QML中析构
	/*for (auto music : musics)
		QQmlEngine::setObjectOwnership(music, QQmlEngine::CppOwnership);*/
	return musics;
}

int McSongSheetModel::rowCount(const QModelIndex &parent) const {
	return d->songSheets.size();
}

QVariant McSongSheetModel::data(const QModelIndex &index, int role) const {
	int row = index.row();
	if (row < 0 || row >= d->songSheets.size()) {
		return QVariant();
	}
	McSongSheet *songSheet = d->songSheets[row];
	// 由于data函数会遍历所有对象，所以直接在此处将所有对象的父类设置为this，防止将对象暴露给QML之后被删除
	songSheet->setParent(const_cast<McSongSheetModel *>(this));
	switch (role) {
	case TitleRole:
		return songSheet->getTitle();
	case SongSheetRole:
		return songSheet->getSongSheet();
	}

	return QVariant();
}

QHash<int, QByteArray> McSongSheetModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[TitleRole] = "title";
	roles[SongSheetRole] = "songSheet";
	return roles;
}

void McSongSheetModel::sort(QList<McSongSheet *> &songSheets, const QString &section, const QStringList &list) noexcept {
	QList<McSongSheet *> temp;
	for (const QString &str : list) {
		for (int i = 0; i < songSheets.size(); ++i) {
			auto songSheet = songSheets.at(i);
			if(songSheet->property(section.toLocal8Bit()) != str)
				continue;
			temp.append(songSheet);
			songSheets.removeAt(i--);
		}
	}
	songSheets.swap(temp);
}
