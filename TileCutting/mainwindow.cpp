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
            _pDataGDAL = new CalDataGDAL( filename );
            _pExtent = _pDataGDAL->getExtent();
            ui->Left->setText(QString::number(_pExtent.getLeft(),10,6));
            ui->Top->setText(QString::number(_pExtent.getTop(),10,6));
            ui->Right->setText(QString::number(_pExtent.getRight(),10,6));
            ui->Bottom->setText(QString::number(_pExtent.getBottom(),10,6));
            int minLevel;
            int maxLevel;
            if(_pDataGDAL->getLayering(&minLevel,&maxLevel))
            {
                ui->txtMinLevel->setText(QString::number(minLevel));
                ui->txtMaxLevel->setText(QString::number(maxLevel));
            }
            delete _pDataGDAL;
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
    if(ui->SavePathShow->text().isEmpty() || ui->FilePathshow->text().isEmpty())
        return;
    if(ui->Left->text().isEmpty() || ui->Right->text().isEmpty() || ui->Top->text().isEmpty() || ui->Bottom->text().isEmpty())
        return;
    if(ui->Left->text().toDouble() > ui->Right->text().toDouble() || ui->Top->text().toDouble() < ui->Bottom->text().toDouble())
        return;
    if(ui->txtMinLevel->text().isEmpty()|| ui->txtMaxLevel->text().isEmpty())
        return;
    if(ui->txtMinLevel->text().toInt() >= ui->txtMaxLevel->text().toInt())
        return;

    CalExtent nowExtent(ui->Top->text().toDouble(),ui->Bottom->text().toDouble(),
                        ui->Left->text().toDouble(),ui->Right->text().toDouble());
    int lodMin = ui->txtMinLevel->text().toInt();
    int lodMax = ui->txtMaxLevel->text().toInt();
    for(int lod = lodMin; lod <= lodMax; lod++)
    {

    }
}
