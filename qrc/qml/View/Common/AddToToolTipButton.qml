import QtQuick 2.12
import "../../Component"

ToolTipButton {
    anchors.verticalCenter: parent.verticalCenter
    tipText: qsTr("添加到")
    normalIcon: "qrc:/icon/addTo.png"
    hoveredIcon: "qrc:/icon/addTo_hover.png"
}
