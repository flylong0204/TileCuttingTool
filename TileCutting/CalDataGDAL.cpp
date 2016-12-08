#include "CalDataGDAL.h"

CalDataGDAL::CalDataGDAL(const QString filePath):_xResolution(0),_yResolution(0)
{
    GDALAllRegister();//注册驱动
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");//支持中文路径
    _poDataset = ( GDALDataset* )GDALOpen( filePath.toStdString().c_str(), GA_ReadOnly );
}

CalDataGDAL::~CalDataGDAL()
{
    delete _poDataset;
}

CalExtent CalDataGDAL::getExtent()
{
    double adfGeoTransform[6];
    if ( _poDataset->GetGeoTransform(adfGeoTransform) == CE_None)
    {
        int x= _poDataset->GetRasterXSize();
        int y= _poDataset->GetRasterYSize();
        qreal left = adfGeoTransform[0];
        qreal top = adfGeoTransform[3];
        qreal right = adfGeoTransform[0]+x*adfGeoTransform[1]+y*adfGeoTransform[2];
        qreal bottom = adfGeoTransform[3]+x*adfGeoTransform[4]+y*adfGeoTransform[5];
        _xResolution = adfGeoTransform[1];
        _yResolution = -adfGeoTransform[5];
        return CalExtent(top,bottom,left,right);
    }else
    {
        return CalExtent(0,0,0,0);
    }
}

bool CalDataGDAL::getLayering(int *min, int *max)
{
    CalExtent extent = getExtent();
    double deltX = extent.getRight() - extent.getLeft();
    double deltY = extent.getTop() - extent.getBottom();
    double delt = ( deltX < deltY ) ? deltX : deltY;

    double resolution=(_xResolution < _yResolution) ? _xResolution:_yResolution;

    if( delt>=36 )
    {
        min=0;
    }
    else
    {
        for(int i=0;i<21;i++)
        {
           double t= 36.0/(pow(2,i));
           if(t>=delt)
           {
               continue;
           }
           else
           {
               *min=i-1;
               break;
           }
        }
    }
    for(int i=0;i<21;i++)
    {
       double t= double(36.0/pow(2,i))/256.0;
       if(t>=resolution)
       {
           continue;
       }
       else
       {
            *max=i-1;
            break;
       }
    }
    if( *min < *max )
    {
        return true;
    }
    else
    {
        return false;
    }

}
