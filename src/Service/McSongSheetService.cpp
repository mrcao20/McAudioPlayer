#include "McAudioPlayer/Service/impl/McSongSheetService.h"

#include <QAbstractItemModel>
#include <QDebug>

#include "McAudioPlayer/McGlobal.h"
#include "McAudioPlayer/Model/IMcSongSheetModel.h"
#include "McAudioPlayer/Dao/IMcSongSheetDao.h"
#include "McAudioPlayer/Domain/Vo/McSongSheet.h"

MC_DECL_PRIVATE_DATA(McSongSheetService)
IMcSongSheetModelPtr model;
IMcSongSheetDaoPtr songSheetDao;
MC_DECL_PRIVATE_DATA_END

MC_INIT(McSongSheetService)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McSongSheetService));
MC_INIT_END

McSongSheetService::McSongSheetService() noexcept
{
    MC_NEW_PRIVATE_DATA(McSongSheetService);
}

McSongSheetService::~McSongSheetService() noexcept {
}

IMcSongSheetModelPtr McSongSheetService::model() const noexcept {
    return d->model;
}

void McSongSheetService::setModel(IMcSongSheetModelConstPtrRef val) noexcept {
    d->model = val;
}

QAbstractItemModel *McSongSheetService::getModel() const noexcept {
    return d->model.dynamicCast<QAbstractItemModel>().data();
}

IMcSongSheetDaoPtr McSongSheetService::songSheetDao() const noexcept {
    return d->songSheetDao;
}

void McSongSheetService::setSongSheetDao(IMcSongSheetDaoConstPtrRef val) noexcept {
    d->songSheetDao = val;
}

QList<McSongSheetPtr> McSongSheetService::loadSongSheets(
        const QString &section, const QStringList &list) noexcept {
    
    qInfo() << "loadSongSheets"
             << "section:" << section
             << "list:" << list;
    QList<McSongSheetPtr> songSheets = d->songSheetDao->getSongSheets();
    if (songSheets.isEmpty())
        return songSheets;
    sort(songSheets, section, list);
    d->model->setSongSheets(songSheets);
    return songSheets;
}

int McSongSheetService::getSongSheetId(int index) const noexcept {
    auto ss = d->model->getSongSheets();
    if(!Mc::isContains(index, ss)) {
        qCritical() << "want to get a not exist index:" << index
                    << "song sheet size:" << ss.size();
        return -1;
    }
    return ss.at(index)->getId();
}

bool McSongSheetService::rename(int index, const QString &newText) noexcept {
    auto ss = d->model->getSongSheets();
    if(!Mc::isContains(index, ss)) {
        return false;
    }
    if(newText.contains("'")) {
        qCritical() << "song sheet name cannot contains '";
        return false;
    }
    if(isContainsName(newText, ss)) {
        qInfo() << QString("repeated the name of '%1'").arg(newText);
        return false;
    }
    auto s = ss.at(index);
    s->setSongSheet(newText);
    d->songSheetDao->renameSongSheet(s);
    d->model->updateSongSheet(index, s);
    return true;
}

void McSongSheetService::deleteSongSheet(int index) noexcept {
    auto ss = d->model->getSongSheets();
    if(!Mc::isContains(index, ss)) {
        return;
    }
    d->model->deleteSongSheet(index);
    d->songSheetDao->deleteSongSheet(ss.at(index));
}

int McSongSheetService::createSongSheet(const QString &title, const QString &newName) noexcept {
    auto ss = d->model->getSongSheets();
    McSongSheetPtr s = McSongSheetPtr::create();
    s->setId(getMaxId(ss) + 1);
    s->setTitle(title);
    QString name = newName;
    int i = 1;
    while (isContainsName(name, ss))
        name += QString::number(i++);
    s->setSongSheet(name);
    if(!d->songSheetDao->insert(s)) {
        return -1;
    }
    int newIndex = ss.length();
    d->model->addSongSheet(s);
    return newIndex;
}

void McSongSheetService::sort(QList<McSongSheetPtr> &songSheets
                              , const QString &section, const QStringList &list) noexcept {
    
    QList<McSongSheetPtr> temp;
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

bool McSongSheetService::isContainsName(const QString &name, const QList<McSongSheetPtr> &songSheets) const noexcept {
    for (auto ss : songSheets)
        if (ss->getSongSheet() == name)
            return true;
    return false;
}

int McSongSheetService::getMaxId(const QList<McSongSheetPtr> &songSheets) const noexcept {
    int id = 0;	// 默认为0，表示没有歌单
    for (auto songSheet : songSheets)
        if (songSheet->getId() > id)
            id = songSheet->getId();
    return id;
}
