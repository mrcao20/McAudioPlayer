#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McMusic);

class IMcMusicModel {
    MC_DEFINE_TYPELIST()
public:
    virtual ~IMcMusicModel() noexcept = default;
    
    virtual void setMusics(const QList<McMusicPtr> &musics) noexcept = 0;
    virtual QList<McMusicPtr> getMusics() const noexcept = 0;
    virtual McMusicPtr getMusic(int index) const noexcept = 0;
    virtual void addMusic(McMusicConstPtrRef music) noexcept = 0;
    virtual void addMusic(const QList<McMusicPtr> &musics) noexcept = 0;
    virtual QList<McMusicPtr> takeMusics(const QList<int> &indexs) noexcept = 0;
};

MC_DECL_METATYPE(IMcMusicModel)
