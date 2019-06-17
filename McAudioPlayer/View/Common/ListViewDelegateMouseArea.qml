import QtQuick 2.12

MouseArea {
    property var listView: null
    property var popupMenu: null
    anchors.fill: parent
    acceptedButtons: Qt.LeftButton | Qt.RightButton // 激活右键（别落下这个）
    onClicked: {
        if(listView == null)
            return;
        listView.forceActiveFocus();
        if(mouse.button === Qt.RightButton){
            if(listView.selectedItems.indexOf(index) === -1)
                listView.selectedItems = [];
            setCurrentIndex();
            if(popupMenu){
                var global = mapToGlobal(mouse.x, mouse.y);
                popupMenu.popup(main, global);
            }
            return;
        }

        if(!listView.isCtrlPressed && !listView.isShiftPressed){
            listView.selectedItems = [];
        }else if(listView.isShiftPressed){
            var minIndex = listView.currentIndex < index ? listView.currentIndex : index;
            var maxIndex = listView.currentIndex > index ? listView.currentIndex : index;
            for(var i = minIndex + 1; i < maxIndex; ++i)
                if(listView.selectedItems.indexOf(i) === -1)
                    listView.selectedItems.push(i);
        }
        setCurrentIndex();
    }
    function setCurrentIndex(){
        listView.currentIndex = index;
        if(listView.selectedItems.indexOf(index) === -1)
            listView.selectedItems.push(index);
    }
}
