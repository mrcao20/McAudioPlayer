import QtQuick 2.12
import "../../Component"

ToolTipButton {
    anchors.verticalCenter: parent.verticalCenter
    tipText: qsTr("播放")
    normalIcon: "qrc:/icon/playButton.png"
    hoveredIcon: "qrc:/icon/playButton_hover.png"
}
