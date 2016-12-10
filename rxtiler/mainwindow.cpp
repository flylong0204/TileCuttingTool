#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "datasourcegdal.h"
#include "datasourcetiles.h"
#include "Extent.h"
#include "TileKey.h"

#include <qDebug>
#include <QFileDialog>
#include <QProcess>
#include <qmath.h>

#include "osgDB/ReadFile"

#include "ProgressBar.h"

mainwindow::mainwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);

//    _source_in = new rxtiler::DataSourceGDAL("");
//    _source_out = new rxtiler::DataSourceTiles;
    _datasourceTiles=new rxtiler::DataSourceTiles();


}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::on_OpenFile_clicked()
{
    if( ui->FileType1->isChecked() && !ui->FileType2->isChecked() )
    {
        //影像
        QString filename = QFileDialog::getOpenFileName(this,
                           tr("选择图像"),
                           "",
                           tr("Images (*.tif *.tiff)")); //选择路径
        if( filename.isEmpty() )
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

void mainwindow::on_Calculation_clicked()
{
    if(!ui->FilePathshow->text().isEmpty())
    {
        dataSource = new rxtiler::DataSourceGDAL( ui->FilePathshow->text());

        pExtent = dataSource->getExtent();
        ui->Left->setText(QString::number(pExtent.left,10,6));
        ui->Top->setText(QString::number(pExtent.top,10,6));
        ui->Right->setText(QString::number(pExtent.right,10,6));
        ui->Bottom->setText(QString::number(pExtent.bottom,10,6));
        int minLevel;
        int maxLevel;
        rxtiler::TileOption tileOption;
        if(dataSource->computerLevels(&tileOption,&minLevel,&maxLevel)){
            ui->txtMinLevel->setText(QString::number(minLevel));
            ui->txtMaxLevel->setText(QString::number(maxLevel));
        }
    }
}

void mainwindow::on_SaveFile_clicked()
{
    QString file_dir = QFileDialog::getExistingDirectory(this,
                   "选择保存路径",
                   "./",
                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if( file_dir.isEmpty() )
    {
        return;
    }
    else
    {
        ui->SavePathShow->setText( file_dir );
    }

    //将选择的目录作为保存图片的一个根目录
    _datasourceTiles->setRootDir(file_dir);
    _datasourceTiles->setNoDataColor(osg::Vec4(0,0,0,1));;
}

void mainwindow::on_structure_clicked()
{
    if(ui->SavePathShow->text().isEmpty() || ui->FilePathshow->text().isEmpty())
        return;
    if(ui->txtMinLevel->text().toInt() >= ui->txtMaxLevel->text().toInt())
        return;
    rxtiler::Extent nowTif( ui->Left->text().toDouble(),
                            ui->Right->text().toDouble(),
                            ui->Bottom->text().toDouble(),
                            ui->Top->text().toDouble());
    dataSource->setNowLrbt(nowTif);

    int lodMin = ui->txtMinLevel->text().toInt();
    int lodMax = ui->txtMaxLevel->text().toInt();
    //图像
    if( ui->FileType1->isChecked() && !ui->FileType2->isChecked() )
    {
        for(int lod = lodMin; lod <= lodMax; lod++)
        {
            int xMin = titleoption.getTileX(lod,ui->Left->text().toDouble());
            int xMax = titleoption.getTileX(lod,ui->Right->text().toDouble());
            int yMin = titleoption.getTileY(lod,ui->Bottom->text().toDouble());
            int yMax = titleoption.getTileY(lod,ui->Top->text().toDouble());

            for(int x = xMin; x <= xMax; x++)
            {
                for(int y = yMin; y <= yMax; y++)
                {
                    key.lod = lod;
                    key.x = x;
                    key.y = y;
                    tile.left = -180 + 36.0/qPow(2,key.lod)*(key.x);
                    tile.right = tile.left + 36.0/qPow(2,key.lod);
                    tile.bottom = -90 + 36.0/qPow(2,key.lod)*(key.y);
                    tile.top = tile.bottom + 36.0/qPow(2,key.lod);
                    _datasourceTiles->saveImage(key,dataSource->getImage(key,tile));
                }
            }
        }
    }
    //DEM
    if( !ui->FileType1->isChecked() && ui->FileType2->isChecked() )
    {
        for(int lod = lodMin; lod <= lodMax; lod++)
        {
            int xMin = titleoption.getTileX(lod,ui->Left->text().toDouble());
            int xMax = titleoption.getTileX(lod,ui->Right->text().toDouble());
            int yMin = titleoption.getTileY(lod,ui->Bottom->text().toDouble());
            int yMax = titleoption.getTileY(lod,ui->Top->text().toDouble());

            for(int x = xMin; x <= xMax; x++)
            {
                for(int y = yMin; y <= yMax; y++)
                {
                    key.lod = lod;
                    key.x = x;
                    key.y = y;
                    tile.left = -180 + 36.0/qPow(2,key.lod)*(key.x);
                    tile.right = tile.left + 36.0/qPow(2,key.lod);
                    tile.bottom = -90 + 36.0/qPow(2,key.lod)*(key.y);
                    tile.top = tile.bottom + 36.0/qPow(2,key.lod);
                    //_datasourceTiles->saveDEM(key,dataSource->getDEM(key,tile));
                }
            }
        }
    }
}

void mainwindow::on_close_clicked()
{
    this->close();
}
