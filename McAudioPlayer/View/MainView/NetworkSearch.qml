import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../Component"

Item {
    height: 25
    Button {
        id: netEntrySearch
        width: 16
        height: 16
        anchors.left: parent.left
        anchors.leftMargin: 6
        anchors.verticalCenter: parent.verticalCenter
        background: Image {
            id: netSearchBtnImage
            anchors.fill: parent
            source: parent.hovered ? "qrc:/icon/search_hover.png" : "qrc:/icon/search.png"
        }
        onClicked: {
            entrySearch();
        }
    }

    LabelButton {
        id: netSearchCancelBtn
        y: 8
        height: 25
        text: qsTr("返回")
        visible: false
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        onClicked: {
            cancelSearch();
        }
    }

    ComboBox {
        id: musicSourceCombo
        y: 0
        width: 96
        height: 25
        visible: false
        font.pixelSize: 12
        currentIndex: 0
        anchors.left: netSearchCancelBtn.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        background: Rectangle {
            radius: 10
            color: "#c7c7c7"
        }
        model: ["ymusic", "qqmusic"]
    }

    TextField {
        id: netSearchInput
        y: 14
        width: 219
        height: 25
        visible: false
        font.pixelSize: 14
        anchors.left: musicSourceCombo.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        placeholderText: "搜索音乐、歌手..."
        background: Rectangle {
            radius: 10
            color: "#c7c7c7"
        }
    }

    LabelButton {
        id: netSearchBtn
        y: 8
        height: 25
        text: qsTr("搜索")
        anchors.left: netSearchInput.right
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        visible: false
        onClicked: {
            console.log(qsTr("搜索"));
        }
    }

    function entrySearch(){
        netEntrySearch.visible = false;
        netSearchCancelBtn.visible = true;
        netSearchInput.visible = true;
        musicSourceCombo.visible = true;
        netSearchBtn.visible = true;
    }

    function cancelSearch(){
        netEntrySearch.visible = true;
        netSearchCancelBtn.visible = false;
        netSearchInput.visible = false;
        musicSourceCombo.visible = false;
        netSearchBtn.visible = false;
    }
}
