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
    id: mainWindow
    visible: true
    width: 1080
    height: 720
    minimumWidth: 400
    minimumHeight: 300
    title: qsTr("Micro C compilers")
    property string language: "en"
    property var languageFile
    property string textAreaBackgrondColor: "#E0E0E0"
    property string textAreaTextColor: "#333"
    property string outputBackgroundColor: "#272822"
    property string outputTextColor: "#FFFFFF"
    FontLoader{id: uiFont; source: "qrc:/font/STKaiTi.ttf"}
    FontLoader{id: textFont; source: "qrc:/font/liberationmono.ttf"}

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
        text: languageFile[0]
        onTriggered: {
            fileDialog.openFlag = true
            fileDialog.open()
        }
    }

    Action {
        id: fileSaveAction
        //iconSource: "qrc:/images/"
        iconName: "Save"
        text: languageFile[2]
        onTriggered: {
            fileDialog.openFlag = false
//            fileDialog.open()
//            console.log(File.exist(":/lang/ch.txt"))
//            console.log(File.read(":/lang/ch.txt"))
        }
    }

    Action {
        id: grammarParserAction
        //iconSource: "qrc:/images/"
        iconName: "Parse"
        text: languageFile[3]
        onTriggered: {
            textArea.outputFadeInStart()
            trans.doParser()
            tokenView.visible = false
            analyzerView.visible = false
            parserView.visible = true
            separator.text = languageFile[20]
        }

    }

    Action {
        id: translateAction
        //iconSource: "qrc:/images/trans.png"
        iconName: "Trans"
        text: languageFile[4]
        onTriggered: {
            textArea.outputFadeInStart()
            trans.doAnalyser()
            tokenView.visible = false
            analyzerView.visible = true
            parserView.visible = false
            separator.text = languageFile[21]
        }
    }


    Action {
        id: readTokensAction
        iconName: "Token"
        text: languageFile[1]
        onTriggered: {
            textArea.outputFadeInStart()
            trans.doTokens()
            parserView.visible = false
            analyzerView.visible = false
            tokenView.visible = true
            separator.text = languageFile[19]
        }
    }

    ToolBar {
        id: myToolBar
        width: parent.width
        RowLayout{
            anchors.fill: parent
            spacing: 6
            ToolButton{action: fileOpenAction;   Layout.minimumWidth: 216;}
            ToolButton{action: readTokensAction; Layout.minimumWidth: 216}
            ToolButton{action: fileSaveAction;   Layout.minimumWidth: 216}
            ToolButton{action: grammarParserAction; Layout.minimumWidth: 216}
            ToolButton{action: translateAction;  Layout.minimumWidth: 216}
        }
    }

    menuBar: MenuBar{
        id: menu
        Menu{
            id: fileMenu
            title: "&" + languageFile[5]
            MenuItem {action: fileOpenAction}
            MenuItem {action: fileSaveAction}
            MenuItem {id: quitAction; text: "Quit"; onTriggered: Qt.quit()}
        }
        Menu{
            id: doMenu
            title: "&" + languageFile[8]
            MenuItem {action: readTokensAction}
            MenuItem {action: grammarParserAction}
            MenuItem {action: translateAction}
        }
        Menu{
            id: appearanceMenu
            title: "&" + languageFile[12]
            MenuItem {text: languageFile[13]; onTriggered: switchSytle("default")}
            MenuItem {text: languageFile[14]; onTriggered: switchSytle("Monokai")}
            MenuItem {text: languageFile[15];    onTriggered: switchSytle("Lazy")}
        }
        Menu{
            id: languageMenu
            title: "&" + languageFile[16]
            MenuItem {id: englishMenu; text: languageFile[17]; onTriggered: switchLanguage("English")}
            MenuItem {id: chineseMenu; text: languageFile[18]; onTriggered: switchLanguage("Chinese")}
        }
        Menu{
            id: exampleMenu
            title: "&" + languageFile[22]
            MenuItem {id: example1; text: languageFile[23]; onTriggered: exampleMenu.showExample(1)}
            MenuItem {id: example2; text: languageFile[24]; onTriggered: exampleMenu.showExample(2)}
            MenuItem {id: example3; text: languageFile[25]; onTriggered: exampleMenu.showExample(3)}
            MenuItem {id: example4; text: languageFile[26]; onTriggered: exampleMenu.showExample(4)}
            MenuItem {id: example5; text: languageFile[27]; onTriggered: exampleMenu.showExample(5)}
            MenuItem {id: example6; text: languageFile[28]; onTriggered: exampleMenu.showExample(6)}
            function showExample(i){
                var source = ""
                if(i === 1){
                    source = File.read(":/examples/100sum.txt")
                }else if(i === 2){
                    source = File.read(":/examples/10mul.txt")
                }else if(i === 3){
                    source = File.read(":/examples/single-if.txt")
                }else if(i === 4){
                    source = File.read(":/examples/single-while.txt")
                }else if(i === 5){
                    source = File.read(":/examples/many-if.txt")
                }else if(i === 6){
                    source = File.read(":/examples/many-while.txt")
                }
                textArea.text = source
            }
        }
    }


    MyTextArea{
        id: textArea
    }

    Label{
        id: separator
        height: 0.05 * parent.height
        anchors.top: textArea.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        text: languageFile[19]
        MouseArea{
            anchors.fill: parent
            onClicked: {
                textArea.outputFadeOutStart()
            }
        }
    }


//--------------------TOKENS-----------------------
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
//--------------------ANALYZER---------------------
    TableView{
        id: analyzerView
        TableViewColumn {
            role: "simbol"
            title: "simbol"
            width: 100
        }
        TableViewColumn {
            role: "val"
            title: "val"
            width: 200
        }
        model: analyzerModel
        anchors.top: separator.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
    ListModel {
        id: analyzerModel
    }
//-------------------PARSER------------------------

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
    property var analyJSON
    Transfer{
        id: trans
        onDoTokens:{
            var data = tokensToJSON(textArea.text)
            codeJSON = JSON.parse(data)
            tokenModel.clear()
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
            parserModel.clear()
            parseStr = ""
            myRecursion(parserJSON)
            parseStr = "parserModel.append([" + parseStr + "])"
            console.log(parseStr)
            eval(parseStr)
        }
        onDoAnalyser:{
            var data = analyzerToJSON(textArea.text)
            analyJSON = JSON.parse(data)
            analyzerModel.clear()
            console.log(data)
            for(var key in analyJSON){
                for(var sim in analyJSON[key]){
                    var exe = "analyzerModel.append([{\"simbol\":\"" + sim
                    exe = exe + "\", \"val\":\"" + analyJSON[key][sim]
                    exe = exe + "\"}])"
                    console.log(exe)
                    eval(exe)
                }
            }
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


    // Appearance
//    property string textAreaBackgrondColor: "#E0E0E0"
//    property string textAreaTextColor: "#333"

    function switchSytle(style){
        if(style === "default"){
            textAreaBackgrondColor = "#E0E0E0"
            textAreaTextColor = "#333"
            textFont.source = "qrc:/font/liberationmono.ttf"
        }else if(style === "Monokai"){
            textAreaBackgrondColor = "#272822"
            textAreaTextColor = "#f8f8f2"
            textFont.source = "qrc:/font/Marion Italic.ttf"
        }else if(style === "Lazy"){
            textAreaBackgrondColor = "#ffffff"
            textAreaTextColor = "#000000"
            textFont.source = "qrc:/font/gulliver.otf"
        }
    }

    function switchLanguage(lang){
        if(lang === "English"){
            language = "en"
        }else if(lang === "Chinese"){
            language = "ch"
        }
    }

    Component.onCompleted: {
        if(File.exist(":/lang/en.txt")){
            languageFile = File.read(":/lang/en.txt").split("\n")
            for(var item in languageFile){
                console.log(languageFile[item])

            }
        }
    }
    onLanguageChanged: {
        if(File.exist(":/lang/"+language+".txt")){
            languageFile = File.read(":/lang/"+language+".txt").split("\n")
            for(var item in languageFile){
                console.log(languageFile[item])

            }
        }
    }
}
