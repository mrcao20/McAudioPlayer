#pragma once

#include "../IMcNetMusicRequestor.h"

MC_FORWARD_DECL_CLASS(IMcMusicApi);

MC_FORWARD_DECL_PRIVATE_DATA(McNetMusicRequestor);

typedef QMap<QString, IMcMusicApiPtr> McMusicApis;

class McNetMusicRequestor : public QObject, public IMcNetMusicRequestor {
    Q_OBJECT
    MC_DECL_INIT(McNetMusicRequestor)
    MC_DEFINE_TYPELIST(QObject, MC_DECL_TYPELIST(IMcNetMusicRequestor))
    Q_PROPERTY(McMusicApis musicApis READ musicApis WRITE setMusicApis)
public:
    Q_INVOKABLE McNetMusicRequestor() noexcept;
    ~McNetMusicRequestor() noexcept override;
    
    McMusicApis musicApis() const noexcept;
    void setMusicApis(const McMusicApis &val) noexcept;
    
    QString getMusicUrl(McMusicConstPtrRef music) noexcept override;
    QList<McMusicPtr> getNetworkMusics(const QString &musicSrc, const QString &keyword) noexcept override;
    QList<McMusicPtr> getLastPageMusic() noexcept override;
    QList<McMusicPtr> getNextPageMusic() noexcept override;
    
private:
    QList<McMusicPtr> getNetworkMusics() noexcept;
    
private:
    MC_DECL_PRIVATE(McNetMusicRequestor)
};

MC_DECL_METATYPE(McNetMusicRequestor)
