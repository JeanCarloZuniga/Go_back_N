#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "servidor.h"
#include "cliente.h"
#include "intermediario.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Servidor *servidor;
    Cliente *cliente;
    Intermediario *intermediario;
};

#endif // MAINWINDOW_H
