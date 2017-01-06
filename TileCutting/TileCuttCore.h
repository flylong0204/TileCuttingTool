#ifndef TileCuttCore_H
#define TileCuttCore_H

#include <QString>

#include "TileCuttInfo.h"
#include "TileCuttCore.h"

#include <gdal_priv.h>
#include <osg/Shape>

class TileCuttCore
{
public:
    TileCuttCore();
    ~TileCuttCore();

    void setSource( const QString &filePath );
    TileCuttInfo getInfo();
    int getBand();

    //void getImage( const TileCuttInfo &info );
    //void saveImage( const TileCuttInfo &info );

private:
    GDALDataset *_dataset = NULL;
    QString _source;
    osg::Image *_img;
    osg::HeightField *_dem;

};

#endif // TileCuttCore_H
