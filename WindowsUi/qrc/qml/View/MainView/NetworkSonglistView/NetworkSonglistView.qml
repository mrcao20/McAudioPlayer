import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../Common"
import "../SongListView"

ListView {
    id: networkongListView

    property real col1Width: width / 7 * 4
    property real col2Width: width / 7
    property real col3Width: width / 7 * 2/* - 15*/
    property bool isShiftPressed: false
    property bool isCtrlPressed: false
    property var selectedItems: []
    property var curMusic: mainWindow.curMusic
    
    signal signal_playMusic(int index)

    onCurMusicChanged: {
        updateIndex();
    }

    function updateIndex(){
        if(!curMusic)
            return;
        $.post("networkMusic.getIndex", {
            "music": curMusic
        }).syncThen(function(index){
            setCurrentIndex(index);
        });
    }

    function search(musicSrc, keyword){
        $.get("networkMusic.getNetworkMusics?musicSrc={0}&keyword={1}"
              .format(musicSrc, keyword));
    }

    function setCurrentIndex(index){
        networkongListView.selectedItems = [];
        networkongListView.currentIndex = index;
        networkongListView.selectedItems.push(index);
    }
    function playIndex(index){
        networkongListView.setCurrentIndex(index);
        $.post("networkMusic.addToPlaylist", {
            "indexs": networkongListView.selectedItems,
            "songSheetId": 0
        }).syncThen(function(){
            signal_playMusic(0);
        });
    }
    function addToSongSheet(songSheetId){
        $.post("networkMusic.addToSongSheet", {
            "songSheetId": songSheetId,
            "indexs": selectedItems
        });
    }

    function searchLast(){
        $.get("networkMusic.getLastPageMusic");
    }

    function searchNext(){
        $.get("networkMusic.getNextPageMusic");
    }

    objectName: "NetworkSonglistView"
    clip: true
    headerPositioning: ListView.OverlayHeader

    header: Row {
        width: parent.width
        height: 29
        z: 2
        HeaderLabel {
            width: networkongListView.col1Width
            text: qsTr("歌名")
        }
        HeaderLabel {
            width: networkongListView.col2Width
            text: qsTr("歌手")
        }
        HeaderLabel {
            width: networkongListView.col3Width
            text: qsTr("专辑")
        }
    }

    Keys.onPressed: {
        if(event.key === Qt.Key_Up || event.key === Qt.Key_Down)
            networkongListView.selectedItems = [];
        networkongListView.isShiftPressed = event.key === Qt.Key_Shift;
        networkongListView.isCtrlPressed = event.key === Qt.Key_Control;
    }
    Keys.onReleased: {
        networkongListView.isShiftPressed = !event.key === Qt.Key_Shift;
        networkongListView.isCtrlPressed = !event.key === Qt.Key_Control;
    }

    delegate: Control {
        width: parent.width
        height: visible ? 29 : 0
        hoverEnabled: true
        background: Rectangle {
            color: parent.hovered ?  "#1c993e" : (networkongListView.currentIndex === index || networkongListView.selectedItems.indexOf(index) > -1) ? "#22af4b" : "#00000000"
        }
        ListViewDelegateMouseArea {
            listView: networkongListView
            onDoubleClicked: {
                if(mouse.button === Qt.RightButton){
                    return;
                }

                networkongListView.playIndex(index);
            }
        }

        Row {
            anchors.fill: parent

            MainControl {
                listView: networkongListView
                width: networkongListView.col1Width
                text: songName
            }

            InfoControl {
                listView: networkongListView
                width: networkongListView.col2Width
                text: artist
            }

            InfoControl {
                listView: networkongListView
                width: networkongListView.col3Width
                text: album
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
        $.get("networkMusic.getModel").syncThen(function(result){
            networkongListView.model = result;
            $.get("networkMusic.clearModel");
        });
    }
}
