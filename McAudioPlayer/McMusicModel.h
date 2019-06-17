#ifndef _MC_MUSIC_MODEL_H_
#define _MC_MUSIC_MODEL_H_

#include <QAbstractListModel>

#include "McBeanGlobal.h"

struct McMusicModelData;

class McMusic;

class McMusicModel : public QAbstractListModel {
	Q_OBJECT
	MC_DECL_STATIC(McMusicModel)

public:
	enum Roles {
		SongNameRole = Qt::UserRole + 1,
		AlbumNamesRole,
		ArtistNamesRole
	};

	explicit McMusicModel(QObject *parent = 0);
	~McMusicModel();

	Q_INVOKABLE QList<McMusic *> getMusics() const noexcept;
	Q_INVOKABLE int getIndex(McMusic* music) noexcept;
	Q_INVOKABLE void clearModel() noexcept;
	Q_INVOKABLE void addMusics(const QList<McMusic*>& musics) noexcept;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	QHash<int, QByteArray> roleNames() const override;

protected:
	bool event(QEvent *e) override;

	void setMusics(const QList<McMusic*>& musics) noexcept;
	McMusic* getMusic(int index) const noexcept;
	McMusic* takeMusic(int index) noexcept;

private:
	QScopedPointer<McMusicModelData> d;
};

Q_DECLARE_METATYPE(McMusicModel*)

#endif // !_MC_MUSIC_MODEL_H_