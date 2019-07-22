#include "musicplayer.h"
#include "volumebutton.h"
#include <QToolButton>
#include <QStyle>
#include <QSlider>
#include <QLabel>
#include <QBoxLayout>
#include <QShortcut>
#include <QCoreApplication>
#include <QtWinExtras>
#include <QFileDialog>
//#include <QtWcreateWidgetsidgets>

/**
 *功能: 初始化播放器
 *参数:
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
MusicPlayer::MusicPlayer(QWidget *parent) : QWidget(parent)
{
    createWidgets();
    createJumpList();
    createTaskbar();
    createThumbnailToolBar();

    connect(&mediaPlayer, &QMediaPlayer::positionChanged, this, &MusicPlayer::updatePosition);
    connect(&mediaPlayer, &QMediaPlayer::durationChanged, this, &MusicPlayer::updateDuration);
    connect(&mediaPlayer, &QMediaPlayer::metaDataAvailableChanged, this, &MusicPlayer::updateInfo);

    connect(&mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
            this, &MusicPlayer::handleError);
    connect(&mediaPlayer, &QMediaPlayer::stateChanged,
            this, &MusicPlayer::updateState);

    stylize();
    setAcceptDrops(true);
}

/**
 *功能: 获取支持播放类型
 *参数:
 *返回: QStringList 格式列表
 *其他: 2019/7/22 By Yjs
**/
QStringList MusicPlayer::supportedMimeTypes()
{
    QStringList result =  QMediaPlayer::supportedMimeTypes();
    if(result.isEmpty())
        result.append(QStringLiteral("audio/mpeg"));
    return result;
}

/**
 *功能: 播放url文件
 *参数: url播放文件
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::playUrl(const QUrl &url)
{
     playButton->setEnabled(true);
     if(url.isLocalFile())
     {
         const QString filePath = url.toLocalFile();
         setWindowFilePath(filePath);
         infoLabel->setText(QDir::toNativeSeparators(filePath));
         fileName = QFileInfo(filePath).fileName();
     }
     else
     {
         setWindowFilePath(QString());
         infoLabel->setText(url.toString());
         fileName.clear();
     }
     mediaPlayer.setMedia(url);
     mediaPlayer.play();
}

/**
 *功能: 根据播放状态做出动作
 *参数: 无
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::togglePlayback()
{
    if(mediaPlayer.mediaStatus() == QMediaPlayer::NoMedia)
        openFile();
    else if (mediaPlayer.state() == QMediaPlayer::PlayingState)
        mediaPlayer.pause();
    else
        mediaPlayer.play();
 }

/**
 *功能: 快进
 *参数: 无
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::seekForward()
{
    positionSlider->triggerAction(QSlider::SliderPageStepAdd);
}

/**
 *功能: 后退
 *参数: 无
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::seekBackward()
{
    positionSlider->triggerAction(QSlider::SliderPageStepSub);
}

/**
 *功能: 打开文件
 *参数: 无
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::openFile()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle("Open file");
    fileDialog.setMimeTypeFilters(MusicPlayer::supportedMimeTypes());
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath()));
    if(fileDialog.exec() == QDialog::Accepted)
        playUrl(fileDialog.selectedUrls().constFirst());
}

/**
 *功能: 选择进度位置
 *参数: 无
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::setPosition(int position)
{
    if(qAbs(mediaPlayer.position() - position) > 99)
        mediaPlayer.setPosition(position);
}

/**
 *功能: 任务栏状态更改
 *参数: 无
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::updateTaskbar()
{
    switch(mediaPlayer.state())
    {
    case QMediaPlayer::PlayingState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    case QMediaPlayer::PausedState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    case QMediaPlayer::StoppedState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaStop));
        break;
    }
    taskbarProgress->show();
    taskbarProgress->resume();
}

/**
 *功能: 缩略图按钮更改
 *参数: 无
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::updateThumbnailToolBar()
{
    playToolButton->setEnabled(mediaPlayer.duration() > 0);
    backwardToolButton->setEnabled(mediaPlayer.duration() > 0);
    forwardToolButton->setEnabled(mediaPlayer.position() < mediaPlayer.duration());

    if(mediaPlayer.state() == QMediaPlayer::PlayingState)
    {
        playToolButton->setToolTip("Pause");
        playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        playToolButton->setToolTip("Play");
        playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

/**
 *功能: 转换显示时间
 *参数: timeMilliSeconds 传入时间
 *返回: 显示的时间
 *其他: 2019/7/22 By Yjs
**/
static QString formatTime(qint64 timeMilliSeconds)
{
    qint64 seconds = timeMilliSeconds / 1000;
    const qint64 minutes = seconds / 60;
    return QStringLiteral("%1:%3")
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'));
}

/**
 *功能: 根据播放进度更改QSlider位置
 *参数: duration 位置
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::updatePosition(qint64 duration)
{
    positionSlider->setValue(static_cast<int>(duration));
    positionLabel->setText(formatTime(duration));
}

/**
 *功能:
 *参数:
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::updateDuration(qint64 position)
{
    positionSlider->setRange(0, static_cast<int>(position));
    positionSlider->setEnabled(position > 0);
    positionSlider->setPageStep(static_cast<int>(position / 10));
    updateInfo();
}

/**
 *功能: 输出文件信息
 *参数: 无
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::updateInfo()
{
    QStringList info;
    if (!fileName.isEmpty())
        info.append(fileName);
    if (mediaPlayer.isMetaDataAvailable()) {
        QString author = mediaPlayer.metaData(QStringLiteral("Author")).toString();
    if (!author.isEmpty())
        info.append(author);
    QString title = mediaPlayer.metaData(QStringLiteral("Title")).toString();
    if (!title.isEmpty())
        info.append(title);
    }
    info.append(formatTime(mediaPlayer.duration()));
    infoLabel->setText(info.join(tr(" - ")));
}

/**
 *功能: 输出错误信息
 *参数: 无
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::handleError()
{
    playButton->setEnabled(false);
    const QString errorString = mediaPlayer.errorString();
    infoLabel->setText(errorString.isEmpty()
                       ? tr("Unknown error #%1").arg(int(mediaPlayer.error()))
                       : tr("Error: %1").arg(errorString));
}

/**
 *功能: 更改播放状态
 *参数: 无
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::updateState(QMediaPlayer::State state)
{
     if (state == QMediaPlayer::PlayingState)
     {
        playButton->setToolTip("Pause");
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
     }
     else
     {
        playButton->setToolTip("Play");
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
     }
}

/**
 *功能: 创建播放菜单栏
 *参数:
 *返回: 无
 *其他: 2019/7/18 By Yjs
**/
void MusicPlayer::createWidgets()
{
    playButton = new QToolButton(this);
    playButton->setEnabled(false);
    playButton->setToolTip(tr("Play"));
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton, &QAbstractButton::clicked, this, &MusicPlayer::togglePlayback);

    QAbstractButton *openButton = new QToolButton(this);
    openButton->setText(tr("..."));
    openButton->setToolTip(tr("Open a file..."));
    openButton->setFixedSize(playButton->sizeHint());
    connect(openButton, &QAbstractButton::clicked, this, &MusicPlayer::openFile);

    volumeButton = new VolumeButton(this);
    volumeButton->setToolTip(tr("Adjust volume"));
    volumeButton->setVolume(mediaPlayer.volume());
    connect(volumeButton, &VolumeButton::volumeChanged, &mediaPlayer, &QMediaPlayer::setVolume);

    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setEnabled(false);
    positionSlider->setToolTip(tr("seek"));
    connect(positionSlider, &QAbstractSlider::valueChanged, this, &MusicPlayer::setPosition);

    infoLabel = new QLabel(this);
    positionLabel = new QLabel(tr("00:00"), this);
    positionLabel->setMinimumWidth(positionLabel->sizeHint().width());

    QBoxLayout * controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(positionSlider);
    controlLayout->addWidget(positionLabel);
    controlLayout->addWidget(volumeButton);

    QBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->addWidget(infoLabel);
    mainlayout->addLayout(controlLayout);
}

/**
 *功能: 绑定快捷方式
 *参数:
 *返回: 无
 *其他: 2019/7/18 By Yjs
**/
void MusicPlayer::createShortcuts()
{
    QShortcut *quitShortcut = new QShortcut(QKeySequence::Quit, this);
    connect(quitShortcut, &QShortcut::activated, QCoreApplication::quit);

    QShortcut *openShortcut = new QShortcut(QKeySequence::Open, this);
    connect(openShortcut, &QShortcut::activated, this, &MusicPlayer::openFile);

    QShortcut *toggleShortcut = new QShortcut(Qt::Key_Space, this);
    connect(toggleShortcut, &QShortcut::activated, this, &MusicPlayer::togglePlayback);

    QShortcut *forwardShortcut = new QShortcut(Qt::Key_Right, this);
    connect(forwardShortcut, &QShortcut::activated, this, &MusicPlayer::seekForward);

    QShortcut *backwardShortcut = new QShortcut(Qt::Key_Left, this);
    connect(backwardShortcut, &QShortcut::activated, this, &MusicPlayer::seekBackward);

    QShortcut *increaseShortcut = new QShortcut(Qt::Key_Up, this);
    connect(increaseShortcut, &QShortcut::activated, volumeButton, &VolumeButton::increaseVolume);

    QShortcut *decreaseShortcut = new QShortcut(Qt::Key_Down, this);
    connect(decreaseShortcut, &QShortcut::activated, volumeButton, &VolumeButton::descreaseVolume);
}

void MusicPlayer::createJumpList()
{
    QWinJumpList jumplistl;
    jumplistl.recent()->setVisible(true);
}

/**
 *功能: 创建任务栏按钮 关联播放状态更改
 *参数:
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::createTaskbar()
{
    taskbarButton = new QWinTaskbarButton(this);
    taskbarButton->setWindow(windowHandle());

    taskbarProgress = taskbarButton->progress();
    connect(positionSlider, &QAbstractSlider::valueChanged, taskbarProgress, &QWinTaskbarProgress::setValue);
    connect(positionSlider, &QAbstractSlider::rangeChanged, taskbarProgress, &QWinTaskbarProgress::setRange);

    connect(&mediaPlayer, &QMediaPlayer::stateChanged, this, &MusicPlayer::updateTaskbar);
}

/**
 *功能: 界面最小化 缩略图的菜单栏
 *参数:
 *返回: 无
 *其他: 2019/7/18 By Yjs
**/
void MusicPlayer::createThumbnailToolBar()
{
    thumbnailToolBar = new QWinThumbnailToolBar(this);
    thumbnailToolBar->setWindow(windowHandle());

    playToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    playToolButton->setEnabled(false);
    playToolButton->setToolTip(tr("Play"));
    playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playToolButton, &QWinThumbnailToolButton::clicked, this, &MusicPlayer::togglePlayback);

    forwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    forwardToolButton->setEnabled(false);
    forwardToolButton->setToolTip(tr("Fast forward"));
    forwardToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    connect(forwardToolButton, &QWinThumbnailToolButton::clicked, this, &MusicPlayer::seekForward);

    backwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    backwardToolButton->setEnabled(false);
    backwardToolButton->setToolTip(tr("Rewind"));
    backwardToolButton  ->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    connect(backwardToolButton, &QWinThumbnailToolButton::clicked, this, &MusicPlayer::seekBackward);

    thumbnailToolBar->addButton(playToolButton);
    thumbnailToolBar->addButton(forwardToolButton);
    thumbnailToolBar->addButton(backwardToolButton);

    connect(&mediaPlayer, &QMediaPlayer::positionChanged, this, &MusicPlayer::updateThumbnailToolBar);
    connect(&mediaPlayer, &QMediaPlayer::durationChanged, this, &MusicPlayer::updateThumbnailToolBar);
    connect(&mediaPlayer, &QMediaPlayer::stateChanged, this, &MusicPlayer::updateThumbnailToolBar);
}

/**
 *功能: 根据系统更改风格
 *参数: 无
 *返回: 无
 *其他: 2019/7/22 By Yjs
**/
void MusicPlayer::stylize()
{
    if (QOperatingSystemVersion::current() < QOperatingSystemVersion::Windows8) {
        // Set styling options relevant only to Windows 7.
        if (QtWin::isCompositionEnabled()) {
            QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
            setAttribute(Qt::WA_TranslucentBackground, true);
            setAttribute(Qt::WA_NoSystemBackground, false);
            setStyleSheet(QStringLiteral("MusicPlayer { background: transparent; }"));
        } else {
            QtWin::resetExtendedFrame(this);
            setAttribute(Qt::WA_TranslucentBackground, false);
            setStyleSheet(QStringLiteral("MusicPlayer { background: %1; }").arg(QtWin::realColorizationColor().name()));
        }
        volumeButton->stylize();
    }
}
