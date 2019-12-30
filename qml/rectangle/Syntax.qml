import QtQuick 2.0

Text {
    id: label
    x: 24; y:24
     anchors.centerIn: parent
    //	custom	counter property	for space   presses
    property int  spacePresses: 0

    text:"Space pressed: " + spacePresses + " times"

    //	(1)	handler	for	text	changes
    onTextChanged: console.log("text changed to:", text)

    //need focus to receive key events
    focus: true
    //(2)	handler	with	some	JS
    Keys.onSpacePressed: {
        increment()
    }
    //	clear	the	text	on	escape
    Keys.onEscapePressed: {
        //label.text = ' '
        spacePresses = 0
    }

    //	(3)	a	JS	function
    function	increment()	{
        spacePresses = spacePresses + 1
    }
}
