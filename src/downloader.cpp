#include "downloader.h"
#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include "downloaderHlsItem.h"
#include "downloaderMultipleItem.h"
#include "downloaderSingleItem.h"

Downloader::Downloader(QObject* parent) : QObject(parent)
{
}

Downloader::~Downloader()
{
}

Downloader * Downloader::instance()
{
    static Downloader* c_instance = nullptr;
    if (c_instance == nullptr)
        c_instance = new Downloader(qApp);
    return c_instance;
}


void Downloader::addTasks(const QString& filename, const QList<QUrl>& urls, const QUrl& danmakuUrl, bool isDash)
{
    QSettings settings;
    QDir dir(settings.value(QStringLiteral("downloader/save_to")).toUrl().toLocalFile());
    QString filepath = dir.filePath(filename);
    DownloaderAbstractItem* item;
    
    if (urls[0].path().endsWith(QStringLiteral(".m3u8")))
        item = new DownloaderHlsItem(filepath, urls[0], danmakuUrl, this);
    else if (urls.length() == 1)
        item = new DownloaderSingleItem(filepath, urls[0], danmakuUrl, this);
    else
        item = new DownloaderMultipleItem(filepath, urls, danmakuUrl, isDash, this);
    m_model << item;
    emit modelUpdated();
}

QList<QObject *> Downloader::model()
{
    return m_model;
}

