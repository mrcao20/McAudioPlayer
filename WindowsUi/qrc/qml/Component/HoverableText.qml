import QtQuick 2.12
import QtQuick.Controls 2.5

Text {
    property bool hovered: mouseArea.containsMouse
    verticalAlignment: Text.AlignVCenter
    font.pixelSize: 15
    font.bold: true
    elide: Text.ElideRight
    MouseArea {
        id: mouseArea
        width: parent.contentWidth
        height: parent.contentHeight
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
    }
    ToolTip {
        visible: parent.hovered
        delay: 500
        text: parent.text
        x: mouseArea.mouseX
        y: mouseArea.mouseY + 20
    }
}
