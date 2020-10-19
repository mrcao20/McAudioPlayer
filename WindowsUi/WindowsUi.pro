QT += quick

TARGET = McAudioPlayer

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    McExceptionFilter.h

SOURCES += \
        McExceptionFilter.cpp \
        main.cpp
        
RESOURCES += \
    qrc/icon/icon.qrc \
    qrc/qml/qml.qrc
    
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

LIBS += -lDbghelp
LIBS += -luser32

CONFIG(release, debug|release) {
    DEFINES += QT_MESSAGELOGCONTEXT
}

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/../bin
    LIBS += -L$$PWD/../bin/ -lServiced
}else:{
    DESTDIR = E:\soft\mine\McAudioPlayer
    LIBS += -LE:\soft\mine\McAudioPlayer -lService
}

MOC_DIR = $$PWD/../moc/WindowsUi

include($$PWD/../../McQuickBoot/McQuickBoot/McQuickBootDepend.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../McQuickBoot/bin/ -lMcQuickBoot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../McQuickBoot/bin/ -lMcQuickBootd
else:unix:!macx: LIBS += -L$$PWD/../../McQuickBoot/bin/ -lMcQuickBoot

INCLUDEPATH += $$PWD/../../McQuickBoot/McQuickBoot/include
DEPENDPATH += $$PWD/../../McQuickBoot/McQuickBoot/include

INCLUDEPATH += $$PWD/../Service/include
DEPENDPATH += $$PWD/../Service/include

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
