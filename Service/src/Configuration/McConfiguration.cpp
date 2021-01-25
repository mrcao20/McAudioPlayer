#include "Service/Configuration/McConfiguration.h"

#include <QDir>

#include <McIoc/ApplicationContext/impl/McLocalPathApplicationContext.h>

#include "Service/McGlobal.h"
#include "Service/Requestor/IMcNetMusicRequestor.h"

MC_STATIC()
MC_REGISTER_BEAN_FACTORY(McConfiguration)
MC_STATIC_END

MC_DECL_PRIVATE_DATA(McConfiguration)
MC_DECL_PRIVATE_DATA_END

McConfiguration::McConfiguration(QObject *parent) noexcept
    : QObject(parent)
{
    MC_NEW_PRIVATE_DATA(McConfiguration);
}

McConfiguration::~McConfiguration()
{
}

IMcNetMusicRequestorPtr McConfiguration::requestor() const noexcept
{
    auto configPath = QDir(qApp->applicationDirPath()).filePath(MC_NET_MUSIC_REQUESTOR_CONFIG_PATH);
    configPath = QDir::cleanPath(configPath);
    qInfo() << "the net music requestor config path:" << configPath;
    auto appCxt = McLocalPathApplicationContextPtr::create(configPath);
    return appCxt->getBean<IMcNetMusicRequestor>("requestor");
}
