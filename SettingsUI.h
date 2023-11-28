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
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QScreen>
#include <QHBoxLayout>
#include <QDir>

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
    }

private:
    QWidget *GeneralTab;
    QWidget *AboutTab;
    QTabWidget *tabWidget;
    QLabel *CreditsShort;
    QLabel *CSVPath;
    QPushButton *OKButton;
    QTextEdit *TextEdit2;

    void setupUI()
    {
        QVBoxLayout *settingsLayout = new QVBoxLayout;
        QVBoxLayout *settingsGeneralLayout = new QVBoxLayout;
        QHBoxLayout *settingsLayoutH = new QHBoxLayout;
        QHBoxLayout *settingsGeneralLayoutH = new QHBoxLayout;
        TextEdit2 = new QTextEdit(this);
        CSVPath = new QLabel("Chemin du dossier\ndes fichiers CSV :", this);
        TextEdit2->setFixedSize(250, 100);
        AboutTab = new QWidget;
        GeneralTab = new QWidget;
        OKButton = new QPushButton("OK", this);
        OKButton->setFixedWidth(75);
        CreditsShort = new QLabel("Par Michel Durand", this);
        tabWidget = new QTabWidget(this);
        tabWidget->addTab(GeneralTab, "General");
        tabWidget->addTab(AboutTab, "About");
        setLayout(settingsLayout);
        settingsLayout->addWidget(tabWidget);
        settingsLayout->addLayout(settingsLayoutH);
        settingsLayoutH->addWidget(CreditsShort);
        settingsLayoutH->addWidget(OKButton);

        GeneralTab->setLayout(settingsGeneralLayout);
        settingsGeneralLayout->addLayout(settingsGeneralLayoutH);
        settingsGeneralLayoutH->addWidget(CSVPath);
        settingsGeneralLayoutH->addWidget(TextEdit2);

        ResetFieldsSettings();
        setWindowTitle("Dev Mode");
        setFixedSize(400, 300);
    }

    void connectButtons()
    {
        QObject::connect(OKButton, SIGNAL(clicked()), this, SLOT(quit()));
    }

private slots:
    void quit()
    {
        hide();
    }
};
#endif // MAINSETTINGS_H
