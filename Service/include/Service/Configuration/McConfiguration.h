#pragma once

#include <McBoot/McBootGlobal.h>
#include <QObject>

MC_FORWARD_DECL_CLASS(IMcNetMusicRequestor);

MC_FORWARD_DECL_PRIVATE_DATA(McConfiguration);

class McConfiguration : public QObject
{
    Q_OBJECT
    MC_BEANNAME("config")
    MC_CONFIGURATION()
public:
    Q_INVOKABLE explicit McConfiguration(QObject *parent = nullptr) noexcept;
    ~McConfiguration() override;

    Q_INVOKABLE
    MC_BEAN
    IMcNetMusicRequestorPtr requestor() const noexcept;

private:
    MC_DECL_PRIVATE(McConfiguration)
};

MC_DECL_METATYPE(McConfiguration)

