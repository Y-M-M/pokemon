#include "mainwindow.h"
#include "pokemon.h"
#include "login.h"
#include "battlecontroller.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login login;
    login.show();
    if(login.exec() == QDialog::Accepted)
    {
        MainWindow w(0, &login);
        w.show();
        return a.exec();
    }
    else return 0;
}
