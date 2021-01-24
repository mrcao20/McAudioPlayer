#include "Service/Controller/McSongSheetController.h"

#include <QDebug>

#include <McBoot/Utils/McJsonUtils.h>

#include "Service/Service/IMcSongSheetService.h"
#include "Service/Service/IMcSonglistService.h"
#include "Service/Domain/Vo/McSongSheet.h"

MC_DECL_PRIVATE_DATA(McSongSheetController)
IMcSongSheetServicePtr songSheetService;
IMcSonglistServicePtr songlistService;
MC_DECL_PRIVATE_DATA_END

MC_INIT(McSongSheetController)
MC_REGISTER_BEAN_FACTORY(McSongSheetController);
MC_REGISTER_LIST_CONVERTER(QList<QUrl>);
MC_INIT_END

McSongSheetController::McSongSheetController() noexcept
{
    MC_NEW_PRIVATE_DATA(McSongSheetController);
}

McSongSheetController::~McSongSheetController() noexcept {
}

IMcSongSheetServicePtr McSongSheetController::songSheetService() const noexcept {
    return d->songSheetService;
}

void McSongSheetController::setSongSheetService(IMcSongSheetServiceConstPtrRef val) noexcept {
    d->songSheetService = val;
}

IMcSonglistServicePtr McSongSheetController::songlistService() const noexcept {
    return d->songlistService;
}

void McSongSheetController::setSonglistService(IMcSonglistServiceConstPtrRef val) noexcept {
    d->songlistService = val;
}

QAbstractItemModel *McSongSheetController::getModel() const noexcept {
    return d->songSheetService->getModel();
}

QJsonArray McSongSheetController::loadSongSheets(
        const QString &section
        , const QStringList &list) noexcept {
    
    qInfo() << "loadSongSheets."
            << "section:" << section
            << "list:" << list;
    QList<McSongSheetPtr> songSheets = d->songSheetService->loadSongSheets(section, list);
    return McJsonUtils::toJson(songSheets);
}

void McSongSheetController::addLocalMusics(int index, const QList<QUrl> &filePaths) noexcept {
    qInfo() << "addLocalMusics:" << index << filePaths;
    auto id = d->songSheetService->getSongSheetId(index);
    d->songlistService->addNewLocalMusics(id, filePaths);
}

bool McSongSheetController::rename(int index, const QString &newText) noexcept {
    qInfo() << "rename song sheet. index:" << index
            <<"new name:" <<newText;
    return d->songSheetService->rename(index, newText);
}

void McSongSheetController::deleteSongSheet(int index) noexcept {
    qInfo() <<"delete song sheet for index:" << index;
    d->songSheetService->deleteSongSheet(index);
}

int McSongSheetController::createNewSongSheet(const QString &title, const QString &newName) noexcept {
    qInfo() << "create new song sheet. title:" << title
            << "newName:" << newName;
    return d->songSheetService->createSongSheet(title, newName);
}
