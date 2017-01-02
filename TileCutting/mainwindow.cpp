#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenFile_clicked()
{
    if( ui->FileType1->isChecked() && !ui->FileType2->isChecked() )
    {
        //影像
        QString filename = QFileDialog::getOpenFileName(this,
                           tr("选择图像"),
                           "",
                           tr("Images (*.tif *.TIF *.tiff *.TIFF)")); //选择路径
        if( filename.toDouble() )
        {
            return;
        }
        else
        {
            ui->FilePathshow->setText( filename );
        }
    }
    if( !ui->FileType1->isChecked() && ui->FileType2->isChecked() )
    {
        //DEM
    }
}

void MainWindow::on_SaveFile_clicked()
{
    QString file_dir = QFileDialog::getExistingDirectory(this,
                   "选择保存路径",
                   "./",
                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if( file_dir.toDouble() )
    {
        return;
    }
    else
    {
        ui->SavePathShow->setText( file_dir );
    }
}

void MainWindow::on_structure_clicked()
{

}

void MainWindow::on_close_clicked()
{
    this->close();
}
