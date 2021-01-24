#pragma once

#include "../IMcMusicDao.h"

MC_FORWARD_DECL_PRIVATE_DATA(McMusicDao);

class McMusicDao : public QObject, public IMcMusicDao {
    Q_OBJECT
    MC_DECL_INIT(McMusicDao)
    MC_TYPELIST(QObject, IMcMusicDao)
    MC_COMPONENT
    MC_BEANNAME("musicDao")
public:
    Q_INVOKABLE McMusicDao() noexcept;
    ~McMusicDao() noexcept override;
    
    void getMusicUrl(McMusicConstPtrRef music) noexcept override;
    void getMusicDetail(McMusicConstPtrRef music) noexcept override;
    void updateMusicUrl(McMusicConstPtrRef music) noexcept override;

private:
    Q_INVOKABLE void getMusicUrl_helper(const McMusicPtr &music) noexcept;
    Q_INVOKABLE void getMusicDetail_helper(const McMusicPtr &music) noexcept;
    Q_INVOKABLE void updateMusicUrl_helper(const McMusicPtr &music) noexcept;

private:
    MC_DECL_PRIVATE(McMusicDao)
};

MC_DECL_METATYPE(McMusicDao)
