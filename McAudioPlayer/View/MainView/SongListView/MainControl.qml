import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../../Component"
import "../../Common"

Control {
    property string text: ""
    property var listView: null
    hoverEnabled: true
    HoverableText {
        anchors.right: songControl.left
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        text: parent.text
        color: hovered ? "#1827ff" : listView.currentIndex === index ? "#ffffff" : "#b5b5b5"
    }

    Rectangle {
        id: songControl
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        color: "#00000000"
        width: 125
        visible: (parent.hovered || listView.currentIndex === index) ? true : false
        PlayToolTipButton {
            id: playBtn
            anchors.left: parent.left
            anchors.leftMargin: 0
            onSignal_clicked: {
                listView.playIndex(index);
            }
        }
        AddToToolTipButton {
            id: addToBtn
            anchors.left: playBtn.right
            anchors.leftMargin: 5
            onSignal_clicked: {
                if(listView.selectedItems.indexOf(index) === -1)
                    listView.selectedItems = [index];
                listView.currentIndex = index
                addToMenu.disable([listView.songSheetId]);
                var global = mapToGlobal(mouse.x, mouse.y);
                addToMenu.popup(main, global.x, global.y);
            }
        }
        ToolTipButton {
            id: downloadBtn
            anchors.left: addToBtn.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            tipText: qsTr("下载")
            normalIcon: "qrc:/icon/download.png"
            hoveredIcon: "qrc:/icon/download_hover.png"
        }
        MoreToolTipButton {
            anchors.left: downloadBtn.right
            anchors.leftMargin: 5
        }
    }
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    anchors.top: parent.top
    anchors.topMargin: 0
}
