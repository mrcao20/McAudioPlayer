import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../Component"
import "../Common"

Item {
    anchors.left: parent.left
    anchors.leftMargin: 10
    anchors.right: parent.right
    anchors.rightMargin: 10
    anchors.top: parent.top
    anchors.topMargin: 5
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 5
    HoverableText {
        id: topText
        anchors.right: songControl.left
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        height: parent.height / 2
        font.pixelSize: 14
        text: songName
        color: hovered ? "#1827ff" : playlistView.currentIndex === index ? "#ffffff" : "#d1d1d1"
    }
    HoverableText {
        anchors.right: songControl.left
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: topText.bottom
        anchors.topMargin: 0
        font.pixelSize: 14
        text: artist
        color: hovered ? "#1827ff" : playlistView.currentIndex === index ? "#ffffff" : "#b5b5b5"
    }
    Rectangle {
        id: songControl
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        color: "#00000000"
        width: 90
        visible: (parent.parent.hovered || playlistView.currentIndex === index) ? true : false
        PlayToolTipButton{
            id: playBtn
            anchors.left: parent.left
            anchors.leftMargin: 0
            onSignal_clicked: {
                playIndex(index);
            }
        }
        AddToToolTipButton{
            id: addToBtn
            anchors.left: playBtn.right
            anchors.leftMargin: 5
        }
        MoreToolTipButton{
            anchors.left: addToBtn.right
            anchors.leftMargin: 5
        }
    }
}
