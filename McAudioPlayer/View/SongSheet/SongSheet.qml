import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../Component"

Item {
    id: songSheetItem
    implicitWidth: 123
    implicitHeight: childrenRect.height

    signal signal_currentChanged(string songSheet)

    Button {
        id: localSongBtn
        width: 25
        height: 25
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        background: Image {
            source: "qrc:/icon/localSong.png"
        }
    }

    ListView {
        id: songSheetView
        anchors.top: localSongBtn.bottom
        anchors.topMargin: 25
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        model: jsonListModel.model

        delegate: Button {
            text: songSheet
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 0
            font.pixelSize: 16
            contentItem: Label {
                text: parent.text
                font: parent.font
                color: (parent.hovered || songSheetView.currentIndex == index) ? "#ffffff" : "#969696"
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: songSheetView.currentIndex == index ? "#88968c" : "#00000000"
            }
            onClicked: {
                songSheetView.currentIndex = index;
            }
        }

        section.property: "title"
        section.criteria: ViewSection.FullString
        section.delegate: Text {
            height: 50
            color: "#828282"
            text: section
            verticalAlignment: Text.AlignBottom
            anchors.left: parent.left
            anchors.leftMargin: 0
            font.pixelSize: 15
        }

        ScrollBar.vertical: ScrollBar {
            hoverEnabled: true
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            policy: ScrollBar.AsNeeded
        }

        onCurrentIndexChanged: {
            songSheetItem.signal_currentChanged(model.get(currentIndex).id);
        }
    }

    JSONListModel {
        id: jsonListModel
        sort: {"title": ["我的音乐", "我创建的歌单"]}
    }
    Component.onCompleted: {
        var response = JSON.parse(controllerContainer.invoke("songSheetController.getSongSheets"));
        if(!response.success)
            return;
        jsonListModel.jsonObject = response.payload;
    }
}
