#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Servidor *servidor = new Servidor;
    servidor->start();
    Cliente *cliente = new Cliente;
    cliente->start();
    cliente->conectar("127.0.0.1", 8888);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Funcion de muestra para ver cómo se harán las flechas para la interfaz cuando se envíen cosas,
 * Deberá recibir un argumento que indicará el número de paquete al que se le deben pintar las flechas
*/
void MainWindow::on_pushButton_clicked()
{
    limpiar_flechas(3);
    for(int i=0; i<24; i++)
    {
        ui->listWidget->item(3)->setText(ui->listWidget->item(3)->text().append("   -->"));
        delay();
    }
    limpiar_flechas(3);
}

/*
 * Hace un delay de 250 Msecs
*/
void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(250);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::limpiar_flechas(int indice)
{
    QChar letra = ui->listWidget->item(indice)->text().at(0);
    ui->listWidget->item(indice)->text().clear();
    ui->listWidget->item(indice)->setText(letra);
}

/*
    Se selecciona el archivo que se quiere descomponer y enviar en paquetes
*/
void MainWindow::on_seleccionarArchivoBTN_clicked()
{
    QString nombre = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "Text file (*.txt)");
    QFile file_for_reading(nombre);
    file_for_reading.open(QIODevice::ReadOnly);
    QTextStream text_stream_for_reading(&file_for_reading);
    QString contenido = text_stream_for_reading.readAll();
    file_for_reading.close();
    for(int indice=0; indice < contenido.length(); indice++)
    {
         ui->listWidget->addItem(contenido.at(indice));
    }
}
