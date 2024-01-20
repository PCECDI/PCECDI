#ifndef UPDATER_H
#define UPDATER_H

#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QLabel>
#include <QProgressBar>
#include <QNetworkAccessManager>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QJsonValue>
#include <QJsonObject>
#include <QProcess>
#include <QJsonArray>
#include <QStyleFactory>
#include <fcntl.h>

class Updater : public QWidget
{
    Q_OBJECT

public:
    Updater(QWidget *parent = nullptr)
    {
        setupUI();
        connect();
    }
    ~Updater()
    {

    }

    void LaunchUpdates()
    {
        Update();
    }

private:
    QString LocalVersion;
    QString LatestVersion;
    QString DownloadUrl;
    QString ZipName;
    QNetworkAccessManager networkManager;
    QList<QNetworkReply *> activeReplies;
    QProgressBar *progressBar;
    QLabel *label1;
    QLabel *label2;

    void setupUI()
    {
        QVBoxLayout *layout = new QVBoxLayout(this);
        label1 = new QLabel("Updating PCECDI...", this);
        label2 = new QLabel("Searching for Updates...", this);
        label1->adjustSize();
        label2->adjustSize();
        this->setStyleSheet("background-color: white;");
        progressBar = new QProgressBar(this);
        progressBar->setTextVisible(0);
        progressBar->setRange(0, 0);
        progressBar->setValue(0);
        progressBar->setFixedSize(365, 14);
        layout->addWidget(label1);
        layout->addWidget(progressBar);
        layout->addWidget(label2);
        setWindowTitle("PCECDI");
        setWindowIcon(QIcon(":/Images/UpdaterIcon.ico"));
        setFixedSize(385, 90);
    }

    void connect()
    {
        QObject::connect(&networkManager, &QNetworkAccessManager::finished, this, &Updater::onReplyFinished);
    }

    void FailureUpdate()
    {
        progressBar->setValue(100);
        qDebug()<<"[Erreur] La mise à jour a échoué !\n";
        close();
    }

    void SucessUpdate()
    {
        progressBar->setValue(100);
        qDebug()<<"[Sucess] La mise à jour est installé !";
        QProcess process;
        process.startDetached(QString("PCECDI_%1.exe").arg(LatestVersion));
        qApp->quit();
    }

    void UpToDate()
    {
        progressBar->setValue(100);
        qDebug()<<"[Info] PCECDI is Up to Date !";
        close();
    }

    void ToUpVersion()
    {
        progressBar->setValue(100);
        qDebug()<<"[Error] Your version is newer version than the latest version !";
        close();
    }

    QString readLocalVersionFromFile(QString file)
    {
        QString localVersion;
        QFile versionFile(file);
        if (versionFile.open(QIODevice::ReadOnly)) {
            localVersion = QString(versionFile.readAll()).trimmed();
            versionFile.close();
        }
        return localVersion;
    }

    void retrieveLatestReleaseVersion(QUrl apiUrl)
    {
        QNetworkReply *reply = networkManager.get(QNetworkRequest(apiUrl));
        activeReplies.append(reply);
    }

    void onReplyFinished(QNetworkReply *reply)
    {
        label2->setText("Installing latest update...");
        progressBar->setRange(0, 100);
        if (reply->error() != QNetworkReply::NoError)
        {
            qDebug()<<"[Erreur] La dernière version n'a pas été trouvée : " + reply->errorString() + " !";
            FailureUpdate();
            return;
        }
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        reply->deleteLater();
        QString latestVersion = parseLatestReleaseVersion(jsonDoc);
        if (latestVersion.isEmpty()) {
            qDebug()<<"[Erreur] La dernière version n'a pas été trouvée.";
            FailureUpdate();
            return;
        }
        qDebug()<<"[Info] Dernière version : " + latestVersion;
        if (LocalVersion == latestVersion)
        {
            qDebug()<<"[Info] PCECDI est à jour.";
            UpToDate();
        }
        else if (LocalVersion > latestVersion)
        {
            qDebug()<<"[Info] Vous utilisez une version supérieur à la dernière version disponible !";
            ToUpVersion();
        }
        else if (LocalVersion < latestVersion)
        {
            qDebug()<<"[Info] Téléchargement de la dernière version...";
            downloadLatestVersion();
            progressBar->setValue(50);
        }
    }

    QString parseLatestReleaseVersion(const QJsonDocument &jsonDoc)
    {
        QJsonObject jsonObj = jsonDoc.object();
        QJsonValue tagName = jsonObj.value("tag_name");
        QString tagNameStr = tagName.toString();
        LatestVersion = tagNameStr;
        if (!jsonDoc.isObject()) {
            FailureUpdate();
        }
        if (!jsonObj.contains("assets") || !jsonObj.value("assets").isArray()) {
            FailureUpdate();
        }
        QJsonArray assetsArray = jsonObj.value("assets").toArray();
        for (const QJsonValue &assetValue : assetsArray) {
            if (!assetValue.isObject()) {
                continue;
            }
            QJsonObject assetObj = assetValue.toObject();
            if (!assetObj.contains("browser_download_url") || !assetObj.value("browser_download_url").isString()) {
                continue;
            }
            DownloadUrl = assetObj.value("browser_download_url").toString();
            ZipName = assetObj.value("name").toString();
            break;
        }
        progressBar->setValue(25);
        return tagNameStr;
    }

    void downloadLatestVersion()
    {
        QNetworkRequest request(DownloadUrl);
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(request);
        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();
        if (reply->error() != QNetworkReply::NoError) {
            qDebug()<<"[Erreur] Erreur lors du téléchargement : " + reply->errorString();
            FailureUpdate();
            reply->deleteLater();
        }
        creat(ZipName.toLatin1(), 0777);
        QFile file(ZipName);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
            qDebug()<<"[Succes] Archive téléchargée avec succès";
        } else {
            qDebug()<<"[Error] Erreur lors de l'enregistrement de l'archive";
            FailureUpdate();
        }
        reply->deleteLater();
        progressBar->setValue(75);
        Unzip();
    }

    void Unzip()
    {
        QProcess process;
        QString ZipName2 = ZipName;
        ZipName2.remove(".zip");
        ZipName2.append("/");
        process.setProgram("tar");
        process.setArguments(QStringList() << "-xvf" << ZipName << "--strip-components=1" << ZipName2);
        process.start();
        process.waitForFinished(-1);
        if(process.exitCode() == 1)
        {
            qDebug()<<"[Succes] L'archive a été décompréssée avec succes !";
        }
        else
        {
            qDebug()<<"[Erreur] La décompression de l'archive a échoué !";
            FailureUpdate();
        }
        QFile j("PCECDI_" + LocalVersion + ".exe");
        QFile h(ZipName);
        h.remove();
        j.remove();
        SucessUpdate();
    }

    void Update()
    {
        QString localVersion = readLocalVersionFromFile(":/TextFiles/version.txt");
        if (localVersion.isEmpty()) {
            qDebug()<<"[Erreur] La version locale n'a pas été trouvée !";
            FailureUpdate();
            return;
        }
        else
        {
            LocalVersion = localVersion;
        }
        qDebug()<<"[Info] Version locale : "  + localVersion;
        retrieveLatestReleaseVersion(QUrl("https://api.github.com/repos/TheGordonFreeman42/PCECDI/releases/latest"));
    }
};
#endif // UPDATER_H
