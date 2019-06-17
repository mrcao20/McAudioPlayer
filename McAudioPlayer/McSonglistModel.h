#ifndef _MC_SONGLIST_MODEL_H_
#define _MC_SONGLIST_MODEL_H_

#include "McMusicModel.h"

#include "McGlobal.h"
#include "McBeanGlobal.h"

struct McSonglistModelData;

class IMcSonglistService;

class McSonglistModel : public McMusicModel {
	Q_OBJECT
	Q_PROPERTY(IMcSonglistService *songlistService READ getSonglistService WRITE setSonglistService USER true)
	Q_CLASSINFO("Component", MC_MODEL_STR)
	MC_DECL_STATIC(McSonglistModel)

public:
	Q_INVOKABLE explicit McSonglistModel(QObject *parent = 0);
	~McSonglistModel();

	IMcSonglistService *getSonglistService() const noexcept;
	void setSonglistService(IMcSonglistService *val) noexcept;

	Q_INVOKABLE void updateMusic(int songSheetId) noexcept;
	Q_INVOKABLE void addToSongSheet(int songSheetId, const QList<int>& indexs) noexcept;
	Q_INVOKABLE void removeFromSongSheet(int songSheetId, const QList<int>& indexs) noexcept;

private:
	QScopedPointer<McSonglistModelData> d;
};

Q_DECLARE_METATYPE(McSonglistModel*)

#endif // !_MC_SONGLIST_MODEL_H_