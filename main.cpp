#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QProcess>
#include <QTranslator>
#include <QMessageBox>
#include <QPainter>
#include <windows.h>
#include <QDomElement>
#include "MainUI.h"
#include "XmlReader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setStyle("windowsvista");

    QString Lang;
    Lang = XmlReader("Settings/settings.xml").lireContenuBalise("settings", "language");

    QTranslator translator;
    if (translator.load(QLocale(Lang), "PCECDI", "_", "translations") && Lang != "en")
        QApplication::installTranslator(&translator);
    MainWindow MainUI;

    if(Lang == "fr") MainUI.settings.LanguageCombo->setCurrentIndex(0);
    if(Lang == "en") MainUI.settings.LanguageCombo->setCurrentIndex(1);
    if(Lang == "de") MainUI.settings.LanguageCombo->setCurrentIndex(2);
    if(Lang == "ru") MainUI.settings.LanguageCombo->setCurrentIndex(3);

    QImage image(":/Images/SplashScreen.png");
    QPainter painter(&image);
    QFont font("Verdana", 4.5);
    font.setItalic(1);
    painter.setFont(font);
    painter.setPen(QPen(Qt::white));
    painter.drawText(20, 120, QApplication::tr("A ( Very ) Small Program for the CDI !"));
    painter.drawText(20, 160, QApplication::tr("By TheGordonFreeman42"));
    painter.drawText(330, 160, "v6.5");

    QSplashScreen Splash;
    Splash.setPixmap(QPixmap::fromImage(image));
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

