import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: splash
    
    color: "transparent"
    title: "Splash Window"
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen | Qt.WindowStaysOnTopHint
    x: (Screen.width - splashImage.width) / 2
    y: (Screen.height - splashImage.height) / 2
    width: splashImage.width
    height: splashImage.height
    
    AnimatedImage {
        id: splashImage
        source: "qrc:/icon/bkns.gif"
    }

    Component.onCompleted: {
        splash.show();
    }
}
