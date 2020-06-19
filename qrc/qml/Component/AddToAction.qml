import QtQuick 2.12
import QtQuick.Controls 2.5

Action {
    property var songSheet: null

    text: songSheet ? songSheet.songSheet : "";
    //checkable: true

    signal clicked(var songSheet);

    onTriggered: {
        clicked(songSheet)
    }
}
