import QtQuick 2.12

QtObject {
	id: root

    property QtObject splashScreen: McSplashScreen {}

	property var loader: Loader {
        asynchronous: true
        source: "qrc:/MainWindow.qml"
        active: false
        onLoaded: {
            splashScreen.hide();
        }
    }
    
    Component.onCompleted: {
        loader.active = true;
    }
}
