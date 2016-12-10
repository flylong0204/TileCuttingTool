#ifndef DATASOURCETILES_H
#define DATASOURCETILES_H

#include <QString>
#include "datasource.h"

#include <osg/Vec4>
#include <osg/Shape>

namespace rxtiler {

    class DataSourceTiles : public DataSource
    {
    public:
        DataSourceTiles();
        virtual ~DataSourceTiles();

        void setRootDir(QString dir);
        void setNoDataColor(osg::Vec4 color);

    public:
        bool saveImage(TileKey &key, osg::Image *img);
        bool saveDEM(TileKey &key, osg::HeightField *dem);
    protected:
        QString _root_dir;
        osg::Vec4 _nodata;
    };

}

#endif // DATASOURCETILES_H
