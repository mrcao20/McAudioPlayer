#pragma once

#include "../IMcMusicService.h"

MC_FORWARD_DECL_CLASS(IMcMusicDao);

MC_FORWARD_DECL_PRIVATE_DATA(McMusicService);

class McMusicService : public QObject, public IMcMusicService {
    Q_OBJECT
    MC_DECL_INIT(McMusicService)
    MC_DEFINE_TYPELIST(QObject, MC_DECL_TYPELIST(IMcMusicService))
    Q_CLASSINFO(MC_BEANNAME, "musicService")
    Q_PROPERTY(IMcMusicDaoPtr musicDao READ musicDao WRITE setMusicDao USER true)
public:
    Q_INVOKABLE McMusicService() noexcept;
    ~McMusicService() noexcept override;
    
    IMcMusicDaoPtr musicDao() const noexcept;
    void setMusicDao(IMcMusicDaoConstPtrRef val) noexcept;
    
    void acquireMusicUrl(McMusicConstPtrRef music) noexcept override;
    
private:
    MC_DECL_PRIVATE(McMusicService)
};

MC_DECL_METATYPE(McMusicService)
