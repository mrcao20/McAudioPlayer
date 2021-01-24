#include "Service/Dao/impl/McMusicDao.h"

#include "Service/Domain/Po/McMusicPo.h"
#include "Service/Domain/Vo/McMusic.h"

MC_DECL_PRIVATE_DATA(McMusicDao)
MC_DECL_PRIVATE_DATA_END

MC_INIT(McMusicDao)
MC_REGISTER_BEAN_FACTORY(McMusicDao);
MC_INIT_END

McMusicDao::McMusicDao() noexcept
{
    MC_NEW_PRIVATE_DATA(McMusicDao);
}

McMusicDao::~McMusicDao() noexcept {
}

void McMusicDao::getMusicUrl(McMusicConstPtrRef music) noexcept {
    if (thread() == QThread::currentThread()) {
        getMusicUrl_helper(music);
    } else {
        QMetaObject::invokeMethod(this,
                                  MC_STRINGIFY(getMusicUrl_helper),
                                  Qt::BlockingQueuedConnection,
                                  Q_ARG(McMusicPtr, music));
    }
}

void McMusicDao::getMusicDetail(McMusicConstPtrRef music) noexcept {
    if (thread() == QThread::currentThread()) {
        getMusicDetail_helper(music);
    } else {
        QMetaObject::invokeMethod(this,
                                  MC_STRINGIFY(getMusicDetail_helper),
                                  Qt::BlockingQueuedConnection,
                                  Q_ARG(McMusicPtr, music));
    }
}

void McMusicDao::updateMusicUrl(McMusicConstPtrRef music) noexcept
{
    if (thread() == QThread::currentThread()) {
        updateMusicUrl_helper(music);
    } else {
        QMetaObject::invokeMethod(this,
                                  MC_STRINGIFY(updateMusicUrl_helper),
                                  Qt::BlockingQueuedConnection,
                                  Q_ARG(McMusicPtr, music));
    }
}

void McMusicDao::getMusicUrl_helper(const McMusicPtr &music) noexcept
{
    McMusicPo_ptr musicPo(new McMusicPo());
    musicPo->m_songIndex = music->getId();
    qx::dao::fetch_by_id_with_relation("{song_url}", musicPo);
    music->setSongUrl(musicPo->m_songUrl);
}

void McMusicDao::getMusicDetail_helper(const McMusicPtr &music) noexcept
{
    McMusicDetailPo_ptr musicDetailPo(new McMusicDetailPo());
    musicDetailPo->m_songIndex = music->getId();
    qx::dao::fetch_by_id_with_relation("{song_src, song_id, song_mid}", musicDetailPo);
    music->setSongSrc(musicDetailPo->m_songSrc);
    music->setSongId(musicDetailPo->m_songId);
    music->setSongMid(musicDetailPo->m_songMid);
}

void McMusicDao::updateMusicUrl_helper(const McMusicPtr &music) noexcept
{
    McMusicPo_ptr musicPo(new McMusicPo());
    musicPo->m_songIndex = music->getId();
    musicPo->m_songUrl = music->getSongUrl().toString();
    qx::QxSqlQuery query
        = "UPDATE `t_music_info` SET song_url = :songUrl WHERE song_index = :songIndex";
    query.bind(":songIndex", static_cast<qlonglong>(musicPo->m_songIndex));
    query.bind(":songUrl", musicPo->m_songUrl);
    QSqlError sqlError = qx::dao::execute_query(query, musicPo);
    if (sqlError.type() != QSqlError::NoError) {
        qCritical() << "update t_music_info: " << sqlError.text();
        return;
    }
}
