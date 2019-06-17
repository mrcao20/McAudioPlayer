#ifndef _MC_QQ_MUSIC_H_
#define _MC_QQ_MUSIC_H_

#include "McAbstractMusic.h"

#include "McBeanGlobal.h"

class McQQMusic : public McAbstractMusic {
	Q_OBJECT
	MC_DECL_STATIC(McQQMusic)

public:
	Q_INVOKABLE explicit McQQMusic(QObject *parent = 0);
	virtual ~McQQMusic();

	QString getUrl(const McMusic* music) noexcept override;
	void getMusics(QList<McMusic*>& musics, const QString& songName, int limit, int offset) noexcept override;
};

Q_DECLARE_METATYPE(McQQMusic*)

#endif // !_MC_QQ_MUSIC_H_