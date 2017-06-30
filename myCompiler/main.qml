import QtQuick 2.2
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1
import QtQuick.Window 2.2

import Transfer 1.0
import File 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 300
    title: qsTr("Micro C compilers")
    property string textAreaBackgrondColor: "#E0E0E0"
    property string textAreaTextColor: "#333"
    property string outputBackgroundColor: "#272822"
    property string outputTextColor: "#FFFFFF"
    FontLoader{id: uiFont; source: ""}

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
            trans.doParser()
            tokenView.visible = false
            parserView.visible = true
            separator.text = "语法树"
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
            trans.doTokens()
            parserView.visible = false
            tokenView.visible = true
            separator.text = "记号流"
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
            ToolButton{action: fileSaveAction}
            ToolButton{action: grammarParserAction}
            ToolButton{action: translateAction}
        }
    }


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
        text: "记号流"
    }

    TableView{
        id: tokenView
        TableViewColumn {
            role: "line"
            title: "Line"
            width: 100
        }
        TableViewColumn {
            role: "simbol"
            title: "Simbol"
            width: 200
        }
        model: tokenModel
        anchors.top: separator.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
    ListModel {
        id: tokenModel
    }

    TreeView {
        id: parserView
        model: parserModel
        onSelectedItemChanged: console.log(item.text)
        anchors.top: separator.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
    ListModel {
        id: parserModel
    }

    property var s: []
    property var codeJSON
    property var parserJSON
    Transfer{
        id: trans
        onDoTokens:{
            var data = tokensToJSON(textArea.text)
            codeJSON = JSON.parse(data)
            for(var key in codeJSON){
                var exe = "tokenModel.append([{\"line\":\"" + key
                exe = exe + "\", \"simbol\":\"" + codeJSON[key]
                exe = exe + "\"}])"
                eval(exe)
            }
        }
        onDoParser: {
            var data = parserToJSON(textArea.text)
            parserJSON = JSON.parse(data)
            var s = ""

            myRecursion(parserJSON)
            parseStr = "parserModel.append([" + parseStr + "])"
            eval(parseStr)
        }
    }
    property string parseStr: ""
    function myRecursion(json){
        for(var key in json){
            for(var realKey in json[key]){
                if(typeof(json[key][realKey]) == "string"){
                    parseStr = parseStr + "{title:\"" + json[key][realKey] + "\"},"
                    //console.log("{title: ", (json[key][realKey]), "}")
                }else{
                    for(var kk in json[key][realKey]){
                        parseStr = parseStr + "{title: " + "\"" + kk + "层" + "\",items:["
                        //console.log("{title: ", kk, ", items: [")
                    }
                    myRecursion(json[key][realKey], s)
                    parseStr = parseStr.substring(0, parseStr.length - 1) + "]},"
                }
            }
        }
    }

}
