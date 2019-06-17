import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.1 as LabsPlatform
import QtQuick.Controls 2.5 as Controls
import Qt.labs.settings 1.0
import McControllerContainer 1.0
import McModelContainer 1.0
import "./View/MediaPlayer"
import "./View/SongSheet"
import "./View/MainView"
import "./View/SongControl"
import "./View/Playlist"
import "./Component"

Window {
    id: main
    visible: true
    width: 1000
    height: 700
    minimumWidth: 600
    minimumHeight: 400
    color: "#6b1500"
    title: qsTr("McAudioPlayer")
    objectName: "mainWindow"

    property var curMusic: playlist.curMusic

    function showWindow(){
        main.show();
        main.raise();
        main.requestActivate();
    }

    function addToPlaylist(index, musics, songSheetId){
        playlist.addMusics(index, musics, songSheetId);
    }

    onCurMusicChanged: {
        if(!curMusic)
            return;
        mediaPlayer.stop();
        mediaPlayer.source = curMusic.songUrl;
    }

    onClosing: {
        close.accepted = false
        hide();
    }

    Settings {
        category: "McAudioPlayer"
        fileName: "./init.ini"
        property alias songSheetIndex: songSheetItem.currentIndex
        property alias musicIndex: playlist.currentIndex
    }

    McControllerContainer {
        id: controllerContainer
    }

    McModelContainer {
        id: modelContainer
    }

    MediaPlayer {
        id: mediaPlayer
        onSignal_positionChanged: {
            if(position >= duration)
                playlist.playNext();
        }
    }

    GridLayout {
        anchors.rightMargin: 9
        anchors.leftMargin: 9
        anchors.bottomMargin: 9
        anchors.topMargin: 9
        columnSpacing: 0
        rowSpacing: 0
        anchors.fill: parent
        columns: 2
        rows: 2
        SongSheet {
            id: songSheetItem
            Layout.preferredWidth: 123
            Layout.fillHeight: true
            onSongSheetsChanged: {
                while(addToMenu.count > 0)
                    addToMenu.removeAction(addToMenu.actionAt(0));
                if(songSheets.length === 0)
                    return;
                var component = Qt.createComponent("qrc:/Component/AddToAction.qml");
                if (component.status === Component.Ready){
                    for(var songSheet of songSheetItem.songSheets){
                        var obj = component.createObject(addToMenu, {"songSheet":songSheet});
                        obj.clicked.connect(mainView.addToSongSheet);
                        addToMenu.addAction(obj);
                    }
                }
            }
        }

        MainView {
            id: mainView
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        SongControl {
            id: songControl
            Layout.columnSpan: 2
            Layout.preferredHeight: 104
            Layout.fillWidth: true
        }
    }
    Playlist {
        id: playlist
        visible: false
        showX: parent.width - width
        hideX: parent.width
        y: 0
        height: parent.height - songControl.height
        width: 250
    }

    Controls.Menu {
        id: addToMenu
        function disable(songSheetIds){
            for(var i = 0; i < count; ++i){
                var action = actionAt(i);
                action.enabled = true;
                if(songSheetIds.indexOf(action.songSheet.id) !== -1)
                    action.enabled = false;
            }
        }
    }

    LabsPlatform.SystemTrayIcon {
        id: trayIcon

        visible: true
        iconSource: "qrc:/icon/AudioPlayer.png"
        tooltip: "McAudioPlayer"
        onActivated: {
            if(reason === LabsPlatform.SystemTrayIcon.DoubleClick){
                if(main.visible)
                    main.hide();
                else
                    showWindow();
            }else if(reason === LabsPlatform.SystemTrayIcon.Context){
                menu.open(showMenuItem);
            }
        }

        menu: LabsPlatform.Menu {
            LabsPlatform.MenuItem {
                id: showMenuItem
                text: qsTr("Show")
                onTriggered: showWindow();
            }

            LabsPlatform.MenuSeparator {
            }

            LabsPlatform.MenuItem {
                text: qsTr("Quit");
                onTriggered: {
                    mediaPlayer.stop();
                    trayIcon.visible = false;
                    trayIcon.menu.visible = false;
                    main.hide();
                    Qt.quit();
                }
            }
        }
    }

    Component.onCompleted: {
        songSheetItem.signal_currentChanged.connect(mainView.updateSongList);
        //songSheetItem.signal_localMusicAdded.connect(mainView.addLocalMusics);
        songControl.signal_playLastMusic.connect(playlist.playLast);
        songControl.signal_playNextMusic.connect(playlist.playNext);
    }
}
