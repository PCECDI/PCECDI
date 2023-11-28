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
    QPixmap SplashScreen(":/Images/SplashScreen.png");
    Splash.setPixmap(SplashScreen);
    Splash.show();
    Sleep(3000);
    MainUI.showMaximized();
    Splash.finish(&MainUI);
    return app.exec();
}
