import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../../Component"

Control {
    property string text: ""
    property var listView: null
    hoverEnabled: true
    HoverableText {
        anchors.fill: parent
        text: parent.text
        color: hovered ? "#1827ff" : listView.currentIndex === index ? "#ffffff" : "#b5b5b5"
    }
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    anchors.top: parent.top
    anchors.topMargin: 0
    font.pixelSize: 15
    font.bold: true
}
