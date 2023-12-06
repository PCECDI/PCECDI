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
        QMessageBox *message = new QMessageBox;
        message->setWindowTitle("Bienvenue");
        message->setWindowIcon(QIcon(":/Images/Icon.png"));
        message->setText("Bienvenue dans PCECDI !\nPCECDI a détécté que vous l'allumer pour la première fois.\nCe programme contient une fenêtre d'outils. Elle est désactivée par défaut, si vous voulez l'activer le raccourcis clavier par défaut est : Ctrl+M, Ctrl+E, Ctrl+D.\nVous pourrez le changer en y accédant.");
        message->show();
    }
    return app.exec();
}
