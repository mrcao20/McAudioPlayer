#pragma once

#include "../IMcMusicDao.h"

MC_FORWARD_DECL_PRIVATE_DATA(McMusicDao);

class McMusicDao : public QObject, public IMcMusicDao {
    Q_OBJECT
    MC_DECL_INIT(McMusicDao)
    MC_DEFINE_TYPELIST(QObject, MC_DECL_TYPELIST(IMcMusicDao))
    MC_COMPONENT
    MC_BEANNAME("musicDao")
public:
    Q_INVOKABLE McMusicDao() noexcept;
    ~McMusicDao() noexcept override;
    
    void getMusicUrl(McMusicConstPtrRef music) noexcept override;
    void getMusicDetail(McMusicConstPtrRef music) noexcept override;
    
private:
    MC_DECL_PRIVATE(McMusicDao)
};

MC_DECL_METATYPE(McMusicDao)
