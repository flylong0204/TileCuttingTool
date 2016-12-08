#ifndef CALDATAGDAL_H
#define CALDATAGDAL_H

#include "CalTools.h"
#include <gdal_priv.h>

#include <QString>

class CalDataGDAL
{
public:
    CalDataGDAL( const QString filePath );
    ~CalDataGDAL();
    CalExtent getExtent();
    bool getLayering ( int *min, int* max);
private:
    GDALDataset *_poDataset;
    double _xResolution;
    double _yResolution;
};

#endif // CALDATAGDAL_H
