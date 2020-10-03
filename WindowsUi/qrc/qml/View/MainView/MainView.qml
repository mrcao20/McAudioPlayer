import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Item {
    property int songSheetId: -1
    property string songSheet: ""
    property string searchKeyword: ""
    
    signal signal_playMusic(int index)

    function viewCountChanged(){
        songInfo.songNum = songListView.item.count;
    }

    function updateSongList(ssid, ss){
        songInfo.clear();
        songSheet = ss;
        songInfo.songSheet = songSheet;
        songSheetId = ssid;
        if(songListView.status === Loader.Ready && songListView.item.objectName !== "SongListView")
            songListView.setSource("SongListView/SongListView.qml");
        else if(songListView.status === Loader.Ready && songListView.item.objectName === "SongListView")
            songListView.item.setSongSheetId(songSheetId);
    }

    function addToSongSheet(songSheet){
        songListView.item.addToSongSheet(songSheet.id);
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 6
        NetworkSearch {
            id: netSearch
            Layout.preferredHeight: 25
            Layout.fillWidth: true
        }
        SongInfo{
            id: songInfo
            Layout.preferredHeight: 25
            Layout.fillWidth: true
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Loader {
                id: songListView
                anchors.fill: parent
                asynchronous: true
                focus: true
                source: "SongListView/SongListView.qml"
                onLoaded: {
                    songListView.item.countChanged.connect(viewCountChanged);
                    if(item.objectName === "SongListView") {
                        item.setSongSheetId(songSheetId);
                    }else if(item.objectName === "NetworkSonglistView"){
                        songListView.item.search(songInfo.songSheet, searchKeyword);
                    }
                    songListView.item.signal_playMusic.connect(signal_playMusic);
                }
            }
        }
    }

    Connections {
        target: netSearch
        function onSignal_netSearch(musicSrc, keyword) {
            songInfo.songSheet = musicSrc;
            searchKeyword = keyword;
            if(songListView.status === Loader.Ready && songListView.item.objectName !== "NetworkSonglistView")
                songListView.setSource("NetworkSonglistView/NetworkSonglistView.qml")
            else if(songListView.status === Loader.Ready && songListView.item.objectName === "NetworkSonglistView")
                songListView.item.search(musicSrc, keyword);
        }

        function onSignal_entrySearch() {
            songInfo.entryNetSearch();
        }

        function onSignal_cancelSearch() {
            songInfo.cancelNetSearch();
            updateSongList(songSheetId, songSheet);
        }
    }

    Connections {
        target: songInfo
        function onSignal_filterTextChanged(text) {
            songListView.item.filterText = text;
        }

        function onSignal_lastPageClicked() {
            if(songListView.status !== Loader.Ready || songListView.item.objectName !== "NetworkSonglistView")
                return;
            songListView.item.searchLast();
        }

        function onSignal_nextPageClicked() {
            if(songListView.status !== Loader.Ready || songListView.item.objectName !== "NetworkSonglistView")
                return;
            songListView.item.searchNext();
        }
    }
}
