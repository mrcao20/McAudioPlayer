#pragma once

#include "McAbstractMusic.h"

MC_FORWARD_DECL_PRIVATE_DATA(McYMusic);

class McYMusic : public McAbstractMusic {
    Q_OBJECT
    MC_DECL_INIT(McYMusic)
    MC_DEFINE_TYPELIST(MC_DECL_TYPELIST(McAbstractMusic))
public:
    Q_INVOKABLE McYMusic() noexcept;
    ~McYMusic() noexcept override;
    
protected:
    QString getUrl(McMusicConstPtrRef music) noexcept override;
    QList<McMusicPtr> getMusics(const QString& songName, int limit, int offset) noexcept override;
    
private:
    QList<McMusicPtr> getMusics(const QString& songName, int limit, int offset, const QString& type, bool total) noexcept;
    
private:
    MC_DECL_PRIVATE(McYMusic)
};

MC_DECL_METATYPE(McYMusic)
