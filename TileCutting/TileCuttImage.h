#ifndef TILECUTTIMAGE_H
#define TILECUTTIMAGE_H

#include <QString>

#include "TileCuttInfo.h"
#include "TileCuttInfo.h"

#include <gdal_priv.h>
#include <osg/Shape>

class TileCuttImage
{
public:
    TileCuttImage();
    ~TileCuttImage();

    void setSource( const QString &source );
    void getRange();
    void getHierarchy();

    void getImage( const TileCuttInfo &info );
    void saveImage( const TileCuttInfo &info );

private:
    GDALDataset *_dataset;
    QString _source;
    double _left;
    double _right;
    double _top;
    double _bottom;
    int _minHierarchy;
    int _maxHierarchy;
    osg::Image *_img;
    osg::HeightField *_dem;

};

#endif // TILECUTTIMAGE_H
