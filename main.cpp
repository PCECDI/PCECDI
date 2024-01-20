#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QProcess>
#include <QMessageBox>
#include <QTimer>
#include <windows.h>
#include "MainUI.h"
#include "Updater.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Updater updater;

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

    updater.show();
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&updater]() {updater.LaunchUpdates();});
    timer.setSingleShot(1);
    timer.start(500);
    return app.exec();
}

