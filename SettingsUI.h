#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QWidget>
#include <QApplication>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QSize>
#include <QPixmap>
#include <QTextEdit>
#include <QGroupBox>
#include <QProcess>
#include <QTranslator>
#include <QLineEdit>
#include <QDesktopServices>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QScreen>
#include <QHBoxLayout>
#include <QDir>
#include <QComboBox>
#include <QRect>
#include <fcntl.h>

class SettingsUI : public QWidget
{
    Q_OBJECT

public:
    SettingsUI(QString hello)
    {
        setupUI(hello);
        connectButtons();
    }
    ~SettingsUI()
    {

    }

    void ResetFieldsSettings()
    {
        TextEdit2->setText(QDir::currentPath() + "/CSVFiles");
        tabWidget->setCurrentIndex(0);
    }

    QComboBox *LanguageCombo;

private:
    QWidget *GeneralTab;
    QWidget *AboutTab;
    QTabWidget *tabWidget;
    QLabel *CreditsShort;
    QLabel *CSVPath;
    QLabel *TitleandIcon;
    QLabel *Credits;
    QLabel *Language;
    QPushButton *OKButton;
    QPushButton *RestartButton;
    QPushButton *AboutQt;
    QTextEdit *TextEdit2;
    QLineEdit *VersionInfo;
    QPushButton *OpenDirCSVButton;
    QPushButton *OpenDirExeButton;
    QPushButton *OpenDirSettingsButton;

    void setupUI(QString hello2)
    {
        QVBoxLayout *settingsLayout = new QVBoxLayout;
        QVBoxLayout *settingsGeneralLayout = new QVBoxLayout;
        QVBoxLayout *settingsAboutLayout = new QVBoxLayout;
        QHBoxLayout *settingsLayoutH = new QHBoxLayout;
        QHBoxLayout *settingsGeneralLayoutH = new QHBoxLayout;
        QHBoxLayout *settingsGeneralLayoutH2 = new QHBoxLayout;
        TextEdit2 = new QTextEdit(this);
        CSVPath = new QLabel(tr("CSV files folder\npath:"), this);
        Language = new QLabel(tr("Language :"), this);
        LanguageCombo = new QComboBox(this);
        LanguageCombo->setFixedWidth(266);
        TextEdit2->setFixedWidth(266);
        ResetComboBoxLanguage();
        OpenDirCSVButton = new QPushButton(tr("Open CSV files folder"), this);
        OpenDirSettingsButton = new QPushButton(tr("Open the choices file"), this);
        OpenDirExeButton = new QPushButton(tr("Open the executable folder"), this);
        VersionInfo = new QLineEdit(this);
        AboutQt = new QPushButton(tr("About Qt"), this);
        TitleandIcon = new QLabel(this);
        Credits = new QLabel(tr("This program was created for the CDI by TheGordonFreeman42.\nThe wallpaper image was\ntaken from: https://pxhere.com/fr/photo/1593135.\nThis program was created with Qt. For more info:\n"), this);
        TitleandIcon->setPixmap(QPixmap(":/Images/TitleWithIcon.png"));
        AboutTab = new QWidget;
        GeneralTab = new QWidget;
        OKButton = new QPushButton("OK", this);
        OKButton->setFixedWidth(75);
        RestartButton = new QPushButton(tr("Cancel"), this);
        RestartButton->setFixedWidth(75);
        CreditsShort = new QLabel("TheGordonFreeman42", this);
        tabWidget = new QTabWidget(this);
        tabWidget->addTab(GeneralTab, tr("General"));
        tabWidget->addTab(AboutTab, tr("About"));
        VersionInfo->setReadOnly(1);
        VersionInfo->setAlignment(Qt::AlignCenter);
        VersionInfo->setText(hello2);
        VersionInfo->setStyleSheet("border: none;");
        setLayout(settingsLayout);
        settingsLayout->addWidget(tabWidget);
        settingsLayout->addLayout(settingsLayoutH);
        settingsLayoutH->addWidget(CreditsShort);
        settingsLayoutH->addWidget(OKButton);
        settingsLayoutH->addWidget(RestartButton);

        GeneralTab->setLayout(settingsGeneralLayout);
        AboutTab->setLayout(settingsAboutLayout);
        settingsAboutLayout->addWidget(TitleandIcon);
        settingsAboutLayout->addWidget(Credits);
        settingsAboutLayout->addWidget(AboutQt);
        settingsGeneralLayout->addWidget(VersionInfo);
        settingsGeneralLayout->addLayout(settingsGeneralLayoutH);
        settingsGeneralLayout->addLayout(settingsGeneralLayoutH2);
        settingsGeneralLayout->addWidget(OpenDirCSVButton);
        settingsGeneralLayout->addWidget(OpenDirExeButton);
        settingsGeneralLayout->addWidget(OpenDirSettingsButton);
        settingsGeneralLayoutH->addWidget(CSVPath);
        settingsGeneralLayoutH->addWidget(TextEdit2);
        settingsGeneralLayoutH2->addWidget(Language);
        settingsGeneralLayoutH2->addWidget(LanguageCombo);
        Credits->setAlignment(Qt::AlignHCenter);
        TitleandIcon->setAlignment(Qt::AlignHCenter);

        setWindowIcon(QIcon(":/Images/Icon.png"));
        setWindowTitle(tr("Tools"));
        setFixedSize(417, 336);
    }

    void connectButtons()
    {
        QObject::connect(OKButton, SIGNAL(clicked()), this, SLOT(quit()));
        QObject::connect(RestartButton, SIGNAL(clicked()), this, SLOT(restart()));
        QObject::connect(OpenDirCSVButton, SIGNAL(clicked()), this, SLOT(OpenCSVFile()));
        QObject::connect(OpenDirExeButton, SIGNAL(clicked()), this, SLOT(OpenExeFile()));
        QObject::connect(OpenDirSettingsButton, SIGNAL(clicked()), this, SLOT(OpenSettingsFile()));
        QObject::connect(AboutQt, SIGNAL(clicked()), qApp, SLOT(aboutQt()));
        QObject::connect(LanguageCombo, SIGNAL(activated(int)), this, SLOT(ChangeLanguage()));
    }

    void ResetComboBoxLanguage()
    {
        LanguageCombo->clear();
        LanguageCombo->addItem("Français");
        LanguageCombo->addItem("English");
        LanguageCombo->addItem("Deutsch");
        LanguageCombo->addItem("Русский");
    }

private slots:
    void ChangeLanguage()
    {
        QFile FichierChoix2("Settings/Language.txt");
        if(FichierChoix2.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream FichierCroixStream2(&FichierChoix2);
            int hello = LanguageCombo->currentIndex();
            switch (hello)
            {
                case 0:   // Français
                    FichierCroixStream2<<"fr";
                    break;

                case 1:   // English
                    FichierCroixStream2<<"en";
                    break;

                case 2:   // Deutsch
                    FichierCroixStream2<<"de";
                    break;

                case 3:   // Русский
                    FichierCroixStream2<<"ru";
                    break;

                default:
                    break;
            }
            FichierChoix2.close();
        }
        qApp->quit();
        QProcess process;
        process.startDetached("PCECDI.exe");
        process.waitForFinished(-1);
    }

    void OpenSettingsFile()
    {
        QDesktopServices::openUrl(QUrl(QDir::currentPath() + "/Settings/Choises.txt"));
    }

    void quit()
    {
        close();
    }

    void restart()
    {
        close();
    }

    void OpenExeFile()
    {
        QDesktopServices::openUrl(QUrl(QDir::currentPath()));
    }

    void OpenCSVFile()
    {
        QString CSVPath = QString("%1/CSVFiles").arg(QDir::currentPath());
        if(!QDesktopServices::openUrl(QUrl(CSVPath)))
        {
            mkdir("CSVFiles");
            QDesktopServices::openUrl(QUrl(CSVPath));
        }
    }
};
#endif // MAINSETTINGS_H
