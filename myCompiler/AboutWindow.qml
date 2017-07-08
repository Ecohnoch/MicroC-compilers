import QtQuick 2.7
import QtQuick.Controls 1.3
//import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Window {
    SystemPalette{
        id: systemPalette
    }

    title: "About The Author"
    width: 320; height: 240
    minimumWidth: 320; minimumHeight: 240
    modality: Qt.ApplicationModal
    color: systemPalette.window
    ScrollView{
        anchors.fill: parent
    }
    TextEdit{
        id: textEdit
        anchors.fill: parent
        anchors.margins: 10
        renderType: Text.NativeRendering
        textFormat: TextEdit.RichText
        wrapMode: TextEdit.Wrap
        readOnly: true
        selectByMouse: false
        font.family: textFont.name
        onLinkActivated: Qt.openUrlExternally(link)
        text: languageFile[30]
        MouseArea{
            anchors.fill: parent
            cursorShape: textEdit.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
            acceptedButtons: Qt.NoButton
        }
    }



}
