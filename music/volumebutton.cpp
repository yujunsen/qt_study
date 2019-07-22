#include "volumebutton.h"
#include <QtWidgets>
#include <QtWinExtras>


VolumeButton::VolumeButton(QWidget *parent) : QToolButton(parent)
{
    setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    setPopupMode(QToolButton::InstantPopup);

    QWidget *popup = new QWidget(this);
    slider = new QSlider(Qt::Horizontal, popup);
    slider->setRange(0, 100);
    connect(slider, &QSlider::valueChanged, this, &VolumeButton::volumeChanged);

    label = new QLabel(popup);
    label->setAlignment(Qt::AlignCenter);
    label->setNum(100);
    label->setMinimumWidth(label->sizeHint().width());
    connect(slider, &QAbstractSlider::valueChanged, label, QOverload<int>::of(&QLabel::setNum));

    QBoxLayout *popupLayout = new QHBoxLayout(popup);
    popupLayout->setMargin(2);
    popupLayout->addWidget(slider);
    popupLayout->addWidget(label);

    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(popup);

    menu = new QMenu(this);
    menu->addAction(action);
    setMenu(menu);
    stylize();

}

int VolumeButton::getvolume() const
{
    return slider->value();
}

void VolumeButton::increaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepAdd);
}

void VolumeButton::descreaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepSub);
}

void VolumeButton::setVolume(int volume)
{
    slider->setValue(volume);
}

/**
 *功能: 根据系统版本设置显示风格
 *参数: 无
 *返回: 无
 *其他: 2019/7/18 By Yjs
**/
void VolumeButton::stylize()
{
    if (QOperatingSystemVersion::current() < QOperatingSystemVersion::Windows8) {
        // Set styling options relevant only to Windows 7.
        if (QtWin::isCompositionEnabled()) {
            QtWin::enableBlurBehindWindow(menu);
            QString css("QMenu { border: 1px solid %1; border-radius: 2px; background: transparent; }");
            menu->setStyleSheet(css.arg(QtWin::realColorizationColor().name()));
        } else {
            QtWin::disableBlurBehindWindow(menu);
            QString css("QMenu { border: 1px solid black; background: %1; }");
            menu->setStyleSheet(css.arg(QtWin::realColorizationColor().name()));
        }
    }
}
