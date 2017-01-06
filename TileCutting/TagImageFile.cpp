#include "TagImageFile.h"

TagImageFileBasic::TagImageFileBasic() :
    _filePath(""),
    _type(IMAGE_TILE),
    _left(0.0),
    _right(0.0),
    _top(0.0),
    _bottom(0.0),
    _minLayer(0),
    _maxLayer(0),
    _band(0),
    _pixelWidth(0),
    _pixelHeight(0)
{
    GDALAllRegister();//注册驱动
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");//支持中文路径
}

TagImageFileBasic::TagImageFileBasic(const QString &filePath, const TigImageFileType &type) :
    _left(0.0),
    _right(0.0),
    _top(0.0),
    _bottom(0.0),
    _minLayer(0),
    _maxLayer(0),
    _band(0),
    _pixelWidth(0),
    _pixelHeight(0)
{
    _filePath = filePath;
    _type = type;
    GDALAllRegister();//注册驱动
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");//支持中文路径
    _dataset = ( GDALDataset* )GDALOpen( filePath.toStdString().c_str(), GA_ReadOnly );
    getInfo();
}

TagImageFileBasic::~TagImageFileBasic()
{
    if( _dataset != NULL )
    {
        delete _dataset;
        _dataset = NULL;
    }
}

void TagImageFileBasic::setFilePath(const QString &filePath)
{
    if( _filePath == filePath)
        return;
    else
        _filePath = filePath;

    if( _dataset == NULL )
    {
        _dataset = ( GDALDataset* )GDALOpen( filePath.toStdString().c_str(), GA_ReadOnly );
        getInfo();
    }
    else
    {
        delete _dataset;
        _dataset = NULL;
        _dataset = ( GDALDataset* )GDALOpen( filePath.toStdString().c_str(), GA_ReadOnly );
        getInfo();
    }
}

double TagImageFileBasic::getLeft()
{
    return _left;
}

double TagImageFileBasic::getRight()
{
    return _right;
}

double TagImageFileBasic::getTop()
{
    return _top;
}

double TagImageFileBasic::getBottom()
{
    return _bottom;
}

int TagImageFileBasic::getMinLayer()
{
    return _minLayer;
}

int TagImageFileBasic::getMaxLayer()
{
    return _maxLayer;
}

int TagImageFileBasic::getBand()
{
    return _band;
}

double TagImageFileBasic::getWidth()
{
    return _right - _left;
}

double TagImageFileBasic::getHeight()
{
    return _top - _bottom;
}

int TagImageFileBasic::getPixelWidth()
{
    return _pixelWidth;
}

int TagImageFileBasic::getPixelHeight()
{
    return _pixelHeight;
}

void TagImageFileBasic::getInfo()
{
    double adfGeoTransform[6];
    if ( _dataset->GetGeoTransform(adfGeoTransform) == CE_None)
    {
        int x = _dataset->GetRasterXSize();
        int y = _dataset->GetRasterYSize();
        _band = _dataset->GetRasterCount();
        _pixelWidth = _dataset->GetRasterXSize();
        _pixelHeight = _dataset->GetRasterYSize();
        _left = adfGeoTransform[0];
        _top = adfGeoTransform[3];
        _right = adfGeoTransform[0]+x*adfGeoTransform[1]+y*adfGeoTransform[2];
        _bottom = adfGeoTransform[3]+x*adfGeoTransform[4]+y*adfGeoTransform[5];
        double xResolution = adfGeoTransform[1];
        double yResolution = -adfGeoTransform[5];
        double deltX = _right - _left;
        double deltY = _top - _bottom;
        double delt = deltX < deltY ? deltX : deltY;
        double resolution = xResolution < yResolution ? xResolution : yResolution;
        if( delt >= 36 )
        {
            _minLayer = 0;
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
                   _minLayer = i-1;
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
                _maxLayer = i-1;
                break;
           }
        }
    }
    else
    {
        return;
    }
}
