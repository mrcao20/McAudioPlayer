#include "Service/Model/impl/McSongSheetModel.h"

#include <QCoreApplication>
#include <QEvent>
#include <QDebug>

#include "Service/Domain/Vo/McSongSheet.h"
#include "Service/McGlobal.h"

class McUpdateSongSheetEvent : public QEvent {
public:
    McUpdateSongSheetEvent(QEvent::Type type
                           , const QList<McSongSheetPtr> &songSheets) noexcept;
    ~McUpdateSongSheetEvent() noexcept;
    
    QList<McSongSheetPtr> songSheets() const noexcept {
        return m_songSheets;
    }
    void setSongSheets(const QList<McSongSheetPtr> &val) noexcept {
        m_songSheets = val;
    }
    
    MC_PADDING_CLANG(4)
private:
    QList<McSongSheetPtr> m_songSheets;
};

McUpdateSongSheetEvent::McUpdateSongSheetEvent(
        QEvent::Type type, const QList<McSongSheetPtr> &songSheets) noexcept
    : QEvent(type)
    , m_songSheets(songSheets)
{
}

McUpdateSongSheetEvent::~McUpdateSongSheetEvent() noexcept {
}

MC_DECL_PRIVATE_DATA(McSongSheetModel)
QList<McSongSheetPtr> songSheets;

void clearSongSheets() {
    songSheets.clear();
}
MC_DECL_PRIVATE_DATA_END

MC_INIT(McSongSheetModel)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McSongSheetModel));
MC_INIT_END

McSongSheetModel::McSongSheetModel() noexcept
{
    MC_NEW_PRIVATE_DATA(McSongSheetModel);
}

McSongSheetModel::~McSongSheetModel() noexcept {
}

int McSongSheetModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
	return d->songSheets.length();
}

QVariant McSongSheetModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    if (row < 0 || row >= d->songSheets.size()) {
        qCritical() << "McSongSheetModel data row less than 0 or more than size";
        return QVariant();
    }
    auto songSheet = d->songSheets[row];
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

QList<McSongSheetPtr> McSongSheetModel::getSongSheets() const noexcept {
    return d->songSheets;
}

void McSongSheetModel::setSongSheets(const QList<McSongSheetPtr> &songSheets) noexcept {
    qInfo() << "setSongSheets. song sheet length:" << songSheets.length();
    qApp->postEvent(this, new McUpdateSongSheetEvent(QEvent::Type::User, songSheets));
}

void McSongSheetModel::updateSongSheet(int index, McSongSheetConstPtrRef songSheet) noexcept {
    if(!Mc::isContains(index, d->songSheets)) {
        return;
    }
    qInfo() << "update song sheet for index:" << index
            << "old name:" << d->songSheets.at(index)
            << "new name:" << songSheet->getSongSheet();
    qApp->postEvent(this, new McCustomEvent(QEvent::Type::User + 1, QVariantList() << index << QVariant::fromValue(songSheet)));
}

void McSongSheetModel::deleteSongSheet(int index) noexcept {
    if(!Mc::isContains(index, d->songSheets)) {
        return;
    }
    qInfo() << "delete song sheet for index:" << index;
    qApp->postEvent(this, new McCustomEvent(QEvent::Type::User + 2, index));
}

void McSongSheetModel::addSongSheet(McSongSheetConstPtrRef songSheet) noexcept {
    if(songSheet.isNull()) {
        return;
    }
    qInfo() << "add song sheet for title:" << songSheet->getTitle();
    qApp->postEvent(this, new McCustomEvent(QEvent::Type::User + 3, QVariant::fromValue(songSheet)));
}

void McSongSheetModel::customEvent(QEvent *event) {
    qInfo() << "recv custom event. type:" << event->type();
    switch(static_cast<int>(event->type())) {
    case QEvent::Type::User:
        doReload(static_cast<McUpdateSongSheetEvent *>(event)->songSheets());
        break;
    case QEvent::Type::User + 1: {
        auto e = static_cast<McCustomEvent *>(event);
        auto list = e->data().value<QVariantList>();
        Q_ASSERT(list.length() == 2);
        auto index = list.first().value<int>();
        auto s = list.back().value<McSongSheetPtr>();
        doUpdate(index, s);
        break;
    }
    case QEvent::Type::User + 2:
        doDelete(static_cast<McCustomEvent *>(event)->data().value<int>());
        break;
    case QEvent::Type::User + 3:
        doAdd(static_cast<McCustomEvent *>(event)->data().value<McSongSheetPtr>());
        break;
    default:
        break;
    }
}

void McSongSheetModel::doReload(const QList<McSongSheetPtr> &songSheets) noexcept {
    beginResetModel();
    d->clearSongSheets();
    endResetModel();
    
    if(songSheets.isEmpty()) {
        return;
    }
    beginInsertRows(QModelIndex(), 0, songSheets.length() - 1);
    d->songSheets = songSheets;
    endInsertRows();
}

void McSongSheetModel::doUpdate(int index, McSongSheetConstPtrRef &songSheet) noexcept {
    if(songSheet.isNull()) {
        qCritical() << "want to update song sheet. but incoming param is null";
        return;
    }
    d->songSheets.replace(index, songSheet);
    emit dataChanged(this->index(index), this->index(index), QVector<int>() << McSongSheetModel::Roles::SongSheetRole);
}

void McSongSheetModel::doDelete(int index) noexcept {
    beginRemoveRows(QModelIndex(), index, index);
    d->songSheets.removeAt(index);
    endRemoveRows();
}

void McSongSheetModel::doAdd(McSongSheetConstPtrRef &songSheet) noexcept {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    d->songSheets.append(songSheet);
    endInsertRows();
}
