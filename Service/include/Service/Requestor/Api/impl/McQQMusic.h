#pragma once

#include "McAbstractMusic.h"

MC_FORWARD_DECL_PRIVATE_DATA(McQQMusic);

class McQQMusic : public McAbstractMusic {
    Q_OBJECT
    MC_DECL_INIT(McQQMusic)
    MC_TYPELIST(McAbstractMusic)
public:
    Q_INVOKABLE McQQMusic() noexcept;
    ~McQQMusic() noexcept override;
    
protected:
    QString getUrl(McMusicConstPtrRef music) noexcept override;
    QString getDownloadLink(McMusicConstPtrRef music) noexcept override;
    QList<McMusicPtr> getMusics(const QString& songName, int limit, int offset) noexcept override;
    
private:
    MC_DECL_PRIVATE(McQQMusic)
};

MC_DECL_METATYPE(McQQMusic)
