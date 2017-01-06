#ifndef TAGIMAGEFILE_H
#define TAGIMAGEFILE_H

#include <QString>

#include <gdal_priv.h>
#include <osg/Shape>

enum TigImageFileType
{
    IMAGE_TILE = 0,
    DEM_TILE = 1
};

class TagImageFileBasic
{
public:
    TagImageFileBasic();
    TagImageFileBasic( const QString &filePath, const TigImageFileType &type );
    ~TagImageFileBasic();

    void setFilePath( const QString &filePath );
    double getLeft();
    double getRight();
    double getTop();
    double getBottom();
    int getMinLayer();
    int getMaxLayer();
    int getBand();
    //范围宽和高
    double getWidth();
    double getHeight();
    //像素宽和高
    int getPixelWidth();
    int getPixelHeight();

    //重载运算符（比较两个tif范围的关系）
    bool operator==(TagImageFileBasic tif) const
    {
        return _left == tif.getLeft() && _right == tif.getRight() && _top == tif.getTop() && _bottom == tif.getBottom();
    }
    bool operator >(TagImageFileBasic tif) const
    {
        return _left < tif.getLeft() && _right < tif.getRight() && _top < tif.getTop() && _bottom < tif.getBottom();
    }
    bool operator <(TagImageFileBasic tif) const
    {
        return _left > tif.getLeft() && _right > tif.getRight() && _top > tif.getTop() && _bottom > tif.getBottom();
    }
    //osg::Image getImage();

protected:
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

    osg::ref_ptr<osg::Image> _image;

    void getInfo();
};

class TagImageFileTile
{
public:
    TagImageFileTile( const double &l, const double &r, const double &t, const double &b) : _pixelWidth(256), _pixelHeight(256)
    {
        _left = l;
        _right = r;
        _top = t;
        _bottom = b;
    }
    double getPixelWidth()
    {
        return _pixelWidth;
    }
    double getPixelHeight()
    {
        return _pixelHeight;
    }
    void setPixelSize( const int &w, const int &h)
    {
        _pixelWidth = w;
        _pixelHeight = h;
    }

protected:
    double _left;
    double _right;
    double _top;
    double _bottom;
    int _pixelWidth;
    int _pixelHeight;
};

#endif // TAGIMAGEFILE_H
