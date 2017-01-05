#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "TileCuttInfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_OpenFile_clicked();

    void on_SaveFile_clicked();

    void on_structure_clicked();

    void on_close_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
