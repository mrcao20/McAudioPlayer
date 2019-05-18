import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "./SongListView"

Item {
    ColumnLayout {
        anchors.fill: parent
        spacing: 6
        NetworkSearch{
            Layout.preferredHeight: 25
            Layout.fillWidth: true
        }
        SongInfo{
            Layout.preferredHeight: 25
            Layout.fillWidth: true
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Loader {
                id: songListView
                anchors.fill: parent
                focus: true
                sourceComponent: SongListView{}
            }
        }
    }

    function updateSongList(songSheet){
        songListView.item.songSheetId = songSheet;
    }
}
