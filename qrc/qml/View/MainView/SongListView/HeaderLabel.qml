import QtQuick 2.12
import QtQuick.Controls 2.5

Label {
    color: "#ffffff"
    verticalAlignment: Text.AlignVCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    anchors.top: parent.top
    anchors.topMargin: 0
    font.pixelSize: 15
    font.bold: true
    background: Rectangle {
        color: "#6b1500"
        anchors.fill: parent
        border.color: "#404040"
        border.width: 1
    }
}
