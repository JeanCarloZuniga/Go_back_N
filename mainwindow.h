#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void a();

private slots:
    void on_pushButton_clicked();
    void salude_cliente();
    void salude_server();
    void on_seleccionarArchivoBTN_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
