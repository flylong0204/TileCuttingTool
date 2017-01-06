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
}

TagImageFileBasic::~TagImageFileBasic()
{

}

void TagImageFileBasic::setFilePath(const QString &filePath)
{
    if( _filePath == filePath)
        return;
    else
        _filePath = filePath;

    if( _dataset == NULL )
        _dataset = ( GDALDataset* )GDALOpen( filePath.toStdString().c_str(), GA_ReadOnly );
    else
    {
        delete _dataset;
        _dataset = NULL;
        _dataset = ( GDALDataset* )GDALOpen( filePath.toStdString().c_str(), GA_ReadOnly );
    }
}
