import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1 as LabsPlatform
import "../../Component"

Item {
    id: songSheetItem
    implicitWidth: 123
    implicitHeight: childrenRect.height

    property var songSheets: []
    property int currentIndex: -1

    signal signal_currentChanged(int songSheetId, string songSheet)
    
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
        onClicked: {
            localFileDialog.open();
        }
    }

    LabsPlatform.FileDialog {
        id: localFileDialog
        title: qsTr("选择要添加的音乐")
        nameFilters: ["Music files (*.mp3 *.ape *.flac)", "All files (*)"]
//        selectMultiple: true
        onAccepted: {
            /*!
              files的类型是QT的list，这里如果直接用files的话，会被转换为对象，key为数组下标的字符串
              value为url类型，C++端需要用QMap<QString, QUrl>接收。所以需要先转换为js的数组，再传递进去，
              C++端可以直接用QList<QUrl>接收
             */
            var data = [];
            for(var i = 0; i < files.length; ++i) {
                data.push(files[i]);
            }

            $.post("songSheet.addLocalMusics", {
                "index": songSheetView.currentIndex,
                "filePaths": data
            });
        }
    }

    TextField {
        id: textInput
        visible: false
        z: 2
        onEditingFinished: {
            if(!visible)
                return;

            var item = songSheetView.currentItem;
            var url = "songSheet.rename?index={0}&newText={1}".format(songSheetView.currentIndex, text);
            $.get(url).syncThen(function(isSuccess){
                if(!isSuccess)
                    text = item.text;   // 如果重命名失败，则将文本框中文本还原
                if(!isSuccess && focus)
                    return; // 如果重命名失败，但是焦点仍在，则说明仍可以继续重命名，则直接返回
    
                // 如果重命名成功，或者丢失了焦点，则取消编辑
                visible = false;
    
                item.visible = true;
                if(focus)   // 如果在取消编辑时输入框仍有焦点，则将焦点转移到delegate上，否则不执行，此处仅仅是取消输入框的焦点
                    item.forceActiveFocus();
            });
        }
    }

    function renameCurrentItem(){
        var item = songSheetView.currentItem;
        item.visible = false;
        var pos = songSheetView.mapToItem(songSheetItem, item.x, item.y);
        textInput.width = item.width
        textInput.height = item.height
        textInput.x = pos.x;
        textInput.y = pos.y;
        textInput.text = item.text;
        textInput.visible = true;
        textInput.forceActiveFocus();
    }

    Menu {
        id: songSheetMenu
        Action {
            text: qsTr("rename")
            onTriggered: {
                renameCurrentItem();
            }
        }

        MenuSeparator{
            padding: 0
            contentItem: Rectangle {
                implicitWidth: 200
                implicitHeight: 1
                color: "#1E000000"
            }
        }

        Action {
            text: qsTr("delete")
            onTriggered: {
                $.get("songSheet.deleteSongSheet?index={0}".format(songSheetView.currentIndex)).syncThen(function(){
                    if(songSheetView.currentIndex >= songSheetView.count)
                        songSheetView.currentIndex = songSheetView.count - 1;
                    songSheetView.update();
                });
            }
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
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton // 激活右键（别落下这个）
                onClicked: {
                    forceActiveFocus();
                    songSheetView.setIndex(index);
                    if(mouse.button === Qt.RightButton) {
                        var global = mapToGlobal(mouse.x, mouse.y);
                        songSheetMenu.popup(mainWindow, global);
                    }
                }
            }
        }

        section.property: "title"
        section.criteria: ViewSection.FullString
        section.delegate: Item {
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            Text {
                id: sectionText
                color: "#828282"
                text: section
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                verticalAlignment: Text.AlignBottom
                anchors.left: parent.left
                anchors.leftMargin: 0
                font.pixelSize: 15
            }
            LabelButton {
                visible: section === qsTr("我创建的歌单")
                anchors.top: sectionText.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: sectionText.right
                anchors.leftMargin: 0
                text: "+"
                font.pixelSize: 25
                onClicked: {
                    $.post("songSheet.createNewSongSheet", {
                        "title": qsTr("我创建的歌单"),
                        "newName": qsTr("新建歌单")
                    }).syncThen(function(newIndex){
                        if(newIndex < 0)    // 表示出错
                            return;
                        songSheetView.setIndex(newIndex);
                        renameCurrentItem();
                    });
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

        function update(){
            if(currentIndex < 0 || currentIndex >= songSheetItem.songSheets.length) {
                return;
            }
            var songSheet = songSheetItem.songSheets[currentIndex];
            emit: songSheetItem.signal_currentChanged(songSheet.id, songSheet.songSheet);
            songSheetItem.currentIndex = songSheetView.currentIndex;
        }
        
        function setIndex(index) {
            if(currentIndex === index) {
                return;
            }

            currentIndex = index;
            update();
        }
    
        Keys.onReleased: {
            if(event.key === Qt.Key_F2) {
                renameCurrentItem();
            }
        }
    }

    Component.onCompleted: {
        $.get("songSheet.getModel").syncThen(function(result) {
            songSheetView.model = result;
            
            var data = {
                "section": "title",
                "list": [
                    "我的音乐",
                    "我创建的歌单"
                ]
            };
            
            $.post("songSheet.loadSongSheets", data).syncThen(function(result) {
                songSheetItem.songSheets = result;
                
                if(songSheetItem.currentIndex !== -1) {
                    songSheetView.setIndex(songSheetItem.currentIndex);
                }
            });
        });
    }
}
