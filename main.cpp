#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <windows.h>
#include "MainUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow MainUI;
    QSplashScreen Splash;
    Splash.setPixmap(QPixmap(":/Images/SplashScreen.png"));
    Splash.show();
    Sleep(3000);
    MainUI.showMaximized();
    Splash.finish(&MainUI);
    return app.exec();
}
