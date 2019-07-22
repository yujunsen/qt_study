#include <QApplication>
#include <QFileInfo>
#include <QDebug>
#include <QSettings>
#include <QMimeDatabase>
#include <QDir>
#include <QCommandLineParser>
#include <QUrl>
#include <QDesktopWidget>
#include <QScreen>
#include "musicplayer.h"

static bool associateFileTypes();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("MusicPlayer"));
    QCoreApplication::setApplicationVersion( QLatin1String(QT_VERSION_STR));
    QCoreApplication::setOrganizationName(QStringLiteral("QtWinExtras"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("qt-project.org"));
    QGuiApplication::setApplicationDisplayName(QStringLiteral("QtWinExtras Music Player"));
    if (!associateFileTypes())
        return -1;

    QCommandLineParser parser;
    parser.setApplicationDescription(QGuiApplication::applicationDisplayName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument(QStringLiteral("url"), MusicPlayer::tr("The URL to open."));
    parser.process(app);

     MusicPlayer player;

    if (!parser.positionalArguments().isEmpty())
            player.playUrl(QUrl::fromUserInput(parser.positionalArguments().constFirst(), QDir::currentPath(), QUrl::AssumeLocalFile));
     //获取可用桌面大小
//    const QRect availableGeometry = QApplication::desktop()->availableGeometry(&player);
//    player.resize(availableGeometry.width() / 6, availableGeometry.height() / 17);
//    player.show();

    QList<QScreen*>list = QGuiApplication::screens();//获取屏幕数量
    const QRect availableGeometry = list.at(0)->availableGeometry();
    player.resize(availableGeometry.width() / 6, availableGeometry.height() / 17);
    player.show();

    return  app.exec();
}


/**
 *功能: 获取ini文件的键值对
 *参数:
 *返回: true 读取成功 fasle读取失败
 *其他:2019/7/18 By Yjs
**/
static bool associateFileTypes()
{
    QString displayName = QGuiApplication::applicationDisplayName();
    QString filePath = QCoreApplication::applicationFilePath();
    QString fileName = QFileInfo(filePath).fileName().remove(QStringLiteral(".exe"));


    const QString key = filePath.remove(fileName + ".exe") + fileName +  QStringLiteral(".ini");
    QSettings settings(key, QSettings::IniFormat);
    if (settings.status() != QSettings::NoError)
    {
        qWarning() << "Cannot access registry key" << key;
        return false;
    }
    settings.setValue(QStringLiteral("FriendlyAppName"), displayName);


    settings.beginGroup(QStringLiteral("SupportedTypes"));
    QMimeDatabase mimeDatabase;
    const QStringList supportedMimeTypes = MusicPlayer::supportedMimeTypes();

    foreach(const QString &fileType, supportedMimeTypes)
    {
        const QStringList suffixes = mimeDatabase.mimeTypeForName(fileType).suffixes();
        foreach(QString suffix, suffixes)
        {
            suffix.prepend('.');
            settings.setValue(suffix, QString());
        }
    }
    settings.endGroup();

//    settings.beginGroup(QStringLiteral("shell"));
//    settings.beginGroup(QStringLiteral("open"));
//    settings.setValue(QStringLiteral("FriendlyAppName"), displayName);
//    settings.beginGroup(QStringLiteral("Command"));
//    settings.setValue(QStringLiteral("."),
//                      QLatin1Char('"') + QDir::toNativeSeparators(filePath) + QStringLiteral("\" \"%1\""));

    return true;
}
