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
    property string textAreaBackgrondColor: "#E0E0E0"
    property string textAreaTextColor: "#333"
    property string fontFamily: "monoco"
    property string outputBackgroundColor: "#272822"
    property string outputTextColor: "#FFFFFF"
    // FontLoader{id: uiFont; source: "monoco"}

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
            textArea.outputFadeInStart()
            trans.doParser()
            tokenView.visible = false
            analyzerView.visible = false
            parserView.visible = true
            separator.text = "Syntax Tree"
        }

    }

    Action {
        id: translateAction
        //iconSource: "qrc:/images/"
        iconName: "Trans"
        text: "Trans"
        onTriggered: {
            textArea.outputFadeInStart()
            trans.doAnalyser()
            tokenView.visible = false
            analyzerView.visible = true
            parserView.visible = false
            separator.text = "Analyzer"
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
            textArea.outputFadeInStart()
            trans.doTokens()
            parserView.visible = false
            analyzerView.visible = false
            tokenView.visible = true
            separator.text = "Token Flow"
        }
    }

    ToolBar {
        id: myToolBar
        width: parent.width
        RowLayout{
            anchors.fill: parent
            spacing: 0
            ToolButton{action: fileOpenAction}
            ToolButton
            {action: readTokensAction}
            ToolButton{action: fileSaveAction}
            ToolButton{action: grammarParserAction}
            ToolButton{action: translateAction}
        }
    }

    menuBar: MenuBar{
        id: menu
        Menu{
            id: fileMenu
            title: "&File"
            MenuItem {action: fileOpenAction}
            MenuItem {action: fileSaveAction}
            MenuItem {id: quitAction; text: "Quit"; onTriggered: Qt.quit()}
            function __switchLanguage(language){
                if(language === "English"){
                    fileMenu.title = "&File"
                    quitAction.text = "Quit"
                }else if(language === "Chinese"){
                    fileMenu.title = "&文件"
                    quitAction.text = "退出"
                }
            }
        }
        Menu{
            id: doMenu
            title: "&Do"
            MenuItem {action: readTokensAction}
            MenuItem {action: grammarParserAction}
            function __switchLanguage(language){
                if(language === "English"){
                    doMenu.title = "&Do"
                }else if(language === "Chinese"){
                    doMenu.title = "&动作"
                }
            }
        }
        Menu{
            id: appearanceMenu
            title: "&Appearance"
            MenuItem {text: "default"; onTriggered: switchSytle("default")}
            MenuItem {text: "Monokai"; onTriggered: switchSytle("Monokai")}
            MenuItem {text: "Lazy";    onTriggered: switchSytle("Lazy")}
            function __switchLanguage(language){
                if(language === "English"){
                    title = "&Appearance"
                }else if(language === "Chinese"){
                    title = "&外观"
                }
            }
        }
        Menu{
            id: languageMenu
            title: "&Language"
            MenuItem {id: englishMenu; text: "English"; onTriggered: switchLanguage("English")}
            MenuItem {id: chineseMenu; text: "Chinese"; onTriggered: switchLanguage("Chinese")}
            function __switchLanguage(language){
                if(language === "English"){
                    title = "&Language"
                    englishMenu.text = "English"
                    chineseMenu.text = "Chinese"
                }else if(language === "Chinese"){
                    title = "&语言"
                    englishMenu.text = "英语"
                    chineseMenu.text = "中文"
                }
            }
        }
        function _switchLanguage(language){
            fileMenu.__switchLanguage(language)
            doMenu.__switchLanguage(language)
            appearanceMenu.__switchLanguage(language)
            languageMenu.__switchLanguage(language)
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
        text: "Token Flow"
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
        }else if(style === "Monokai"){
            textAreaBackgrondColor = "#272822"
            textAreaTextColor = "#f8f8f2"
        }else if(style === "Lazy"){
            textAreaBackgrondColor = "#ffffff"
            textAreaTextColor = "#000000"
        }
    }

    function switchLanguage(language){
        if(language === "English"){
            fileOpenAction.text = "Open"
            fileSaveAction.text = "Save"
            grammarParserAction.text = "Parser"
            translateAction.text = "Trans"
            generateAction.text = "Generate"
            readTokensAction.text = "Tokens"
        }else if(language === "Chinese"){
            fileOpenAction.text = "打开"
            fileSaveAction.text = "保存"
            grammarParserAction.text = "语法分析"
            translateAction.text = "语义分析"
            generateAction.text = "代码生成"
            readTokensAction.text = "记号流"
        }
        menu._switchLanguage(language)
    }
}
