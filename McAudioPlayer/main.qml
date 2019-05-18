import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import McControllerContainer 1.0
import "./View/SongSheet"
import "./View/MainView"
import "./View/SongControl"

Window {
    visible: true
    width: 800
    height: 600
    minimumWidth: 600
    minimumHeight: 400
    color: "#6b1500"
    title: qsTr("McAudioPlayer")

    McControllerContainer {
        id: controllerContainer
    }

    GridLayout {
        anchors.rightMargin: 9
        anchors.leftMargin: 9
        anchors.bottomMargin: 9
        anchors.topMargin: 9
        columnSpacing: 0
        rowSpacing: 0
        anchors.fill: parent
        columns: 2
        rows: 2
        SongSheet{
            id: songSheetItem
            Layout.preferredWidth: 123
            Layout.fillHeight: true
        }

        MainView {
            id: mainView
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        SongControl {
            id: songControl
            Layout.columnSpan: 2
            Layout.preferredHeight: 104
            Layout.fillWidth: true
        }
    }

    Component.onCompleted: {
        songSheetItem.signal_currentChanged.connect(mainView.updateSongList);
    }
}
