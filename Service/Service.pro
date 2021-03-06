QT -= gui
QT += sql network concurrent av qml quickboot

TARGET = $$qt5LibraryTarget($$TARGET)

TEMPLATE = lib
DEFINES += SERVICE_LIBRARY

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += _BUILDING_QX_DAO

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

CONFIG(release, debug|release) {
    DEFINES += QT_MESSAGELOGCONTEXT
}

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/../bin/mcservices
}else:{
    DESTDIR = E:\soft\mine\McAudioPlayer\mcservices
}

include($$PWD/Service.pri)

MOC_DIR = $$PWD/../moc/Service

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Download/GitHub/QxOrm/lib/ -lQxOrm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Download/GitHub/QxOrm/lib/ -lQxOrmd

INCLUDEPATH += $$PWD/../../../Download/GitHub/QxOrm/include
DEPENDPATH += $$PWD/../../../Download/GitHub/QxOrm/include

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
