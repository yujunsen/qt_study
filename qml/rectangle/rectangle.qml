import QtQuick 2.6
import QtQuick.Controls 1.5

//	The	root	element	is	the	Rectangle
Rectangle{
    //	name	this	element	root
    id:	root
    //	properties:	<name>:	<value>
    width:	120;	height:	240
    //	color	property
    color:	"#D8D8D8"
    //	Declare	a	nested	element	(child	of	root)
    Image	{
        id:	rocket

        //	reference	the	parent
        x:	(parent.width	-	width)/2;	y:	40

        source:	'assets/rocket.png'

        //	Another	child	of	root
        Text	{
            //	un-named	element
            //	reference	element	by	id
            y:	rocket.y	+	rocket.height	+	20
            //	reference	root	element
            width:	root.width
            horizontalAlignment:	Text.AlignHCenter
            text:	'Rocket'
        }
    }
}
/*
 import声明导入了一个指定的模块版本。一般来说会导入QtQuick2.0来作为初始元素的引用
 每一个QML文件都需要一个根元素，就像HTML一样
 一个元素使用它的类型声明，然后使用{}进行包含。
 元素拥有属性，他们按照name:value的格式来赋值。
 任何在QML文档中的元素都可以使用它们的id进行访问（id是一个任意的标识符）。
 元素可以嵌套，这意味着一个父元素可以拥有多个子元素。子元素可以通过访问parent关键字来访问它们的父元素。
*/
