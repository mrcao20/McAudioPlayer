import QtQuick 2.12
import QtQuick.Controls 2.5

Slider {
    id: progressBar
    anchors.verticalCenter: parent.verticalCenter
    anchors.left: parent.left
    anchors.leftMargin: 0
    anchors.right: parent.right
    anchors.rightMargin: 0
    height: handle.height
    value: mediaPlayer.position / mediaPlayer.duration
    background: Rectangle {
        x: progressBar.leftPadding
        y: progressBar.topPadding + progressBar.availableHeight / 2 - height / 2
        implicitWidth: 200
        implicitHeight: 3
        width: progressBar.availableWidth
        height: implicitHeight
        radius: 2
        border.width: 1
        color: "#bcbcbc"

        Rectangle {
            id: subPage     // 已经划过的从地方
            width: progressBar.visualPosition * parent.width
            height: parent.height
            color: "#439cf3"
            radius: 2
        }
        Image {
            width: (1 - progressBar.visualPosition) * parent.width
            height: parent.height
            anchors.left: subPage.right
            anchors.leftMargin: 0
            source: "qrc:/icon/Slider_bar.png"
        }
    }

    handle: Rectangle {
        x: progressBar.leftPadding + progressBar.visualPosition * (progressBar.availableWidth - width)
        y: progressBar.topPadding + progressBar.availableHeight / 2 - height / 2
        implicitWidth: 15
        implicitHeight: 15
        color: "#00000000"
        Image {
            anchors.fill: parent
            source: "qrc:/icon/Slider_handle.png"
        }
    }

    onMoved: {
        var targetPos = value * mediaPlayer.duration;
        mediaPlayer.seek(targetPos);
    }
}
