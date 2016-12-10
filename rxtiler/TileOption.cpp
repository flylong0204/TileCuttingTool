#include "TileOption.h"
#include <math.h>

using namespace rxtiler;

int rxtiler::TileOption::getTileX( unsigned int z,double lon )
{
	return (lon - extent.left) / (tile_lon_0 / (1 << (z - level0)));
}

int rxtiler::TileOption::getTileY( unsigned int z,double lat )
{
	double d = origin == LeftTop ? extent.top - lat : lat - extent.bottom;
	return d / (tile_lat_0 / (1 << z - level0));
}

double rxtiler::TileOption::getReslutionY( unsigned int  z )
{
	return tile_lat_0 / tilesize / (1 << z - level0);
}

double rxtiler::TileOption::getReslutionX( unsigned int  z )
{
	return tile_lon_0 / (1 << (z - level0)) / tilesize;
}

rxtiler::Extent rxtiler::TileOption::getExtent( TileKey& key )
{
	double dx = tile_lon_0 / (1 << (key.lod - level0));
	Extent ext;
	ext.left = key.x * dx  + extent.left;
	ext.right = ext.left + dx;

	double dy = tile_lat_0  / (1 << (key.lod - level0));

	if(origin ==  LeftTop ){
		ext.top = extent.top - key.y * dy;
		ext.bottom = ext.top - dy;
	} else {
		ext.bottom = key.y * dy + extent.bottom; 
		ext.top = ext.bottom + dy;
	}

	return ext;
}

rxtiler::TileOption::TileOption()
	:extent(-180,180,-90,90)
{
    //extent = rxtiler::Extent(-180,180,-90,90);
	level0 = 0;
    level1 = 1;
	tilesize = 256;
    tile_lon_0 = 36;
    tile_lat_0 = 36;
    origin = LeftBottom;
}

int rxtiler::TileOption::getTileCountX()
{
	return extent.width() / this->tile_lon_0 + 0.5;
}

int rxtiler::TileOption::getTileCountX( int level )
{
	int x = getTileCountX();
	return x << (level - level0);
}

int rxtiler::TileOption::getTileCountY()
{
	return extent.height() / this->tile_lat_0 + 0.5;
}

int rxtiler::TileOption::getTileCountY( int level )
{
	int x = getTileCountY();
	return x << (level - level0);
}
