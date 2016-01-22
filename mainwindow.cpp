#include "mainwindow.h"
#include <QDebug>
#include "ui_mainwindow.h"
#include "cliente.h"
#include "servidor.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Cliente *cliente = new Cliente;
    Servidor *servidor = new Servidor;
    cliente->start();
    servidor->start();
    connect(cliente, SIGNAL(salude_cliente()), this, SLOT(salude_cliente()));
    connect(servidor, SIGNAL(salude_server()), this, SLOT(salude_server()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //qDebug() << "Me estriparon";
    //ui->label->setText("Cambiado");
}

void MainWindow::salude_cliente()
{
    //qDebug() << "ME HABLARON!!!!!!!!!!!!!!";
    ui->label_cliente->setText("Hola, soy el cliente");
}

void MainWindow::salude_server()
{
    ui->label_server->setText("Hola, soy el server");
}


void MainWindow::on_seleccionarArchivoBTN_clicked()
{
    QString nombre = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "All files (*.*);;Text file (*.txt)");
}
