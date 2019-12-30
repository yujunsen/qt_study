import QtQuick 2.8

Rectangle{
    width: 360
    height: 360
    Text {
        anchors.centerIn: parent
        text: qsTr("HelloWorld")
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}

//import QtQuick.Window 2.2

//Window {
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("Hello World")

//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
//        }
//    }

//    TextEdit {
//        id: textEdit
//        text: qsTr("Enter some text...")
//        verticalAlignment: Text.AlignVCenter
//        anchors.top: parent.top
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.topMargin: 20
//        Rectangle {
//            anchors.fill: parent
//            anchors.margins: -10
//            color: "transparent"
//            border.width: 1
//        }
//    }
//}
