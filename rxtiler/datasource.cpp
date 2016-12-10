#include "datasource.h"

using namespace rxtiler;

rxtiler::DataSource::DataSource()
{

}

DataSource::~DataSource()
{

}

Extent DataSource::getExtent()
{
    return Extent();
}

bool DataSource::computerLevels(TileOption *option, int *min, int* max)
{
    return false;
}

osg::Image *DataSource::getImage(TileKey &key,Extent& extent)
{
    return 0;
}

osg::HeightField *DataSource::getDEM(TileKey &key, Extent &extent)
{
    return 0;
}

bool DataSource::saveImage(TileKey &key, osg::Image *img)
{
    return false;
}

osg::Image *DataSource::saveDEM()
{
    return 0;
}

