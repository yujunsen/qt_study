#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

//#include <QAbstractButton>
#include <QWidget>
#include <QMediaPlayer>

class QAbstractButton;
class VolumeButton;
class QSlider;
class QLabel;
class QWinTaskbarButton;
class QWinTaskbarProgress;
class QWinThumbnailToolBar;
class QWinThumbnailToolButton;

class MusicPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    static QStringList supportedMimeTypes();
signals:

public slots:
    void stylize();
    void playUrl(const QUrl& url);
    void togglePlayback();
    void seekForward();
    void seekBackward();
    void openFile();
    void setPosition(int position);

    void updateTaskbar();
    void updateThumbnailToolBar();
    void updatePosition(qint64 duration);
    void updateDuration(qint64 position);
    void updateInfo();
    void handleError();
    void updateState(QMediaPlayer::State state);

private:
    void createWidgets();
    void createShortcuts();
    void createJumpList();
    void createTaskbar();
    void createThumbnailToolBar();

    QMediaPlayer mediaPlayer;

    QWinTaskbarButton *taskbarButton = nullptr;
    QWinTaskbarProgress *taskbarProgress = nullptr;
    QWinThumbnailToolBar *thumbnailToolBar = nullptr;
    QWinThumbnailToolButton *playToolButton = nullptr;
    QWinThumbnailToolButton *forwardToolButton = nullptr;
    QWinThumbnailToolButton *backwardToolButton = nullptr;

    QAbstractButton *playButton = nullptr;
    VolumeButton *volumeButton = nullptr;
    QSlider *positionSlider = nullptr;
    QLabel *positionLabel = nullptr;
    QLabel *infoLabel = nullptr;
    QPoint offset;
    QString fileName;

};

#endif // MUSICPLAYER_H
