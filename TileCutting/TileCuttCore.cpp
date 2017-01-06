#include "TileCuttCore.h"

TileCuttCore::TileCuttCore() :
    _source(""),
    _left(0),
    _right(0),
    _top(0),
    _bottom(0),
    _minHierarchy(0),
    _maxHierarchy(0)
{
    GDALAllRegister();//注册驱动
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");//支持中文路径
}

TileCuttCore::~TileCuttCore()
{
    if( _dataset != NULL )
    {
        delete _dataset;
        _dataset = NULL;
    }
}

void TileCuttCore::setSource(const QString &filePath)
{
    if( _source == filePath)
        return;
    else
        _source = filePath;

    if( _dataset == NULL )
        _dataset = ( GDALDataset* )GDALOpen( filePath.toStdString().c_str(), GA_ReadOnly );
    else
    {
        delete _dataset;
        _dataset = NULL;
        _dataset = ( GDALDataset* )GDALOpen( filePath.toStdString().c_str(), GA_ReadOnly );
    }
}

TileCuttInfo TileCuttCore::getInfo()
{
    double adfGeoTransform[6];
    if ( _dataset->GetGeoTransform(adfGeoTransform) == CE_None)
    {
        int x = _dataset->GetRasterXSize();
        int y = _dataset->GetRasterYSize();
        double left = adfGeoTransform[0];
        double top = adfGeoTransform[3];
        double right = adfGeoTransform[0]+x*adfGeoTransform[1]+y*adfGeoTransform[2];
        double bottom = adfGeoTransform[3]+x*adfGeoTransform[4]+y*adfGeoTransform[5];
        double xResolution = adfGeoTransform[1];
        double yResolution = -adfGeoTransform[5];
        double deltX = right - left;
        double deltY = top - bottom;
        double delt = deltX < deltY ? deltX : deltY;
        double resolution = xResolution < yResolution ? xResolution : yResolution;
        int min = 0;
        int max = 0;
        if( delt >= 36 )
        {
            min = 0;
        }
        else
        {
            for( int i = 0; i < 21; i++ )
            {
               double t = 36.0/(pow( 2, i ));
               if( t >= delt)
               {
                   continue;
               }
               else
               {
                   min = i-1;
                   break;
               }
            }
        }
        for( int i = 0; i < 21; i++)
        {
           double t = double(36.0/pow(2,i))/256.0;
           if(t >= resolution)
           {
               continue;
           }
           else
           {
                max = i-1;
                break;
           }
        }
        return TileCuttInfo( left, right, bottom, top, min, max);
    }
    else
    {
        return TileCuttInfo( 0, 0, 0, 0, 0, 0);
    }
}

int TileCuttCore::getBand()
{
    return _dataset->GetRasterCount();
}
