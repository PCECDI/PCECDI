#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QProcess>
#include <QTranslator>
#include <QMessageBox>
#include <QPainter>
#include <windows.h>
#include "MainUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setStyle("windowsvista");
    QFile FichierChoix2("Settings/Language.txt");
    QString Lang;
    if(!FichierChoix2.open(QIODevice::ReadOnly))
    {
        QDir DossierSettings2("Settings");
        if(!DossierSettings2.exists()) mkdir("Settings");
        creat("Settings/Language.txt", 0777);
        FichierChoix2.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream FichierCroixStream2(&FichierChoix2);
        FichierCroixStream2<<"fr";
        Lang = "fr";
        FichierChoix2.close();
    }
    else
    {
        FichierChoix2.close();
        FichierChoix2.open(QIODevice::ReadOnly);
        QByteArray line = FichierChoix2.readLine();
        if(!line.startsWith("#") && line != "\r\n")
        {
            Lang = line;
        }
    }
    QTranslator translator;
    if (translator.load(QLocale(Lang), "PCECDI", "_", "translations") && Lang != "en")
        QApplication::installTranslator(&translator);
    MainWindow MainUI;
    if(Lang == "fr")
    {
        MainUI.settings.LanguageCombo->setCurrentIndex(0);
    }
    if(Lang == "en")
    {
        MainUI.settings.LanguageCombo->setCurrentIndex(1);
    }
    if(Lang == "de")
    {
        MainUI.settings.LanguageCombo->setCurrentIndex(2);
    }
    if(Lang == "ru")
    {
        MainUI.settings.LanguageCombo->setCurrentIndex(3);
    }

    QImage image(":/Images/SplashScreen.png");
    QPainter painter(&image);
    QFont font("Verdana", 4.5);
    font.setItalic(1);
    painter.setFont(font);
    painter.setPen(QPen(Qt::white));
    painter.drawText(18, 120, QApplication::tr("A ( Very ) Small Program for the CDI !"));
    painter.drawText(18, 160, QApplication::tr("By TheGordonFreeman42"));
    painter.drawText(445, 160, "v6.5");
    QPixmap pixmap = QPixmap::fromImage(image);

    QSplashScreen Splash;
    Splash.setPixmap(pixmap);
    Splash.show();
    Sleep(3000);
    MainUI.showMaximized();
    Splash.finish(&MainUI);
    if(MainUI.New == 1)
    {
        MainUI.Welcome();
    }
    return app.exec();
}

