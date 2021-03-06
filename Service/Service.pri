HEADERS += \
    $$PWD/include/Service/Configuration/McConfiguration.h \
    $$PWD/include/Service/Controller/McNetworkMusicController.h \
    $$PWD/include/Service/Controller/McPlaylistController.h \
    $$PWD/include/Service/Controller/McSongSheetController.h \
    $$PWD/include/Service/Controller/McSonglistController.h \
    $$PWD/include/Service/Dao/IMcMusicDao.h \
    $$PWD/include/Service/Dao/IMcNetworkMusicDao.h \
    $$PWD/include/Service/Dao/IMcPlaylistDao.h \
    $$PWD/include/Service/Dao/IMcSongSheetDao.h \
    $$PWD/include/Service/Dao/IMcSonglistDao.h \
    $$PWD/include/Service/Dao/impl/McMusicDao.h \
    $$PWD/include/Service/Dao/impl/McNetworkMusicDao.h \
    $$PWD/include/Service/Dao/impl/McPlaylistDao.h \
    $$PWD/include/Service/Dao/impl/McSongSheetDao.h \
    $$PWD/include/Service/Dao/impl/McSonglistDao.h \
    $$PWD/include/Service/Domain/Po/McAlbumPo.h \
    $$PWD/include/Service/Domain/Po/McArtistPo.h \
    $$PWD/include/Service/Domain/Po/McMusicDetailPo.h \
    $$PWD/include/Service/Domain/Po/McMusicPo.h \
    $$PWD/include/Service/Domain/Po/McPlaylistPo.h \
    $$PWD/include/Service/Domain/Po/McSongSheetPo.h \
    $$PWD/include/Service/Domain/Po/McSonglistPo.h \
    $$PWD/include/Service/Domain/Vo/McAlbum.h \
    $$PWD/include/Service/Domain/Vo/McArtist.h \
    $$PWD/include/Service/Domain/Vo/McMusic.h \
    $$PWD/include/Service/Domain/Vo/McSongSheet.h \
    $$PWD/include/Service/McGlobal.h \
    $$PWD/include/Service/McMacroDefines.h \
    $$PWD/include/Service/Model/IMcMusicModel.h \
    $$PWD/include/Service/Model/IMcNetworkMusicModel.h \
    $$PWD/include/Service/Model/IMcPlaylistModel.h \
    $$PWD/include/Service/Model/IMcSongSheetModel.h \
    $$PWD/include/Service/Model/IMcSonglistModel.h \
    $$PWD/include/Service/Model/impl/McMusicModel.h \
    $$PWD/include/Service/Model/impl/McNetworkMusicModel.h \
    $$PWD/include/Service/Model/impl/McPlaylistModel.h \
    $$PWD/include/Service/Model/impl/McSongSheetModel.h \
    $$PWD/include/Service/Model/impl/McSonglistModel.h \
    $$PWD/include/Service/Requestor/Api/IMcMusicApi.h \
    $$PWD/include/Service/Requestor/Api/impl/McAbstractMusic.h \
    $$PWD/include/Service/Requestor/Api/impl/McQQMusic.h \
    $$PWD/include/Service/Requestor/Api/impl/McYMusic.h \
    $$PWD/include/Service/Requestor/IMcNetMusicRequestor.h \
    $$PWD/include/Service/Requestor/impl/McNetMusicRequestor.h \
    $$PWD/include/Service/Service/IMcAcquireModel.h \
    $$PWD/include/Service/Service/IMcAcquireMusic.h \
    $$PWD/include/Service/Service/IMcMusicForSongSheet.h \
    $$PWD/include/Service/Service/IMcMusicService.h \
    $$PWD/include/Service/Service/IMcNetworkMusicService.h \
    $$PWD/include/Service/Service/IMcPlaylistService.h \
    $$PWD/include/Service/Service/IMcSongSheetService.h \
    $$PWD/include/Service/Service/IMcSonglistService.h \
    $$PWD/include/Service/Service/impl/McMusicService.h \
    $$PWD/include/Service/Service/impl/McNetworkMusicService.h \
    $$PWD/include/Service/Service/impl/McPlaylistService.h \
    $$PWD/include/Service/Service/impl/McSongSheetService.h \
    $$PWD/include/Service/Service/impl/McSonglistService.h \
    $$PWD/include/Service/Utils/McNetUtils.h \
    $$PWD/include/Service/Utils/McOrmUtils.h

SOURCES += \
    $$PWD/src/Configuration/McConfiguration.cpp \
    $$PWD/src/Controller/McNetworkMusicController.cpp \
    $$PWD/src/Controller/McPlaylistController.cpp \
    $$PWD/src/Controller/McSongSheetController.cpp \
    $$PWD/src/Controller/McSonglistController.cpp \
    $$PWD/src/Dao/McMusicDao.cpp \
    $$PWD/src/Dao/McNetworkMusicDao.cpp \
    $$PWD/src/Dao/McPlaylistDao.cpp \
    $$PWD/src/Dao/McSongSheetDao.cpp \
    $$PWD/src/Dao/McSonglistDao.cpp \
    $$PWD/src/Domain/Po/McAlbumPo.cpp \
    $$PWD/src/Domain/Po/McArtistPo.cpp \
    $$PWD/src/Domain/Po/McMusicDetailPo.cpp \
    $$PWD/src/Domain/Po/McMusicPo.cpp \
    $$PWD/src/Domain/Po/McPlaylistPo.cpp \
    $$PWD/src/Domain/Po/McSongSheetPo.cpp \
    $$PWD/src/Domain/Po/McSonglistPo.cpp \
    $$PWD/src/Domain/Vo/McAlbum.cpp \
    $$PWD/src/Domain/Vo/McArtist.cpp \
    $$PWD/src/Domain/Vo/McMusic.cpp \
    $$PWD/src/Domain/Vo/McSongSheet.cpp \
    $$PWD/src/McGlobal.cpp \
    $$PWD/src/Model/McMusicModel.cpp \
    $$PWD/src/Model/McNetworkMusicModel.cpp \
    $$PWD/src/Model/McPlaylistModel.cpp \
    $$PWD/src/Model/McSongSheetModel.cpp \
    $$PWD/src/Model/McSonglistModel.cpp \
    $$PWD/src/Requestor/Api/McAbstractMusic.cpp \
    $$PWD/src/Requestor/Api/McQQMusic.cpp \
    $$PWD/src/Requestor/Api/McYMusic.cpp \
    $$PWD/src/Requestor/McNetMusicRequestor.cpp \
    $$PWD/src/Service/McMusicService.cpp \
    $$PWD/src/Service/McNetworkMusicService.cpp \
    $$PWD/src/Service/McPlaylistService.cpp \
    $$PWD/src/Service/McSongSheetService.cpp \
    $$PWD/src/Service/McSonglistService.cpp \
    $$PWD/src/Utils/McNetUtils.cpp

INCLUDEPATH += $$PWD/include/

RESOURCES += \
    $$PWD/qrc/qrc.qrc
