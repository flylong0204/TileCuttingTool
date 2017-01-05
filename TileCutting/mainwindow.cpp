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
        if( filename.toFloat() )
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
    if( file_dir.toFloat() )
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
    qDebug() << (TileCuttInfo(2,2,3,4) == TileCuttInfo(1,2,3,4));
}

void MainWindow::on_close_clicked()
{
    this->close();
}
