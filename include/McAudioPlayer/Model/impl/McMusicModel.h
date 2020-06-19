#pragma once

#include <QAbstractListModel>

#include <QEvent>

#include <McBoot/McBootGlobal.h>

MC_FORWARD_DECL_CLASS(McMusic);

class McUpdateMusicEvent : public QEvent {
public:
    enum MusicType {
        SetType = QEvent::User,
        AddType
    };
    McUpdateMusicEvent(MusicType type, const QList<McMusicPtr> &musics) noexcept;
    ~McUpdateMusicEvent() noexcept override;
    
    QList<McMusicPtr> musics() const noexcept {
        return m_musics;
    }
    void setMusics(const QList<McMusicPtr> &val) noexcept {
        m_musics = val;
    }
    
private:
    QList<McMusicPtr> m_musics;
};

MC_FORWARD_DECL_PRIVATE_DATA(McMusicModel);

class McMusicModel : public QAbstractListModel {
    Q_OBJECT
    MC_DECL_INIT(McMusicModel)
    MC_DEFINE_TYPELIST(QAbstractListModel)
public:
    enum Roles {
        SongNameRole = Qt::UserRole + 1,
        AlbumNamesRole,
        ArtistNamesRole
    };
    Q_INVOKABLE McMusicModel() noexcept;
    ~McMusicModel() noexcept override;
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    
protected:
    void customEvent(QEvent *event) override;
    
protected:
    QList<McMusicPtr> musics() const noexcept;
    QList<McMusicPtr> takeMusics(const QList<int> &indexs) noexcept;
    McMusicPtr music(int index) const noexcept;
    
private:
    void doSetMusics(const QList<McMusicPtr> &musics) noexcept;
    void doAddMusics(const QList<McMusicPtr> &musics) noexcept;
    void doClear() noexcept;
    Q_INVOKABLE QList<McMusicPtr> doTakeMusics(const QList<int> &indexs) noexcept;
    
private:
    MC_DECL_PRIVATE(McMusicModel)
};

MC_DECL_METATYPE(McMusicModel)
