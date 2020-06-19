import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../Common"

ListView {
    id: songListView

    property real col1Width: width / 7 * 4
    property real col2Width: width / 7
    property real col3Width: width / 7 * 2/* - 15*/
    property bool isShiftPressed: false
    property bool isCtrlPressed: false
    property var selectedItems: []
    property int songSheetId: -1
    property var curMusic: mainWindow.curMusic
    property var filterText: ""
    
    signal signal_playMusic(int index)

    function setCurrentIndex(index){
        songListView.selectedItems = [];
        songListView.currentIndex = index;
    }
    function updateIndex(){
        if(!curMusic)
            return;
        $.post("songlist.getIndex", {
            "music": curMusic
        }).syncThen(function(result) {
            setCurrentIndex(result);
        });
    }
    function playIndex(index){
        songListView.setCurrentIndex(index);
        $.get("songlist.addToPlaylist?songSheetId=" + songListView.songSheetId).syncThen(function() {
            signal_playMusic(songListView.currentIndex);
        });
    }
    function addToSongSheet(songSheetId){
        $.post("songlist.addToSongSheet", {
            "songSheetId": songSheetId,
            "indexs": selectedItems
        });
    }

    function setSongSheetId(id){
        songSheetId = id;
        if(songSheetId < 0)
            return;
        selectedItems = [];
        $.get("songlist.reloadMusic?songSheetId=" + songSheetId);
        updateIndex();
    }

    onCurMusicChanged: {
        updateIndex();
    }

    objectName: "SongListView"
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
        visible: songName.indexOf(songListView.filterText) !== -1 ? true : false
        width: parent.width
        height: visible ? 29 : 0
        hoverEnabled: true
        background: Rectangle {
            color: parent.hovered ?  "#1c993e" : (songListView.currentIndex === index || songListView.selectedItems.indexOf(index) > -1) ? "#22af4b" : "#00000000"
        }
        ListViewDelegateMouseArea {
            listView: songListView
            popupMenu: menu
            onDoubleClicked: {
                if(mouse.button === Qt.RightButton){
                    return;
                }

                songListView.playIndex(index);
            }
        }

        Row {
            anchors.fill: parent

            MainControl {
                listView: songListView
                width: songListView.col1Width
                text: songName
            }

            InfoControl {
                listView: songListView
                width: songListView.col2Width
                text: artist
            }

            InfoControl {
                listView: songListView
                width: songListView.col3Width
                text: album
            }
        }
    }

    Menu {
        id: menu
        Action {
            text: "remove"
            onTriggered: {
                $.post("songlist.removeFromSongSheet", {
                    "songSheetId": songListView.songSheetId,
                    "indexs": songListView.selectedItems
                });
                songListView.selectedItems = [];
                songListView.updateIndex();
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

    Component.onCompleted: {
        $.get("songlist.getModel").syncThen(function(result) {
            songListView.model = result;
        });
    }
}
