#pragma once

#include "../IMcMusicApi.h"

MC_FORWARD_DECL_PRIVATE_DATA(McAbstractMusic);

class McAbstractMusic : public QObject, public IMcMusicApi {
    Q_OBJECT
    MC_DECL_INIT(McAbstractMusic)
    MC_DEFINE_TYPELIST(QObject, MC_DECL_TYPELIST(IMcMusicApi))
public:
    McAbstractMusic() noexcept;
    ~McAbstractMusic() noexcept override;
    
    QString getMusicUrl(McMusicConstPtrRef music) noexcept override final;
    QList<McMusicPtr> searchSong(const QString &songName, int limit = 20, int offset = 0) noexcept override final;
    
protected:
	virtual QString getUrl(McMusicConstPtrRef music) noexcept = 0;
    virtual QList<McMusicPtr> getMusics(const QString& songName, int limit, int offset) noexcept = 0;
    
protected:
	QJsonValue getJsonValue(const QByteArray& json, const QString& nodeName) noexcept;
	QJsonValue getJsonValue(const QJsonObject& root, const QString& nodeName) noexcept;
	void getValue(QJsonObject& root, QJsonValue& nodeValue, QStringList& nodeList) noexcept;
    
private:
    MC_DECL_PRIVATE(McAbstractMusic)
};

MC_DECL_METATYPE(McAbstractMusic)
