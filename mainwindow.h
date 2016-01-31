#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "servidor.h"
#include "cliente.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    Servidor *servidor;
    Cliente *cliente;
};

#endif // MAINWINDOW_H
