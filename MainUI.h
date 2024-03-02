#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QTextEdit>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDate>
#include <QInputDialog>
#include <QIcon>
#include <QTime>
#include <QDateTime>
#include <QPalette>
#include <QShortcut>
#include <QStatusBar>
#include <QComboBox>
#include <fcntl.h>
#include "SettingsUI.h"
#include "XmlReader.h"
#define VersionInfoText "CDIHP5MED_v6.5"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow()
    {
#ifndef VersionInfoText
        qApp->quit();
#endif
        setupUI();
        connectButtons();
    }
    ~MainWindow()
    {

    }
    int New;

    void Welcome()
    {
        QMessageBox *message = new QMessageBox;
        message->setWindowTitle(tr("Welcome"));
        message->setWindowIcon(QIcon(":/Images/Icon.png"));
        message->setText(tr("Welcome to PCECDI!\nPCECDI has detected that you are turning it on for the first time.\nThis program is used to classify students coming to the Cdi.\nTo register you must enter a name, a first name, a class and a reason. \nTo add reasons please consult the \"Choises.txt\" file contained in the \"Settings\" folder."));
        message->show();
    }

    SettingsUI settings = SettingsUI(VersionInfoText);

private:
    QLineEdit *NomLineEdit;
    QLineEdit *PrenomLineEdit;
    QLineEdit *ClasseLineEdit;
    QShortcut *shortcutMed;
    QShortcut *shortcutFlemme;
    QComboBox *ComboBox1;
    QTextEdit *TextEdit1;
    QPushButton *QuitButton;
    QPushButton *ApplyButton;
    QPushButton *ToolsButton;
    QScreen *screen;
    QLabel *Spacer;
    QLabel *Title;
    int ToolsWidowStatus;

    void setupUI()
    {
        New = 0;
        screen = QGuiApplication::primaryScreen();
        QWidget *window = new QWidget;
        QIcon progIcon(":/Images/Icon.png");
        NomLineEdit = new QLineEdit(this);
        PrenomLineEdit = new QLineEdit(this);
        ClasseLineEdit = new QLineEdit(this);
        TextEdit1 = new QTextEdit(this);
        QuitButton = new QPushButton(tr("Quit"), this);
        ApplyButton = new QPushButton(tr("Save"), this);
        ToolsButton = new QPushButton(tr("Tools"), this);
        shortcutFlemme = new QShortcut(QKeySequence("Ctrl+M, Ctrl+I, Ctrl+C, Ctrl+H"), this);
        ComboBox1 = new QComboBox(this);
        Spacer = new QLabel(this);
        Title = new QLabel(this);
        QPixmap SpacerImage(":/Images/Spacer.png");
        QPixmap TitleImage(":/Images/Title.png");
        Spacer->setPixmap(SpacerImage);
        Title->setPixmap(TitleImage);
        NomLineEdit->setFixedWidth(300);
        PrenomLineEdit->setFixedWidth(300);
        ClasseLineEdit->setFixedWidth(300);
        ComboBox1->setFixedWidth(300);
        QuitButton->setFixedWidth(148);
        ApplyButton->setFixedWidth(148);
        ToolsButton->setFixedWidth(300);
        Spacer->setFixedSize(300, 2);
        Title->setFixedSize(342, 71);
        TextEdit1->setFixedSize(800, 150);

        ToolsWidowStatus = 0;
        ResetFields();
        TextEdit1->setReadOnly(1);
        TextEdit1->setAlignment(Qt::AlignCenter);
        TextEdit1->append(tr("Welcome to PCECDI!\nEnter your name, first name, class and finally a reason to be registered.\n|------------------------ -------------------------------------------------- --------------|\n"));
        TextEdit1->setAlignment(Qt::AlignLeft);

        QVBoxLayout *layout = new QVBoxLayout(window);
        QVBoxLayout *Vlayout = new QVBoxLayout;
        QHBoxLayout *Hlayout = new QHBoxLayout;
        QHBoxLayout *Hlayout2 = new QHBoxLayout;
        QHBoxLayout *Hlayout3 = new QHBoxLayout;
        QHBoxLayout *Hlayout4 = new QHBoxLayout;

        Hlayout3->setSpacing(0);
        Hlayout4->setSpacing(0);

        layout->addLayout(Hlayout3);
        layout->addLayout(Hlayout);
        layout->addLayout(Hlayout4);

        Hlayout4->addWidget(TextEdit1);
        Hlayout3->addWidget(Title);

        Hlayout->addLayout(Vlayout);
        Vlayout->addWidget(NomLineEdit);
        Vlayout->addWidget(PrenomLineEdit);
        Vlayout->addWidget(ClasseLineEdit);
        Vlayout->addWidget(ComboBox1);
        Vlayout->addLayout(Hlayout2);
        Hlayout2->addWidget(ApplyButton);
        Hlayout2->addWidget(QuitButton);
        Vlayout->addWidget(Spacer);
        Vlayout->addWidget(ToolsButton);
        setCentralWidget(window);
        setWindowIcon(progIcon);
        setWindowTitle("PCECDI");
        setMinimumSize(820, 450);

        QPixmap bkgnd(":/Images/WallPaper.jpg");
        bkgnd = bkgnd.scaled(screen->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }

    void connectButtons()
    {
        QObject::connect(QuitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
        QObject::connect(ApplyButton, SIGNAL(clicked()), this, SLOT(Register()));
        QObject::connect(ToolsButton, SIGNAL(clicked()), this, SLOT(LaunchSettingsUI()));
        QObject::connect(shortcutFlemme, SIGNAL(activated()), this, SLOT(Mich()));
    }

    void RebootRegister()
    {
        Register();
    }

    void ResetFields()
    {
        NomLineEdit->setText("");
        PrenomLineEdit->setText("");
        ClasseLineEdit->setText("");
        ComboBox1->clear();
        ComboBox1->setPlaceholderText(tr("I come to the CDI to..."));
        NomLineEdit->setPlaceholderText(tr("Name :"));
        PrenomLineEdit->setPlaceholderText(tr("First name :"));
        ClasseLineEdit->setPlaceholderText(tr("Class :"));

        QStringList ChoicesList = XmlReader("Settings/settings.xml").getTextFromChoices();
        for(int i = 0; i < ChoicesList.size(); i++) {
            ComboBox1->addItem(ChoicesList.at(i));
        }
    }

    void RebootResetFields()
    {
        ResetFields();
    }

private slots:
    void Mich()
    {
        NomLineEdit->setText("Durand");
        PrenomLineEdit->setText("Michel");
        ClasseLineEdit->setText("4C");
        ComboBox1->setCurrentIndex(13);
    }

    void LaunchSettingsUI()
    {
        settings.move(screen->geometry().width()/2 - settings.width()/2, screen->geometry().height()/2.5 - settings.height()/2);
        settings.ResetFieldsSettings();
        settings.show();
    }

    void Register()
    {
        bool ok;

        QDateTime *DateWithTime = new QDateTime(QDateTime::currentDateTime());
        QTime ProgTime = DateWithTime->time();
        QDate ProgDate = DateWithTime->date();

        QString CSVFileName = QString("%1 %2.csv").arg(ProgDate.year(), 4, 10, QChar('0')).arg(ProgDate.month(), 2, 10, QChar('0'));
        QString ProgDate2 = QString("%1/%2/%3").arg(ProgDate.day(), 2, 10, QChar('0')).arg(ProgDate.month(), 2, 10, QChar('0')).arg(ProgDate.year(), 4, 10, QChar('0'));
        QString ProgTime2;

        int compsec = ProgTime.second();
        int compheure = ProgTime.hour();
        int compmin = ProgTime.minute();

        switch (compheure)
        {
            case 7:
                ProgTime2 = QString("7:20 - 8:20");
                break;

            case 8:
                if(compmin < 20) ProgTime2 = QString("7:20 - 8:20");
                if(compmin >= 20) ProgTime2 = QString("8:20 - 9:20");
                break;

            case 9:
                if(compmin < 20) ProgTime2 = QString("8:20 - 9:20");
                if(compmin >= 20) ProgTime2 = QString("9:20 - 10:20");
                break;

            case 10:
                if(compmin < 20) ProgTime2 = QString("9:20 - 10:20");
                if(compmin >= 35) ProgTime2 = QString("10:20 - 11:35");
                break;

            case 11:
                if(compmin < 35) ProgTime2 = QString("10:20 - 11:35");
                if(compmin >= 35) ProgTime2 = QString("11:35 - 12:35");
                break;

            case 12:
                if(compmin < 35) ProgTime2 = QString("11:35 - 12:35");
                if(compmin >= 35) ProgTime2 = QString("12:35 - 13:00");
                break;

            default:
                ProgTime2 = QString("%1:00 - %2:00").arg(compheure).arg(compheure+1);
                break;
        }

        QString nom = NomLineEdit->text();
        QString prenom = PrenomLineEdit->text();
        QString classe = ClasseLineEdit->text();
        QString raison = ComboBox1->currentText();

        nom.remove(",");
        prenom.remove(",");
        classe.remove(",");
        nom.remove(";");
        prenom.remove(";");
        classe.remove(";");

        QFile CSVFile(QDir::currentPath() + "/CSVFiles/" + CSVFileName);
        if(!CSVFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            mkdir("CSVFiles");
            creat("CSVFiles/"+CSVFileName.toUtf8(), 0777);
            CSVFile.open(QIODevice::ReadWrite | QIODevice::Text);
            QTextStream hellostream(&CSVFile);
            QString line = "Dates :,Heures :,Noms :,Prénoms :,Classes :, Raisons :\n";
            hellostream<<line;
            CSVFile.close();
            RebootRegister();
        }
        else
        {
            if(nom == "" || prenom == "" || classe == "" || raison == "" || classe.size() != 2)
            {
                if(nom == "") NomLineEdit->setPlaceholderText(tr("Empty..."));
                if(prenom == "") PrenomLineEdit->setPlaceholderText(tr("Empty..."));
                if(classe == "" || classe.size() != 2)
                {
                    ClasseLineEdit->setText("");
                    ClasseLineEdit->setPlaceholderText(tr("The class must be a number then a letter."));
                }
                if(raison == "") ComboBox1->setPlaceholderText(tr("Please choose an option..."));
            }
            else
            {
                if(raison == "Travailler sur les postes" || raison == "Se connecter à l'ENT")
                {
                    int numposte = QInputDialog::getInt(this, tr("Computer number"), tr("Enter your computer number:"), 1, 1, 9, 1, &ok);
                    if (ok && !numposte == 0) raison = QString("%1 - poste : %2").arg(raison).arg(numposte);
                    else return;
                }

                CSVFile.close();
                CSVFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
                QString line = ProgDate2 + "," + ProgTime2 + "," + nom + "," + prenom + "," + classe + "," + raison + "\n";
                QString heurelog = QString("%1:%2:%3").arg(compheure, 2, 10, QChar('0')).arg(compmin, 2, 10, QChar('0')).arg(compsec, 2, 10, QChar('0'));
                QTextStream hellostream(&CSVFile);
                hellostream<<line;
                CSVFile.close();
                TextEdit1->append(QString(tr("[PCECDI] [%1] Student %2 %3 in %4 to %5, on %6. Who came for %7 successfully registered !")).arg(heurelog, nom, prenom, classe, ProgTime2, ProgDate2, raison));
                ResetFields();
            }
        }
    }
};
#endif // MAINWINDOW_H
