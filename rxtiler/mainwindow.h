#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "datasource.h"
#include "datasourcetiles.h"
#include "TileKey.h"
#include "datasourcegdal.h"

namespace Ui {
class mainwindow;
}

class mainwindow : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = 0);
    ~mainwindow();

    rxtiler::DataSourceTiles *_datasourceTiles;

private slots:
    void on_OpenFile_clicked();
    void on_Calculation_clicked();
    void on_SaveFile_clicked();
    void on_structure_clicked();
    void on_close_clicked();

private:
    Ui::mainwindow *ui;
    rxtiler::DataSource* _source_in;
    rxtiler::DataSource* _source_out;

    rxtiler::DataSourceGDAL *dataSource;
    rxtiler::Extent pExtent;
    rxtiler::TileOption titleoption;
    rxtiler::TileKey key;
    rxtiler::Extent tile;

};

#endif // MAINWINDOW_H
