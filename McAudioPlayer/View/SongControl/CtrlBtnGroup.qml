import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    implicitWidth: childrenRect.width
    Button {
        id: previousBtn
        width: 25
        height: 25
        text: qsTr("")
        anchors.verticalCenter: parent.verticalCenter
        background: Image {
            source: parent.hovered ? "qrc:/icon/previous_hover.png" : "qrc:/icon/previous.png"
        }
    }

    Button {
        id: playButton
        width: 32
        height: 32
        text: qsTr("")
        anchors.left: previousBtn.right
        anchors.leftMargin: 6
        anchors.verticalCenter: parent.verticalCenter
        background: Image {
            source: parent.hovered ? "qrc:/icon/play_hover.png" : "qrc:/icon/play.png"
        }
    }

    Button {
        id: nextBtn
        width: 25
        height: 25
        text: qsTr("")
        anchors.left: playButton.right
        anchors.leftMargin: 6
        anchors.verticalCenter: parent.verticalCenter
        background: Image {
            source: parent.hovered ? "qrc:/icon/next_hover.png" : "qrc:/icon/next.png"
        }
    }
}
