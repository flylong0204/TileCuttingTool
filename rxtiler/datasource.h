#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "datasource.h"
#include "TileKey.h"
#include "TileOption.h"
#include <osg/Image>
#include <osg/Shape>

namespace rxtiler {

    class DataSource
    {
    public:
        DataSource();

        virtual ~DataSource();
        //获取数据源空间范围
        virtual Extent getExtent();
        //计算该数据在option金字塔结构下的层级范围
        virtual bool computerLevels(TileOption* option,int* min,int* max);
        //获取瓦片对应的影像
        virtual osg::Image* getImage(TileKey& key,Extent& extent);
        virtual osg::HeightField* getDEM(TileKey &key,Extent& extent);
        //保存该瓦片的影像
        virtual bool saveImage(TileKey& key,osg::Image* img);
        virtual osg::Image *saveDEM();

    };

}



#endif // DATASOURCE_H
