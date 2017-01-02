#include "TileCuttImage.h"

TileCuttImage::TileCuttImage() :
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

TileCuttImage::~TileCuttImage()
{

}
