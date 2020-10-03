import QtQuick 2.12
import "../../Component"

ToolTipButton {
    anchors.verticalCenter: parent.verticalCenter
    tipText: qsTr("更多")
    normalIcon: "qrc:/icon/more.png"
    hoveredIcon: "qrc:/icon/more_hover.png"
}
