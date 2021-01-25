#pragma once

#include "../IMcMusicService.h"
#include <McBoot/McBootGlobal.h>

MC_FORWARD_DECL_CLASS(IMcMusicDao);
MC_FORWARD_DECL_CLASS(IMcNetMusicRequestor);

MC_FORWARD_DECL_PRIVATE_DATA(McMusicService);

class McMusicService : public QObject, public IMcMusicService {
    Q_OBJECT
    MC_DECL_INIT(McMusicService)
    MC_TYPELIST(QObject, IMcMusicService)
    MC_SERVICE
    MC_BEANNAME("musicService")
    MC_AUTOWIRED("musicDao")
    Q_PROPERTY(IMcMusicDaoPtr musicDao READ musicDao WRITE setMusicDao)
    MC_AUTOWIRED("requestor")
    Q_PRIVATE_PROPERTY(d, IMcNetMusicRequestorPtr requestor MEMBER requestor)
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
