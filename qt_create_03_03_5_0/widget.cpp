#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

/*
 * 先看两个Scroll Bar的属性：
 *  maximum属性用来设置最大值，minimum属性用来设置最小值；
 *  singleStep属性是每步的步长，默认是1，就是按下方向键后其数值增加或者减少1；
 *  pageStep是每页的步长，默认是10，就是按下PageUp或者PageDown按键后，其数值增加或者减少10；
 *  value与sliderPosition是当前值；tracking设置是否跟踪，默认为是，就是在拖动滑块时，每移动一个刻度，
 *  都会发射valueChanged（）信号，如果选择否，则只有拖动滑块释放时才发射该信号；
 *  orientation设置部件的方向，有水平和垂直两种选择；
 *  invertedAppearance属性设置滑块所在的位置，
 *  比如默认滑块开始在最左端，选中这个属性后，滑块默认就会在最右端。
 *  invertedControls设置反向控制，比如默认是向上方向键是增大，向下方向键是减小，如果选中这个属性，那么控制就会正好反过来。
 *  另外，为了使部件可以获得焦点，需要将focusPolicy设置为StrongFocus。
 *  再来看两个Slider，它们有了自己的两个属性tickPosition和ticklnterval，前者用来设置显示刻度的位置，默认是不显示刻度；
 *  后者是设置刻度的间隔。
 *  而Dial有自己的属性wrapping，用来设置是否首尾相连，默认开始与结束是分开的；
 *  属性notchTarget用来设置刻度之间的间隔；属性notchesVisible用来设置是否显示刻度。
*/
