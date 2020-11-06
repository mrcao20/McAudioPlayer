import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    y: 487
    height: 104
    signal signal_playLastMusic();
    signal signal_playNextMusic();
    CtrlBtnGroup {
        id: ctrlBtnGroup
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 50
    }

    Middle {
        id: middle
        anchors.right: otherBtnGroup.left
        anchors.rightMargin: 20
        anchors.left: ctrlBtnGroup.right
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    OtherBtnGroup {
        id: otherBtnGroup
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.right: parent.right
        anchors.rightMargin: 0
    }
}
