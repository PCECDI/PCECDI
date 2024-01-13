#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QMessageBox>
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
    if(MainUI.New == 1)
    {
        MainUI.Welcome();
    }
    return app.exec();
}

