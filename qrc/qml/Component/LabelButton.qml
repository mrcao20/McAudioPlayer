import QtQuick 2.12
import QtQuick.Controls 2.5

Button {
    property Item hoverableItem: this
    property var horizontalAlignment: Text.AlignHCenter
    font.pixelSize: 15
    contentItem: Label {
        anchors.fill: parent
        font: parent.font
        color: hoverableItem.hovered ? "#ffffff" : "#969696"
        text: parent.text
        horizontalAlignment: parent.horizontalAlignment
        verticalAlignment: Text.AlignVCenter
    }
    background: Rectangle {
        color: "#00000000"
    }
}
