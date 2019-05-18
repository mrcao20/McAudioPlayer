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
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    anchors.top: parent.top
    anchors.topMargin: 0
    font.pixelSize: 15
    font.bold: true
}
