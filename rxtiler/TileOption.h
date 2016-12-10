#ifndef RE_TILEOPTION
#define RE_TILEOPTION 1

#include "TileKey.h"
#include "Extent.h"


namespace rxtiler{

    //瓦片存储结构
    class TileOption
    {
    public:
        TileOption();
        typedef unsigned int uint;
        //编码起始点 左上/左下 默认为左上
        enum CodeOrigin
        {
            LeftTop = 0,
            LeftBottom = 1
        };
        Extent extent;

        uint tilesize;
        double tile_lon_0;
        double tile_lat_0;

        uint level0;
        uint level1;
        //编号起始点 左上/左下
        CodeOrigin origin;
    public:
        double getReslutionX(unsigned int z);
        double getReslutionY(unsigned int  z);
        int getTileX(unsigned int  z,double lon);
        int getTileY(unsigned int  z,double lat);
        rxtiler::Extent getExtent(TileKey& key);
        int getTileCountX();
        int getTileCountY();
        int getTileCountX(int level);
        int getTileCountY(int level);
    };

}
#endif
