#include "mainwindow.h"
#include <QApplication>
#include "cliente.h"

static MainWindow *ventana;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ventana = new MainWindow();
    ventana->show();
    //ventana->cliente->_start("127.0.0.1", 8888);

    return a.exec();
}
