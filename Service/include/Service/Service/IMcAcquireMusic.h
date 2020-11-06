#pragma once

#include <McIoc/McGlobal.h>

MC_FORWARD_DECL_CLASS(McMusic);

class IMcAcquireMusic {
    MC_DEFINE_TYPELIST()
public:
    virtual ~IMcAcquireMusic() noexcept = default;
    
    virtual QList<McMusicPtr> getMusics() const noexcept = 0;
    virtual QList<McMusicPtr> getMusics(const QList<int> &indexs) const noexcept = 0;
    virtual int getIndex(const McMusicPtr &music) noexcept = 0;
};

MC_DECL_METATYPE(IMcAcquireMusic)
