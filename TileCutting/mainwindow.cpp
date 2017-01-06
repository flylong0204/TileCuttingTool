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
    //影像和DEM一样
    QString filename = QFileDialog::getOpenFileName(this,
                       tr("选择图像"),
                       "",
                       tr("Images (*.tif *.TIF *.tiff *.TIFF)")); //选择路径
    if( filename.isEmpty() )
    {
        return;
    }
    else
    {
        ui->FilePathshow->setText( filename );
        _tileCuttCore.setSource(filename);
        ui->Left->setText( QString::number( _tileCuttCore.getInfo().getLeft()) );
        ui->Right->setText( QString::number( _tileCuttCore.getInfo().getRight()) );
        ui->Top->setText( QString::number( _tileCuttCore.getInfo().getTop()) );
        ui->Bottom->setText( QString::number( _tileCuttCore.getInfo().getBottom()) );
        ui->txtMinLevel->setText( QString::number( _tileCuttCore.getInfo().getMinLayer()));
        ui->txtMaxLevel->setText( QString::number( _tileCuttCore.getInfo().getMaxLayer()));
        ui->band->setText( QString::number( _tileCuttCore.getBand()));
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
    qDebug() << (TileCuttInfo(1.111100001111,2,3,4,0,1) == TileCuttInfo(1.111100001111,2,3,4,0,1));
}

void MainWindow::on_close_clicked()
{
    this->close();
}
