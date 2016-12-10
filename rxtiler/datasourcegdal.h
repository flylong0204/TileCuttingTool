#ifndef DATASOURCEGDAL_H
#define DATASOURCEGDAL_H
#include "datasource.h"

#include <gdal_priv.h>
#include <osg/Shape>

#include "QString"

namespace rxtiler {

    class DataSourceGDAL : public DataSource
    {
        public:
            DataSourceGDAL(const QString filePath);
            virtual ~DataSourceGDAL();

            // DataSource interface
        public:

            Extent getExtent();
            bool computerLevels(TileOption *option, int *min, int* max);
            osg::Image *getImage(TileKey &key, Extent &extent);
            osg::HeightField *getDEM(TileKey &key, Extent &extent);

            void setNowLrbt( const Extent &lrbt);
            rxtiler::Extent getFoemerLrbt();

private:

            GDALDataset *poDataset;
            double _xResolution;
            double _yResolution;

            rxtiler::Extent _tif;
            rxtiler::Extent _foemerTif;
            rxtiler::Extent overLapTif;
            osg::Image* img;
            osg::HeightField dem;
    };



}

#endif // DATASOURCEGDAL_H
