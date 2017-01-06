#ifndef TAGIMAGEFILE_H
#define TAGIMAGEFILE_H

#include <QString>

#include <gdal_priv.h>
#include <osg/Shape>

enum TigImageFileType
{
    IMAGE_TILE = x0,
    DEM_TILE = x1
};

class TagImageFileBasic
{
public:
    TagImageFileBasic();
    TagImageFileBasic( const QString &filePath, const TigImageFileType &type );
    ~TagImageFileBasic();

    void setFilePath( const QString &filePath );

private:
    GDALDataset *_dataset = NULL;
    QString _filePath;
    TigImageFileType _type;
    double _left;
    double _right;
    double _top;
    double _bottom;
    int _minLayer;
    int _maxLayer;
    int _band;
    int _pixelWidth;
    int _pixelHeight;
};

#endif // TAGIMAGEFILE_H
