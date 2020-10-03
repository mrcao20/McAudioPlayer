#pragma once

#include "../IMcSonglistModel.h"
#include "McMusicModel.h"

#include <McBoot/McBootGlobal.h>

MC_FORWARD_DECL_PRIVATE_DATA(McSonglistModel);

class McSonglistModel : public McMusicModel
        , public IMcSonglistModel {
    
    Q_OBJECT
    MC_DECL_INIT(McSonglistModel)
    MC_DEFINE_TYPELIST(MC_DECL_TYPELIST(McMusicModel), MC_DECL_TYPELIST(IMcSonglistModel))
    MC_MODEL
    MC_BEANNAME("songlistModel")
public:
    Q_INVOKABLE McSonglistModel() noexcept;
    ~McSonglistModel() noexcept override;
    
    void setMusics(const QList<McMusicPtr> &musics) noexcept override;
    QList<McMusicPtr> getMusics() const noexcept override;
    McMusicPtr getMusic(int index) const noexcept override;
    void addMusic(McMusicConstPtrRef music) noexcept override;
    void addMusic(const QList<McMusicPtr> &musics) noexcept override;
    QList<McMusicPtr> takeMusics(const QList<int> &indexs) noexcept override;
    
private:
    MC_DECL_PRIVATE(McSonglistModel)
};

MC_DECL_METATYPE(McSonglistModel)
