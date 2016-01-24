#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "cliente.h"
#include "servidor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void delay(); //[Interfaz]:Retraso para cuando se corre en modo lento
    void limpiar_flechas(int); //[Interfaz]:Limpia las flechas de un paquete

private slots:
    void on_pushButton_clicked(); //[Prueba]:Es solo para prueba de flechas.
    void on_seleccionarArchivoBTN_clicked(); //[Interfaz]:Selecciona el archivo a enviar

private:
    Ui::MainWindow *ui;
    Servidor *servidor;
    Cliente *cliente;
};

#endif // MAINWINDOW_H
