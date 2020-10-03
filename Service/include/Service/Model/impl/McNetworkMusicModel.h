#pragma once

#include "../IMcNetworkMusicModel.h"
#include "McMusicModel.h"

#include <McBoot/McBootGlobal.h>

MC_FORWARD_DECL_PRIVATE_DATA(McNetworkMusicModel);

class McNetworkMusicModel : public McMusicModel
        , public IMcNetworkMusicModel {
    
    Q_OBJECT
    MC_DECL_INIT(McNetworkMusicModel)
    MC_DEFINE_TYPELIST(MC_DECL_TYPELIST(McMusicModel), MC_DECL_TYPELIST(IMcNetworkMusicModel))
    MC_MODEL
    MC_BEANNAME("networkMusicModel")
public:
    Q_INVOKABLE McNetworkMusicModel() noexcept;
    ~McNetworkMusicModel() noexcept override;
    
    void setMusics(const QList<McMusicPtr> &musics) noexcept override;
    QList<McMusicPtr> getMusics() const noexcept override;
    McMusicPtr getMusic(int index) const noexcept override;
    void addMusic(McMusicConstPtrRef music) noexcept override;
    void addMusic(const QList<McMusicPtr> &musics) noexcept override;
    QList<McMusicPtr> takeMusics(const QList<int> &indexs) noexcept override;
    
private:
    MC_DECL_PRIVATE(McNetworkMusicModel)
};

MC_DECL_METATYPE(McNetworkMusicModel)
