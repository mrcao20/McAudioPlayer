import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../Component"

Item {
    id: element
    implicitWidth: leftItem.width + playOrderBtn.width + volumeBtn.width + playlistBtn.width
    Item {
        id: leftItem
        anchors.right: playOrderBtn.left
        anchors.rightMargin: 6
        implicitHeight: lyricBtn.height + lyricTranslatedBtn.height
        width: 21
        anchors.verticalCenter: parent.verticalCenter
        LabelButton {
            id: lyricBtn
            height: 21
            text: qsTr("词")
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: lyricTranslatedBtn.top
            anchors.bottomMargin: 0
        }

        LabelButton {
            id: lyricTranslatedBtn
            height: 21
            text: qsTr("译")
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
        }
    }

    Button {
        id: playOrderBtn
        width: 20
        height: 20
        text: qsTr("Button")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: volumeBtn.left
        anchors.rightMargin: 6
        background: Image {
            anchors.fill: parent
            source: parent.hovered ? "qrc:/icon/shuffle_hover.png" : "qrc:/icon/shuffle.png"
        }
    }

    Button {
        id: volumeBtn
        width: 24
        height: 24
        text: qsTr("Button")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: playlistBtn.left
        anchors.rightMargin: 6
        background: Image {
            anchors.fill: parent
            source: parent.hovered ? "qrc:/icon/volume_hover.png" : "qrc:/icon/volume.png"
        }
    }

    Button {
        id: playlistBtn
        width: 46
        height: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 0
        background: Item {
            anchors.fill: parent
            Button {
                id: playListImg
                height: playlistBtn.height
                anchors.verticalCenter: parent.verticalCenter
                width: 24
                anchors.left: parent.left
                anchors.leftMargin: 0
                background: Image {
                    anchors.fill: parent
                    source: playlistBtn.hovered ? "qrc:/icon/playlist_hover.png" : "qrc:/icon/playlist.png"
                }
            }
            LabelButton {
                id: playListNum
                text: qsTr("0")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: playListImg.right
                anchors.leftMargin: 0
                horizontalAlignment: Text.AlignLeft
                hoverableItem: playlistBtn
            }
        }
    }
}
