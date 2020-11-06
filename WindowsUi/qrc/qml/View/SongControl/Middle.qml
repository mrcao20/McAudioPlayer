import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    Item {
        id: tipItem
        implicitHeight: childrenRect.height
        anchors.bottom: progressItem.top
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        Label {
            id: songNameLabel
            color: "#787878"
            text: mainWindow.curMusic === null ? qsTr("无音乐") : mainWindow.curMusic.songTitle
            font.pixelSize: 15
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.right: songTimeLabel.left
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        Label {
            id: songTimeLabel
            width: 101
            height: 21
            color: "#787878"
            text: {
                var pos = mediaPlayer.position;
                var dur = mediaPlayer.duration;
                return new Date(pos).toLocaleString(Qt.locale("de_DE"), "mm:ss") + "/" + new Date(dur).toLocaleString(Qt.locale("de_DE"), "mm:ss");
            }
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
        }
    }

    Item {
        id: progressItem
        height: progressBar.height
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        CustomSlider {
            id: progressBar
        }
    }
}
