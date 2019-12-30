import QtQuick 2.0

Rectangle	{
    id  : root
    property alias text: label.text
    signal clicked

    width:	116;	height:	26
    color:	"lightsteelblue"
    border.color:	"slategrey"

    Text {
        id: label
        anchors.centerIn:	parent
        text: qsTr("Start")
    }
    MouseArea	{
        anchors.fill:	parent
        onClicked:	{
            root.clicked()
        }
    }

    //    Button{
    //        id:	button
    //        x:	12;	y:	12
    //        text:	"Start"
    //        onClicked:	{
    //            status.text	=	"Button	clicked!"
    //        }
    //    }
    //    Text	{	//	text	changes	when	button	was	clicked
    //        id:	status
    //        x:	12;	y:	76
    //        width:	116;	height:	26
    //        text:	"waiting	..."
    //            horizontalAlignment:	Text.AlignHCenter
    //    }
}
