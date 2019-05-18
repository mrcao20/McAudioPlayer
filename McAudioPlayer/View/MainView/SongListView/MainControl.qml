import QtQuick 2.12
import QtQuick.Controls 2.5

Control {
    property string text: ""
    hoverEnabled: true
    Text {
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 15
        font.bold: true
        color: parent.hovered ? "#1827ff" : songListView.currentIndex === index ? "#ffffff" : "#b5b5b5"
        text: parent.text
    }
    Rectangle {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        color: "#00000000"
        width: 125
        visible: (parent.hovered || songListView.currentIndex === index) ? true : false
        Button {
            id: playBtn
            width: 25
            height: 20
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.verticalCenter: parent.verticalCenter
            hoverEnabled: true
            background: Image {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: parent.hovered ? "qrc:/icon/playButton_hover.png" : "qrc:/icon/playButton.png"
            }
        }
        Button {
            id: addToBtn
            width: 25
            height: 20
            anchors.left: playBtn.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            hoverEnabled: true
            background: Image {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: parent.hovered ? "qrc:/icon/addTo_hover.png" : "qrc:/icon/addTo.png"
            }
        }
        Button {
            id: downloadBtn
            width: 25
            height: 20
            anchors.left: addToBtn.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            hoverEnabled: true
            background: Image {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: parent.hovered ? "qrc:/icon/download_hover.png" : "qrc:/icon/download.png"
            }
        }
        Button {
            width: 25
            height: 20
            anchors.left: downloadBtn.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            hoverEnabled: true
            background: Image {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: parent.hovered ? "qrc:/icon/more_hover.png" : "qrc:/icon/more.png"
            }
        }
    }
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    anchors.top: parent.top
    anchors.topMargin: 0
}
