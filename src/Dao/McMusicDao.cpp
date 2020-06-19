#include "McAudioPlayer/Dao/impl/McMusicDao.h"

#include "McAudioPlayer/Domain/Po/McMusicPo.h"
#include "McAudioPlayer/Domain/Vo/McMusic.h"

MC_DECL_PRIVATE_DATA(McMusicDao)
MC_DECL_PRIVATE_DATA_END

MC_INIT(McMusicDao)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McMusicDao));
MC_INIT_END

McMusicDao::McMusicDao() noexcept
{
    MC_NEW_PRIVATE_DATA(McMusicDao);
}

McMusicDao::~McMusicDao() noexcept {
}

void McMusicDao::getMusicUrl(McMusicConstPtrRef music) noexcept {
    McMusicPo_ptr musicPo(new McMusicPo());
    musicPo->m_songIndex = music->getId();
    qx::dao::fetch_by_id_with_relation("{song_url}", musicPo);
    music->setSongUrl(musicPo->m_songUrl);
}

void McMusicDao::getMusicDetail(McMusicConstPtrRef music) noexcept {
    McMusicDetailPo_ptr musicDetailPo(new McMusicDetailPo());
    musicDetailPo->m_songIndex = music->getId();
    qx::dao::fetch_by_id_with_relation("{song_src, song_id, song_mid}", musicDetailPo);
    music->setSongSrc(musicDetailPo->m_songSrc);
    music->setSongId(musicDetailPo->m_songId);
    music->setSongMid(musicDetailPo->m_songMid);
}
