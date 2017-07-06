import QtQuick 2.2
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.4

TextArea{
    id: textArea
    style: TextAreaStyle {
        textColor: textAreaTextColor
        selectionColor: "steelblue"
        selectedTextColor: "#eee"
        backgroundColor: textAreaBackgrondColor
    }
    anchors.top: myToolBar.bottom

    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0.05 * parent.height
    anchors.left: parent.left
    anchors.right: parent.right
    font.family: "monoco"
    text:"if((5>3)&&(a<b)||!(6)){\n    p = (3+5*2+6*(3+7)*2+3*3);\n}else{\n    p = c+1;\n    while(5<3){\n        p = 3+3;\n    }\n}"
    // textFormat: Qt.RichText
    Component.onCompleted: forceActiveFocus()
    NumberAnimation on anchors.bottomMargin{
        id: outputFadeIn
        duration: 300; running: false
        easing.type: Easing.InOutQuad
        from: 0.05 * mainWindow.height; to: 0.4 * mainWindow.height
    }
    NumberAnimation on anchors.bottomMargin{
        id: outputFadeOut
        duration: 300; running: false
        easing.type: Easing.InOutQuad
        from: 0.4 * mainWindow.height; to: 0.05 * mainWindow.height
    }
    function outputFadeInStart(){
        outputFadeIn.restart()
    }
    function outputFadeOutStart(){
        outputFadeOut.restart()
    }
}
