import QtQuick 2.12
import QtQuick.Controls 2.5

Component {
    id: songListViewComponent
    ListView {
        id: songListView
        Component.onCompleted: {
            console.log();
            var json = "["
            for(var i = 0; i < 100; ++i){
                json += "{\"songName\":\"最美的回忆\", \"artist\":\"六哲\", \"album\": \"最美的回忆\"}";
                if(i < 99)
                    json += ",";
            }
            json += "]";
            songListView.model = JSON.parse(json);
        }

        property real col1Width: width / 7 * 4
        property real col2Width: width / 7
        property real col3Width: width / 7 * 2/* - 15*/
        property bool isShiftPressed: false
        property bool isCtrlPressed: false
        property var selectedItems: []
        property int songSheetId: -1

        onSongSheetIdChanged: {
            var response = JSON.parse(controllerContainer.invoke("musicController.getMusics?songSheetId=" + songSheetId));
            if(!response.success)
                return;
            var time = new Date().getTime();
            songListView.model = response.payload;
            console.log(new Date().getTime() - time);
        }

        clip: true
        headerPositioning: ListView.OverlayHeader

        header: Row {
            width: parent.width
            height: 29
            z: 2
            HeaderLabel {
                width: songListView.col1Width
                text: qsTr("歌名")
            }
            HeaderLabel {
                width: songListView.col2Width
                text: qsTr("歌手")
            }
            HeaderLabel {
                width: songListView.col3Width
                text: qsTr("专辑")
            }
        }

        Keys.onPressed: {
            if(event.key === Qt.Key_Up || event.key === Qt.Key_Down)
                songListView.selectedItems = [];
            songListView.isShiftPressed = event.key === Qt.Key_Shift;
            songListView.isCtrlPressed = event.key === Qt.Key_Control;
        }
        Keys.onReleased: {
            songListView.isShiftPressed = !event.key === Qt.Key_Shift;
            songListView.isCtrlPressed = !event.key === Qt.Key_Control;
        }

        delegate: Control {
            width: parent.width
            height: 29
            hoverEnabled: true
            background: Rectangle {
                color: parent.hovered ?  "#1c993e" : (songListView.currentIndex === index || songListView.selectedItems.indexOf(index) > -1) ? "#22af4b" : "#00000000"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    songListView.forceActiveFocus();
                    if(!songListView.isCtrlPressed && !songListView.isShiftPressed){
                        songListView.selectedItems = [];
                    }else if(songListView.isShiftPressed){
                        var minIndex = songListView.currentIndex < index ? songListView.currentIndex : index;
                        var maxIndex = songListView.currentIndex > index ? songListView.currentIndex : index;
                        for(var i = minIndex + 1; i < maxIndex; ++i)
                            if(songListView.selectedItems.indexOf(i) === -1)
                                songListView.selectedItems.push(i);
                    }
                    songListView.currentIndex = index;
                    if(songListView.selectedItems.indexOf(index) === -1)
                        songListView.selectedItems.push(index);
                }
            }

            Row {
                anchors.fill: parent

                MainControl {
                    width: songListView.col1Width
                    text: modelData.songName
                }

                InfoControl {
                    width: songListView.col2Width
                    //text: modelData.artist
                }

                InfoControl {
                    width: songListView.col3Width
                    //text: modelData.album
                }
            }
        }

        ScrollBar.vertical: ScrollBar {
            hoverEnabled: true
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            policy: ScrollBar.AsNeeded
        }

    }
}
