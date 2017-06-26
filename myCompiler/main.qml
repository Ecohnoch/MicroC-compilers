import QtQuick 2.7
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1
import QtQuick.Window 2.2

import TokenParser 1.0
import File 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 300
    title: qsTr("Micro C compilers")

    property string fileSource
    property string sourceCode: ""
    FileDialog{
        id: fileDialog
        property bool openFlag: true
        onAccepted: {
            if(openFlag){
                fileSource = fileUrl
                fileSource = fileSource.substring(7, fileSource.length)
                console.log(File.exist(fileSource), fileSource)
                if(File.exist(fileSource))
                    sourceCode = File.read(fileSource)
                else
                    console.log("*** Error when open the file!")
                console.log(sourceCode)
                textArea.text = sourceCode
            }else{
                fileSource = folder
                fileSource = fileSource.substring(7, fileSource.length)
                // to do
                // write
            }
        }
    }
    Action {
        id: fileOpenAction
        iconName: "Open"
        text: "Open"
        onTriggered: {
            fileDialog.openFlag = true
            fileDialog.open()
        }
    }

    Action {
        id: fileSaveAction
        //iconSource: "qrc:/images/"
        iconName: "Save"
        text: "Save"
        onTriggered: {
            fileDialog.openFlag = false
            fileDialog.open()
        }
    }

    Action {
        id: grammarParserAction
        //iconSource: "qrc:/images/"
        iconName: "Parse"
        text: "Parse"
        onTriggered: {
            // TODO
        }
    }

    Action {
        id: translateAction
        //iconSource: "qrc:/images/"
        iconName: "Trans"
        text: "Trans"
        onTriggered: {
            // TODO
        }
    }

    Action {
        id: generateAction
        //iconSource: "qrc:/images/"
        iconName: "generate"
        text: "generate"
        onTriggered: {
            // TODO
        }
    }

    Action {
        id: readTokensAction
        iconName: "Token"
        text: "Token"
        onTriggered: {
            token.doParse()
            output.text = ""
            var outputData = "词法分析: \n"
            outputData = outputData + "序号        " + "记号名       " + "属性值\n"
            var eachLine = ""
            for(var key in codeJSON){
                eachLine = ""
                eachLine = eachLine + key
                for(var i = 0; i < 15 - key.length; ++i)
                    eachLine = eachLine + " "
                eachLine = eachLine + codeJSON[key]["token_name"]
                for(var j = 0; j < 35 - eachLine.length; ++j)
                    eachLine = eachLine + " "


                eachLine = eachLine + codeJSON[key]["token_num"]  + "\n"
                outputData = outputData + eachLine
                console.log("Debug: ", eachLine.length)
            }
            output.text = outputData
        }
    }

    ToolBar {
        id: myToolBar
        width: parent.width
        RowLayout{
            anchors.fill: parent
            spacing: 0
            ToolButton{action: fileOpenAction}
            ToolButton{action: readTokensAction}
            ToolButton{action: fileOpenAction}
            ToolButton{action: fileOpenAction}
            ToolButton{action: fileOpenAction}
        }
    }


    property string textAreaBackgrondColor: "#E0E0E0"
    property string textAreaTextColor: "#333"
    property string outputBackgroundColor: "#272822"
    property string outputTextColor: "#FFFFFF"

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
        anchors.bottomMargin: 0.24 * parent.height
        anchors.left: parent.left
        anchors.right: parent.right
        font.family: "monoco"

        // textFormat: Qt.RichText
        Component.onCompleted: forceActiveFocus()
    }
    Label{
        id: separator
        height: 0.01 * parent.height
        anchors.top: textArea.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

    TextArea{
        id: output
        style: TextAreaStyle {
            textColor: outputTextColor
            selectionColor: "steelblue"
            selectedTextColor: "#eee"
            backgroundColor: outputBackgroundColor
        }
        anchors.top: separator.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        readOnly: true
    }

    property var s: []
    property var codeJSON
    TokenParser{
        id: token
        onDoParse:{
            getSourcecode(textArea.text);
            var data = JSON.parse(toJSON())
            codeJSON = data
        }
    }
}