#ifndef _MC_SONG_SHEET_MODEL_H_
#define _MC_SONG_SHEET_MODEL_H_

#include <qabstractitemmodel.h>

#include "McGlobal.h"
#include "McBeanGlobal.h"

struct McSongSheetModelData;

class IMcSongSheetService;
class McSongSheet;
class McMusic;

class McSongSheetModel : public QAbstractListModel {
	Q_OBJECT
	Q_PROPERTY(IMcSongSheetService *songSheetService READ getSongSheetService WRITE setSongSheetService USER true)
	Q_CLASSINFO("Component", MC_MODEL_STR)
	MC_DECL_STATIC(McSongSheetModel)

public:
	enum Roles {
		TitleRole = Qt::UserRole + 1,
		SongSheetRole
	};

	Q_INVOKABLE explicit McSongSheetModel(QObject *parent = 0);
	~McSongSheetModel();

	IMcSongSheetService *getSongSheetService() const noexcept;
	void setSongSheetService(IMcSongSheetService *val) noexcept;

	Q_INVOKABLE void loadSongSheets(const QString &section, const QStringList &list) noexcept;
	Q_INVOKABLE QList<McSongSheet*> getSongSheets() noexcept;
	Q_INVOKABLE McSongSheet *get(int row) noexcept;
	Q_INVOKABLE void deleteSongSheet(int index) noexcept;
	Q_INVOKABLE bool rename(int index, const QString& newName) noexcept;
	Q_INVOKABLE int createNewSongSheet(const QString& title, const QString& newName) noexcept;
	Q_INVOKABLE QList<McMusic*> addLocalMusics(int index, const QList<QUrl>& filePaths) noexcept;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	QHash<int, QByteArray> roleNames() const override;

private:
	void sort(QList<McSongSheet *> &songSheets, const QString &section, const QStringList &list) noexcept;

private:
	QScopedPointer<McSongSheetModelData> d;
};

Q_DECLARE_METATYPE(McSongSheetModel*)

#endif // !_MC_SONG_SHEET_MODEL_H_