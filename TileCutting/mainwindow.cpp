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
        _tile.setFilePath(filename);
        ui->Left->setText( QString::number( _tile.getLeft()) );
        ui->Right->setText( QString::number( _tile.getRight()) );
        ui->Top->setText( QString::number( _tile.getTop()) );
        ui->Bottom->setText( QString::number( _tile.getBottom()) );
        ui->txtMinLevel->setText( QString::number( _tile.getMinLayer()));
        ui->txtMaxLevel->setText( QString::number( _tile.getMaxLayer()));
        ui->band->setText( QString::number( _tile.getBand()));
        ui->pixelW->setText( QString::number( _tile.getPixelWidth() ));
        ui->pixelH->setText( QString::number( _tile.getPixelHeight() ));
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
    if(ui->SavePathShow->text().isEmpty() || ui->FilePathshow->text().isEmpty())
        return;
    if(ui->txtMinLevel->text().toInt() >= ui->txtMaxLevel->text().toInt())
        return;
    if(ui->Left->text().isEmpty() || ui->Right->text().isEmpty() || ui->Top->text().isEmpty() || ui->Bottom->text().isEmpty())
        return;
    if(ui->Left->text().toDouble() >= ui->Right->text().toDouble() || ui->Bottom->text().toDouble() >= ui->Top->text().toDouble() )
        return;
}

void MainWindow::on_close_clicked()
{
    this->close();
}
