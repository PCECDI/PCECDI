#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QWidget>
#include <QApplication>
#include <QTabWidget>
#include <QPushButton>
#include <QProcess>
#include <QLabel>
#include <QSize>
#include <QPixmap>
#include <QTextEdit>
#include <QGroupBox>
#include <QDesktopServices>
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
    SettingsUI(QWidget *parent = nullptr)
    {
        setupUI();
        connectButtons();
    }
    ~SettingsUI()
    {

    }

    void ResetFieldsSettings()
    {
        TextEdit2->setText(QDir::currentPath() + "/CSVFiles");
        tabWidget->setCurrentIndex(0);
        ResetMedCombo();
    }


private:
    QWidget *GeneralTab;
    QWidget *AboutTab;
    QTabWidget *tabWidget;
    QLabel *CreditsShort;
    QLabel *CSVPath;
    QLabel *TitleandIcon;
    QLabel *Credits;
    QPushButton *OKButton;
    QPushButton *ApplyButton;
    QPushButton *RestartButton;
    QPushButton *AboutQt;
    QTextEdit *TextEdit2;
    QPushButton *OpenDirCSVButton;
    QPushButton *OpenDirExeButton;
    QLabel *ctrl;
    QLabel *ctrl2;
    QLabel *ctrl3;
    QGroupBox *GroupBox1;
    QGroupBox *GroupBox2;
    QComboBox *ShortMedCombo1;
    QComboBox *ShortMedCombo2;
    QComboBox *ShortMedCombo3;

    void setupUI()
    {
        QVBoxLayout *settingsLayout = new QVBoxLayout;
        QVBoxLayout *settingsGeneralLayout = new QVBoxLayout;
        QVBoxLayout *settingsAboutLayout = new QVBoxLayout;
        QVBoxLayout *LayoutGroup2 = new QVBoxLayout;
        QHBoxLayout *settingsLayoutH = new QHBoxLayout;
        QHBoxLayout *LayoutHGroup1 = new QHBoxLayout;
        QHBoxLayout *settingsGeneralLayoutH = new QHBoxLayout;
        ctrl = new QLabel("Ctrl +");
        ctrl2 = new QLabel(" + ");
        ctrl3 = new QLabel(" + ");
        GroupBox1 = new QGroupBox(tr("Raccourcis"));
        GroupBox2 = new QGroupBox(tr("Autres"));
        ShortMedCombo1 = new QComboBox(this);
        ShortMedCombo2 = new QComboBox(this);
        ShortMedCombo3 = new QComboBox(this);
        TextEdit2 = new QTextEdit(this);
        CSVPath = new QLabel("Chemin du dossier\ndes fichiers CSV :", this);
        OpenDirCSVButton = new QPushButton("Ouvrir le dossier des fichiers CSV", this);
        OpenDirExeButton = new QPushButton("Ouvrir le dossier de l'éxecutable", this);
        AboutQt = new QPushButton("À Propos de Qt", this);
        TitleandIcon = new QLabel(this);
        Credits = new QLabel("Ce programme a été créé pour le CDI par Michel Durand.\nMerci à Mme Noiret pour l'idée de ce projet.\nL'image de fond d'écran a été\nprise sur : https://pxhere.com/fr/photo/1593135.\nCe programme a été créé avec Qt. Pour plus d'info :\n", this);
        TitleandIcon->setPixmap(QPixmap(":/Images/TitleWithIcon.png"));
        TitleandIcon->setFixedSize(326, 42);
        setFixedSize(421, 360);
        TextEdit2->setFixedSize(250, 100);
        AboutTab = new QWidget;
        GeneralTab = new QWidget;
        OKButton = new QPushButton("OK", this);
        OKButton->setFixedWidth(75);
        ApplyButton = new QPushButton("Appliquer", this);
        ApplyButton->setFixedWidth(75);
        RestartButton = new QPushButton("Redémarer", this);
        RestartButton->setFixedWidth(75);
        CreditsShort = new QLabel("Par Michel Durand", this);
        tabWidget = new QTabWidget(this);
        tabWidget->addTab(GeneralTab, "General");
        tabWidget->addTab(AboutTab, "About");
        setLayout(settingsLayout);
        settingsLayout->addWidget(tabWidget);
        settingsLayout->addLayout(settingsLayoutH);
        settingsLayoutH->addWidget(CreditsShort);
        settingsLayoutH->addWidget(OKButton);
        settingsLayoutH->addWidget(RestartButton);
        settingsLayoutH->addWidget(ApplyButton);

        GeneralTab->setLayout(settingsGeneralLayout);
        AboutTab->setLayout(settingsAboutLayout);
        settingsAboutLayout->addWidget(TitleandIcon);
        settingsAboutLayout->addWidget(Credits);
        settingsAboutLayout->addWidget(AboutQt);
        LayoutGroup2->addLayout(settingsGeneralLayoutH);
        LayoutGroup2->addWidget(OpenDirCSVButton);
        LayoutGroup2->addWidget(OpenDirExeButton);
        settingsGeneralLayoutH->addWidget(CSVPath);
        settingsGeneralLayoutH->addWidget(TextEdit2);
        settingsGeneralLayout->addWidget(GroupBox1);
        settingsGeneralLayout->addWidget(GroupBox2);
        LayoutHGroup1->addWidget(ctrl);
        LayoutHGroup1->addWidget(ShortMedCombo1, 93);
        LayoutHGroup1->addWidget(ctrl2);
        LayoutHGroup1->addWidget(ShortMedCombo2, 93);
        LayoutHGroup1->addWidget(ctrl3);
        LayoutHGroup1->addWidget(ShortMedCombo3, 93);
        GroupBox1->setLayout(LayoutHGroup1);
        GroupBox2->setLayout(LayoutGroup2);

        ResetMedCombo();
        ResetFieldsSettings();
        setWindowTitle("Dev Mode");
        setWindowIcon(QIcon(":/Images/Icon.png"));
    }

    void connectButtons()
    {
        QObject::connect(OKButton, SIGNAL(clicked()), this, SLOT(quit()));
        QObject::connect(ApplyButton, SIGNAL(clicked()), this, SLOT(apply()));
        QObject::connect(RestartButton, SIGNAL(clicked()), this, SLOT(restart()));
        QObject::connect(OpenDirCSVButton, SIGNAL(clicked()), this, SLOT(OpenCSVFile()));
        QObject::connect(OpenDirExeButton, SIGNAL(clicked()), this, SLOT(OpenExeFile()));
        QObject::connect(AboutQt, SIGNAL(clicked()), qApp, SLOT(aboutQt()));
    }

    void ResetMedCombo()
    {
        ShortMedCombo1->clear();
        ShortMedCombo1->clear();
        ShortMedCombo1->clear();

        ShortMedCombo1->addItem("A");
        ShortMedCombo1->addItem("B");
        ShortMedCombo1->addItem("C");
        ShortMedCombo1->addItem("D");
        ShortMedCombo1->addItem("E");
        ShortMedCombo1->addItem("F");
        ShortMedCombo1->addItem("G");
        ShortMedCombo1->addItem("H");
        ShortMedCombo1->addItem("I");
        ShortMedCombo1->addItem("J");
        ShortMedCombo1->addItem("K");
        ShortMedCombo1->addItem("L");
        ShortMedCombo1->addItem("M");
        ShortMedCombo1->addItem("N");
        ShortMedCombo1->addItem("O");
        ShortMedCombo1->addItem("P");
        ShortMedCombo1->addItem("Q");
        ShortMedCombo1->addItem("R");
        ShortMedCombo1->addItem("S");
        ShortMedCombo1->addItem("T");
        ShortMedCombo1->addItem("U");
        ShortMedCombo1->addItem("V");
        ShortMedCombo1->addItem("W");
        ShortMedCombo1->addItem("X");
        ShortMedCombo1->addItem("Y");
        ShortMedCombo1->addItem("Z");

        ShortMedCombo2->addItem("A");
        ShortMedCombo2->addItem("B");
        ShortMedCombo2->addItem("C");
        ShortMedCombo2->addItem("D");
        ShortMedCombo2->addItem("E");
        ShortMedCombo2->addItem("F");
        ShortMedCombo2->addItem("G");
        ShortMedCombo2->addItem("H");
        ShortMedCombo2->addItem("I");
        ShortMedCombo2->addItem("J");
        ShortMedCombo2->addItem("K");
        ShortMedCombo2->addItem("L");
        ShortMedCombo2->addItem("M");
        ShortMedCombo2->addItem("N");
        ShortMedCombo2->addItem("O");
        ShortMedCombo2->addItem("P");
        ShortMedCombo2->addItem("Q");
        ShortMedCombo2->addItem("R");
        ShortMedCombo2->addItem("S");
        ShortMedCombo2->addItem("T");
        ShortMedCombo2->addItem("U");
        ShortMedCombo2->addItem("V");
        ShortMedCombo2->addItem("W");
        ShortMedCombo2->addItem("X");
        ShortMedCombo2->addItem("Y");
        ShortMedCombo2->addItem("Z");

        ShortMedCombo3->addItem("A");
        ShortMedCombo3->addItem("B");
        ShortMedCombo3->addItem("C");
        ShortMedCombo3->addItem("D");
        ShortMedCombo3->addItem("E");
        ShortMedCombo3->addItem("F");
        ShortMedCombo3->addItem("G");
        ShortMedCombo3->addItem("H");
        ShortMedCombo3->addItem("I");
        ShortMedCombo3->addItem("J");
        ShortMedCombo3->addItem("K");
        ShortMedCombo3->addItem("L");
        ShortMedCombo3->addItem("M");
        ShortMedCombo3->addItem("N");
        ShortMedCombo3->addItem("O");
        ShortMedCombo3->addItem("P");
        ShortMedCombo3->addItem("Q");
        ShortMedCombo3->addItem("R");
        ShortMedCombo3->addItem("S");
        ShortMedCombo3->addItem("T");
        ShortMedCombo3->addItem("U");
        ShortMedCombo3->addItem("V");
        ShortMedCombo3->addItem("W");
        ShortMedCombo3->addItem("X");
        ShortMedCombo3->addItem("Y");
        ShortMedCombo3->addItem("Z");

        QFile FileSettings("Settings/file.txt");
        FileSettings.open(QIODevice::ReadOnly);
        QByteArray data;
        data = FileSettings.readAll();
        FileSettings.close();
        QString data2 = QString("%1").arg(data);
        ShortMedCombo1->setCurrentText(data2[5]);
        ShortMedCombo2->setCurrentText(data2[13]);
        ShortMedCombo3->setCurrentText(data2[21]);
    }

    void applyFunc()
    {
        QFile FileSettings("Settings/file.txt");
        if(FileSettings.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream stream(&FileSettings);
            QString gkjgfkugdkufgkhfkh = QString("Ctrl+%1, Ctrl+%2, Ctrl+%3").arg(ShortMedCombo1->currentText(), ShortMedCombo2->currentText(), ShortMedCombo3->currentText());
            stream<<gkjgfkugdkufgkhfkh;
            FileSettings.close();
        }
        else
        {
            mkdir("Settings");
            creat("Settings/file.txt", 0777);
            FileSettings.open(QIODevice::ReadWrite | QIODevice::Text);
            QTextStream stream(&FileSettings);
            QString gkjgfkugdkufgkhfkh = QString("Ctrl+%1, Ctrl+%2, Ctrl+%3").arg(ShortMedCombo1->currentText(), ShortMedCombo2->currentText(), ShortMedCombo3->currentText());
            stream<<gkjgfkugdkufgkhfkh;
            FileSettings.close();
        }
    }

private slots:
    void apply()
    {
        applyFunc();
    }

    void quit()
    {
        applyFunc();
        hide();
    }

    void restart()
    {
        applyFunc();
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
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
