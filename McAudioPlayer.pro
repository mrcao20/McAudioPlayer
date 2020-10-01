QT += quick sql network concurrent av
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += _BUILDING_QX_DAO

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    include/McAudioPlayer/Controller/McNetworkMusicController.h \
    include/McAudioPlayer/Controller/McPlaylistController.h \
    include/McAudioPlayer/Controller/McSongSheetController.h \
    include/McAudioPlayer/Controller/McSonglistController.h \
    include/McAudioPlayer/Dao/IMcMusicDao.h \
    include/McAudioPlayer/Dao/IMcNetworkMusicDao.h \
    include/McAudioPlayer/Dao/IMcPlaylistDao.h \
    include/McAudioPlayer/Dao/IMcSongSheetDao.h \
    include/McAudioPlayer/Dao/IMcSonglistDao.h \
    include/McAudioPlayer/Dao/impl/McMusicDao.h \
    include/McAudioPlayer/Dao/impl/McNetworkMusicDao.h \
    include/McAudioPlayer/Dao/impl/McPlaylistDao.h \
    include/McAudioPlayer/Dao/impl/McSongSheetDao.h \
    include/McAudioPlayer/Dao/impl/McSonglistDao.h \
    include/McAudioPlayer/Domain/Po/McAlbumPo.h \
    include/McAudioPlayer/Domain/Po/McArtistPo.h \
    include/McAudioPlayer/Domain/Po/McMusicDetailPo.h \
    include/McAudioPlayer/Domain/Po/McMusicPo.h \
    include/McAudioPlayer/Domain/Po/McPlaylistPo.h \
    include/McAudioPlayer/Domain/Po/McSongSheetPo.h \
    include/McAudioPlayer/Domain/Po/McSonglistPo.h \
    include/McAudioPlayer/Domain/Vo/McAlbum.h \
    include/McAudioPlayer/Domain/Vo/McArtist.h \
    include/McAudioPlayer/Domain/Vo/McMusic.h \
    include/McAudioPlayer/Domain/Vo/McSongSheet.h \
    include/McAudioPlayer/McExceptionFilter.h \
    include/McAudioPlayer/McGlobal.h \
    include/McAudioPlayer/McMacroDefines.h \
    include/McAudioPlayer/Model/IMcMusicModel.h \
    include/McAudioPlayer/Model/IMcNetworkMusicModel.h \
    include/McAudioPlayer/Model/IMcPlaylistModel.h \
    include/McAudioPlayer/Model/IMcSongSheetModel.h \
    include/McAudioPlayer/Model/IMcSonglistModel.h \
    include/McAudioPlayer/Model/impl/McMusicModel.h \
    include/McAudioPlayer/Model/impl/McNetworkMusicModel.h \
    include/McAudioPlayer/Model/impl/McPlaylistModel.h \
    include/McAudioPlayer/Model/impl/McSongSheetModel.h \
    include/McAudioPlayer/Model/impl/McSonglistModel.h \
    include/McAudioPlayer/Requestor/Api/IMcMusicApi.h \
    include/McAudioPlayer/Requestor/Api/impl/McAbstractMusic.h \
    include/McAudioPlayer/Requestor/Api/impl/McQQMusic.h \
    include/McAudioPlayer/Requestor/Api/impl/McYMusic.h \
    include/McAudioPlayer/Requestor/IMcNetMusicRequestor.h \
    include/McAudioPlayer/Requestor/impl/McNetMusicRequestor.h \
    include/McAudioPlayer/Service/IMcAcquireModel.h \
    include/McAudioPlayer/Service/IMcAcquireMusic.h \
    include/McAudioPlayer/Service/IMcMusicForSongSheet.h \
    include/McAudioPlayer/Service/IMcMusicService.h \
    include/McAudioPlayer/Service/IMcNetworkMusicService.h \
    include/McAudioPlayer/Service/IMcPlaylistService.h \
    include/McAudioPlayer/Service/IMcSongSheetService.h \
    include/McAudioPlayer/Service/IMcSonglistService.h \
    include/McAudioPlayer/Service/impl/McMusicService.h \
    include/McAudioPlayer/Service/impl/McNetworkMusicService.h \
    include/McAudioPlayer/Service/impl/McPlaylistService.h \
    include/McAudioPlayer/Service/impl/McSongSheetService.h \
    include/McAudioPlayer/Service/impl/McSonglistService.h \
    include/McAudioPlayer/Utils/McNetUtils.h \
    include/McAudioPlayer/Utils/McOrmUtils.h \
    include/McAudioPlayer/version.h

SOURCES += \
        src/Controller/McNetworkMusicController.cpp \
        src/Controller/McPlaylistController.cpp \
        src/Controller/McSongSheetController.cpp \
        src/Controller/McSonglistController.cpp \
        src/Dao/McMusicDao.cpp \
        src/Dao/McNetworkMusicDao.cpp \
        src/Dao/McPlaylistDao.cpp \
        src/Dao/McSongSheetDao.cpp \
        src/Dao/McSonglistDao.cpp \
        src/Domain/Po/McAlbumPo.cpp \
        src/Domain/Po/McArtistPo.cpp \
        src/Domain/Po/McMusicDetailPo.cpp \
        src/Domain/Po/McMusicPo.cpp \
        src/Domain/Po/McPlaylistPo.cpp \
        src/Domain/Po/McSongSheetPo.cpp \
        src/Domain/Po/McSonglistPo.cpp \
        src/Domain/Vo/McAlbum.cpp \
        src/Domain/Vo/McArtist.cpp \
        src/Domain/Vo/McMusic.cpp \
        src/Domain/Vo/McSongSheet.cpp \
        src/McExceptionFilter.cpp \
        src/McGlobal.cpp \
        src/Model/McMusicModel.cpp \
        src/Model/McNetworkMusicModel.cpp \
        src/Model/McPlaylistModel.cpp \
        src/Model/McSongSheetModel.cpp \
        src/Model/McSonglistModel.cpp \
        src/Requestor/Api/McAbstractMusic.cpp \
        src/Requestor/Api/McQQMusic.cpp \
        src/Requestor/Api/McYMusic.cpp \
        src/Requestor/McNetMusicRequestor.cpp \
        src/Service/McMusicService.cpp \
        src/Service/McNetworkMusicService.cpp \
        src/Service/McPlaylistService.cpp \
        src/Service/McSongSheetService.cpp \
        src/Service/McSonglistService.cpp \
        src/Utils/McNetUtils.cpp \
        src/main.cpp

RESOURCES += qrc/qml/qml.qrc \
    qrc/icon/icon.qrc

win32 {
    RC_ICONS = qrc/icon/format.ico
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CONFIG(release, debug|release) {
    DEFINES += QT_MESSAGELOGCONTEXT
}

INCLUDEPATH += $$PWD/include/

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/bin
}else:{
    DESTDIR = E:\soft\mine\McAudioPlayer
}

MOC_DIR = $$PWD/moc

LIBS += -lDbghelp
LIBS += -luser32

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../McIocBoot/bin/ -lMcIocContainer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../McIocBoot/bin/ -lMcIocContainerd
else:unix:!macx: LIBS += -L$$PWD/../McIocBoot/bin/ -lMcIocContainer

INCLUDEPATH += $$PWD/../McIocBoot/McIocContainer/include
DEPENDPATH += $$PWD/../McIocBoot/McIocContainer/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../McIocBoot/bin/ -lMcIocBoot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../McIocBoot/bin/ -lMcIocBootd
else:unix:!macx: LIBS += -L$$PWD/../McIocBoot/bin/ -lMcIocBoot

INCLUDEPATH += $$PWD/../McIocBoot/McIocBoot/include
DEPENDPATH += $$PWD/../McIocBoot/McIocBoot/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../McLogQt/bin/ -lMcLogQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../McLogQt/bin/ -lMcLogQtd

INCLUDEPATH += $$PWD/../McLogQt/McLogQt/include
DEPENDPATH += $$PWD/../McLogQt/McLogQt/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Download/GitHub/QxOrm/lib/ -lQxOrm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Download/GitHub/QxOrm/lib/ -lQxOrmd

INCLUDEPATH += $$PWD/../../Download/GitHub/QxOrm/include
DEPENDPATH += $$PWD/../../Download/GitHub/QxOrm/include

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
