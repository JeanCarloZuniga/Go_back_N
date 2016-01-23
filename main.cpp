#include "mainwindow.h"
#include <QApplication>
#include "cliente.h"

static MainWindow *ventana;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ventana = new MainWindow();
    ventana->show();

    return a.exec();
}
