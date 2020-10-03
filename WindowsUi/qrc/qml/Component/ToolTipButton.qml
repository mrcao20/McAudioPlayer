import QtQuick 2.12
import QtQuick.Controls 2.5

Button {
    property string tipText: ""
    property string normalIcon: ""
    property string hoveredIcon: ""
    signal signal_clicked(var mouse)
    width: 25
    height: 20
    hoverEnabled: true
    background: Image {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        source: parent.hovered ? hoveredIcon : normalIcon
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            signal_clicked(mouse);
        }
    }
    ToolTip {
        visible: parent.hovered
        delay: 500
        text: parent.tipText
        x: mouseArea.mouseX
        y: mouseArea.mouseY + 20
    }
}
