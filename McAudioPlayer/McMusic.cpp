#include "McMusic.h"

#include "McArtist.h"
#include "McAlbum.h"
#include "McMacroGlobal.h"

MC_STATIC(McMusic)
mcRegisterBeanFactory<McMusic *>("McMusic");
mcRegisterListObjectConverter<QList<McArtist *>>();
MC_STATIC_END

McMusic::McMusic(QObject *parent)
	: QObject(parent)
{
}

McMusic::~McMusic() {
	MC_SAFE_DELETE(m_album);
	qDeleteAll(m_artists);
}

McMusic* McMusic::copy() const noexcept {
	McMusic* other = new McMusic();
	other->m_id = m_id;
	other->m_songTitle = m_songTitle;
	other->m_songUrl = m_songUrl;
	if(m_album)
		other->m_album = m_album->copy();
	QList<McArtist*> artists;
	for (auto artist : m_artists) {
		artists.append(artist->copy());
	}
	other->m_artists = artists;
	other->m_songSrc = m_songSrc;
	other->m_songId = m_songId;
	other->m_songMid = m_songMid;
	other->m_songName = m_songName;
	other->m_songTitleHilight = m_songTitleHilight;
	return other;
}