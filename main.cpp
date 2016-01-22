#include "mainwindow.h"
#include <QApplication>
#include "cliente.h"

static MainWindow *ventana;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    ventana = new MainWindow();
    ventana->show();
/*
    Cliente cliente;
    cliente.start();
*/
    //ventana->a();





    //w.show();

    return a.exec();
}
