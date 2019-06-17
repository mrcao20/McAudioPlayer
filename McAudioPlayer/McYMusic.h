#ifndef _MC_Y_MUSIC_H_
#define _MC_Y_MUSIC_H_

#include "McAbstractMusic.h"

#include "McBeanGlobal.h"

class McYMusic : public McAbstractMusic {
	Q_OBJECT
	MC_DECL_STATIC(McYMusic)

public:
	Q_INVOKABLE explicit McYMusic(QObject *parent = 0);
	virtual ~McYMusic();

protected:
	QString getUrl(const McMusic* music) noexcept override;
	void getMusics(QList<McMusic*>& musics, const QString& songName, int limit, int offset) noexcept override;

private:
	void getMusics(QList<McMusic*>& musics, const QString& songName, int limit, int offset, const QString& type, bool total) noexcept;
};

Q_DECLARE_METATYPE(McYMusic*)

#endif // !_MC_Y_MUSIC_H_