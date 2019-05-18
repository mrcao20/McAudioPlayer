#include "McSongSheetDao.h"

#include <QVariant>
#include <QDebug>

#include "McContainerGlobal.h"
#include "McSongSheet.h"
#include "McSongSheetPo.h"

MC_STATIC(McSongSheetDao)
mcRegisterComponent<McSongSheetDao*, IMcSongSheetDao*>("McSongSheetDao", "songSheetDao");
MC_STATIC_END

McSongSheetDao::McSongSheetDao(QObject *parent)
	: QObject(parent)
{
}

McSongSheetDao::~McSongSheetDao(){
}

QList<McSongSheet *> McSongSheetDao::getSongSheets() noexcept {
	QList<McSongSheet *> songSheets;
	list_McSongSheetPo list_of_McSongSheetPo;
	QSqlError daoError = qx::dao::fetch_all(list_of_McSongSheetPo);
	if (daoError.type() != QSqlError::NoError) {
		qCritical() << daoError.text();
		return songSheets;
	}
	for (const auto &pair : list_of_McSongSheetPo) {
		McSongSheet * songSheet = new McSongSheet();
		songSheet->setId(pair.second->m_songlistIndex);
		songSheet->setTitle(pair.second->m_songlistSection);
		songSheet->setSongSheet(pair.second->m_songlistName);
		songSheets.append(songSheet);
	}
	return songSheets;
}
