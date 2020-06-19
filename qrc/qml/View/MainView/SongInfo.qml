import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../Component"

Item {

    property string songSheet: ""
    property int songNum: 0

    signal signal_filterTextChanged(string text)
    signal signal_lastPageClicked()
    signal signal_nextPageClicked()

    function clear(){
        searchInput.text = "";
    }

    function entryNetSearch(){
        lastPageBtn.visible = true;
        nextPageBtn.visible = true;
        searchInput.visible = false;
    }

    function cancelNetSearch(){
        lastPageBtn.visible = false;
        nextPageBtn.visible = false;
        searchInput.visible = true;
    }

    height: 25
    LabelButton {
        id: lastPageBtn
        width: 30
        height: 25
        visible: false
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("back")
        onClicked: signal_lastPageClicked();
    }

    LabelButton {
        id: nextPageBtn
        width: 30
        height: 25
        visible: false
        text: qsTr("next")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: lastPageBtn.right
        anchors.leftMargin: 6
        onClicked: signal_nextPageClicked();
    }

    Label {
        id: curSongListLabel
        color: "#ffffff"
        text: songSheet
        anchors.horizontalCenterOffset: -50
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Label {
        id: songNumLabel
        y: 9
        color: "#ffffff"
        text: songNum
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: curSongListLabel.right
        anchors.leftMargin: 10
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15
    }

    TextField {
        id: searchInput
        y: 14
        width: 210
        height: 25
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        placeholderText: "搜索音乐、歌手..."
        selectByMouse: true
        background: Rectangle {
            color: "#c7c7c7"
            radius: 10
        }
        font.pixelSize: 14
        anchors.leftMargin: 10
        onTextChanged: {
            signal_filterTextChanged(text);
        }
    }
}
