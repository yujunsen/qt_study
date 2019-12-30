import QtQuick 2.0

Item {
    //	set	width	based	on	given	background
    Image {
        id: bg
        source: "assets/background.png"
    }
    width: bg.width
    height: bg.height

    MouseArea{
        id : backgroundClicker
        anchors.fill: parent
        onClicked: {
            //	reset	our	little	scene
            rocket1 .x =20
            rocket2.rotation	=	0
            rocket3.rotation	=	0
            rocket3.scale	=	1.0
        }
    }
    ClickableImage{
        id : rocket1
        x : 20; y:  100
        source  : "assets/rocket.png"
        onClicked : {
            x	+=	5
        }
    }

    ClickableImage{
        id : rocket2
        x : 140; y:  100
        source  : "assets/rocket.png"
        onClicked : {
            rotation	+=	5
        }
    }
    ClickableImage{
        id : rocket3
        x : 240; y:  100
        source  : "assets/rocket.png"
        onClicked : {
            rotation	+=	5
            scale -= 0.05
        }
    }
}
