#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //servidor = new Servidor(10001, 0);
    //servidor->start();

    //intermediario = new Intermediario(10000, 10001, 0.5, 0);
    //intermediario->start();

    cliente = new Cliente(1);
    cliente->start();
    cliente->conectar("127.0.0.1", 10001);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete servidor;
    delete cliente;
    delete intermediario;
}
