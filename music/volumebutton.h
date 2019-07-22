#ifndef VOLUMEBUTTON_H
#define VOLUMEBUTTON_H

#include <QToolButton>

//class QSlider;

QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSlider)

class VolumeButton : public QToolButton
{
    Q_OBJECT
public:
    explicit VolumeButton(QWidget *parent = nullptr);

    int getvolume() const;

signals:
    void volumeChanged(int volume);
public slots:
    void increaseVolume();
    void descreaseVolume();
    void setVolume(int volume);
    void stylize();

private:

    QMenu *menu = nullptr;
    QLabel *label = nullptr;
    QSlider *slider = nullptr;
};

#endif // VOLUMEBUTTON_H
