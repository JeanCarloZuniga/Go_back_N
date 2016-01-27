#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    servidor = new Servidor(8888);
    servidor->start();
    cliente = new Cliente;
    cliente->start();
    cliente->conectar("127.0.0.1", 8888);
}

MainWindow::~MainWindow()
{
    delete ui;
}
