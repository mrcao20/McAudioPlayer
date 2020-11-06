import QtQuick 2.12

Rectangle {
    property int songNum: 0
    width: parent.width
    height: 60
    z: 2
    color: "#6b1500"
    Item {
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        Text {
            id: headerTopText
            font.pixelSize: 19
            font.bold: true
            color: "#ffffff"
            text: qsTr("播放列表")
        }
        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: headerTopText.bottom
            anchors.topMargin: 10
            Text {
                font.pixelSize: 15
                color: "#b5b5b5"
                text: songNum + qsTr("首歌曲")
            }
        }
    }
}
