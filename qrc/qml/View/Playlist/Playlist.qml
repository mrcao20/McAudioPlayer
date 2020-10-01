import QtQuick 2.12
import QtQuick.Controls 2.5
import "../Common"
import "../MediaPlayer"

Rectangle {
    id: rect
    property real showX: 0
    property real hideX: 0
    property int musicNum: playlistView.count
    property var curMusic: null
    property int currentIndex: -1

    x: hideX
    color: "#6b1500"

    onXChanged: {
        if(x >= hideX)
            visible = false;
        else
            visible = true;
    }

    PropertyAnimation {
        id: xAnimation
        target: rect
        property: "x"
        duration: 200
    }

    function visibleChanged(){
        if(xAnimation.running)
            return;
        if(visible)
            xAnimation.to = hideX;
        else
            xAnimation.to = showX;
        xAnimation.running = true;
    }

    function setCurrentIndex(index){
        playlistView.selectedItems = [];
        playlistView.currentIndex = index;
    }

    function playIndex(index){
        setCurrentIndex(index);
        //! 不需要使用syncThen，因为没有使用JSEngine的任何东西，而curMusic对其他item来说都是属性
        //! 绑定的形式的被动更新，不存在资源抢占的情况
        $.get("playlist.getMusic?index=" + playlistView.currentIndex).syncThen(function(result) {
            rect.curMusic = result;
        });
    }

    function getRandomNum(min, max){
        var range = max - min;
        var rand = Math.random();
        return (min + Math.round(rand * range));
    }

    function getRandomIndex(){
        if(playlistView.count === 0)
            return -1;
        var index = getRandomNum(0, playlistView.count - 1);
        while(playlistView.count > 1 && index === playlistView.currentIndex)
            index = getRandomNum(0, playlistView.count - 1);
        return index;
    }

    function playLast(){
        var index = -1;
        switch(mediaPlayer.playMode){
        case MediaPlayer.PlayMode.Shuffle:
            index = getRandomIndex();
            break;
        case MediaPlayer.PlayMode.Repeat:
            index = playlistView.currentIndex > 0 ? playlistView.currentIndex - 1 : playlistView.count - 1;
            break;
        case MediaPlayer.PlayMode.Single:
            index = playlistView.currentIndex
            break;
        }
        playIndex(index);
    }

    function playNext(){
        var index = -1;
        switch(mediaPlayer.playMode){
        case MediaPlayer.PlayMode.Shuffle:
            index = getRandomIndex();
            break;
        case MediaPlayer.PlayMode.Repeat:
            index = playlistView.currentIndex < playlistView.count - 1 ? playlistView.currentIndex + 1 : 0;
            break;
        case MediaPlayer.PlayMode.Single:
            index = playlistView.currentIndex
            break;
        }
        playIndex(index);
    }

    ListView {
        id: playlistView

        property bool isShiftPressed: false
        property bool isCtrlPressed: false
        property var selectedItems: []

        anchors.fill: parent
        clip: true
        headerPositioning: ListView.OverlayHeader

        header: HeaderItem{
            songNum: playlistView.count
        }

        Keys.onPressed: {
            if(event.key === Qt.Key_Up || event.key === Qt.Key_Down)
                playlistView.selectedItems = [];
            playlistView.isShiftPressed = event.key === Qt.Key_Shift;
            playlistView.isCtrlPressed = event.key === Qt.Key_Control;
        }
        Keys.onReleased: {
            playlistView.isShiftPressed = !event.key === Qt.Key_Shift;
            playlistView.isCtrlPressed = !event.key === Qt.Key_Control;
        }

        delegate: Control {
            width: rect.width
            height: 40
            hoverEnabled: true
            background: Rectangle {
                color: parent.hovered ?  "#1c993e" : (playlistView.currentIndex === index || playlistView.selectedItems.indexOf(index) > -1) ? "#22af4b" : "#00000000"
            }
            ListViewDelegateMouseArea{
                listView: playlistView
                onDoubleClicked: {
                    if(mouse.button === Qt.RightButton){
                        return;
                    }

                    playIndex(index);
                }
            }
            DelegateItem{}
        }

        ScrollBar.vertical: ScrollBar {
            hoverEnabled: true
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            policy: ScrollBar.AsNeeded
        }

        onCurrentIndexChanged: {
            rect.currentIndex = playlistView.currentIndex;
        }

        Component.onCompleted: {
            $.get("playlist.getModel").syncThen(function(result) {
                playlistView.model = result;
                $.get("playlist.loadPlaylist").syncThen(function(result) {
                    if(rect.currentIndex !== -1)
                        playlistView.currentIndex = rect.currentIndex;
                });
            });
        }
    }
}
