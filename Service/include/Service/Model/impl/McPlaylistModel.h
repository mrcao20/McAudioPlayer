#pragma once

#include "../IMcPlaylistModel.h"
#include "McMusicModel.h"

#include <McBoot/McBootGlobal.h>

MC_FORWARD_DECL_PRIVATE_DATA(McPlaylistModel);

class McPlaylistModel : public McMusicModel
        , public IMcPlaylistModel {
    
    Q_OBJECT
    MC_DECL_INIT(McPlaylistModel)
    MC_DEFINE_TYPELIST(MC_DECL_TYPELIST(McMusicModel), MC_DECL_TYPELIST(IMcPlaylistModel))
    MC_MODEL
    MC_BEANNAME("playlistModel")
public:
    Q_INVOKABLE McPlaylistModel() noexcept;
    ~McPlaylistModel() noexcept override;
    
    void setMusics(const QList<McMusicPtr> &musics) noexcept override;
    QList<McMusicPtr> getMusics() const noexcept override;
    McMusicPtr getMusic(int index) const noexcept override;
    void addMusic(McMusicConstPtrRef music) noexcept override;
    void addMusic(const QList<McMusicPtr> &musics) noexcept override;
    QList<McMusicPtr> takeMusics(const QList<int> &indexs) noexcept override;
    
private:
    MC_DECL_PRIVATE(McPlaylistModel)
};

MC_DECL_METATYPE(McPlaylistModel)
