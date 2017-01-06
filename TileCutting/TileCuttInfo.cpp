#include "TileCuttInfo.h"

TileCuttInfo::TileCuttInfo() : _left(-180),_bottom(-90),_right(180),_top(90),_minLayer(0),_maxLayer(0),_pixelWidth(0),_pixelHeight(0)
{

}

TileCuttInfo::TileCuttInfo( const double &l, const double &r, const double &t, const double &b, const int &min, const int &max ) : _pixelWidth(0),_pixelHeight(0)
{
    _left = l;
    _right = r;
    _top = t;
    _bottom = b;
    _minLayer = min;
    _maxLayer = max;
}

double TileCuttInfo::getLeft()
{
    return _left;
}

double TileCuttInfo::getRight()
{
    return _right;
}

double TileCuttInfo::getTop()
{
    return _top;
}

double TileCuttInfo::getBottom()
{
    return _bottom;
}

int TileCuttInfo::getMinLayer()
{
    return _minLayer;
}

int TileCuttInfo::getMaxLayer()
{
    return _maxLayer;
}

double TileCuttInfo::getWidth()
{
    return _right - _left;
}

double TileCuttInfo::getHeight()
{
    return _top - _bottom;
}

int TileCuttInfo::getPixelWidth()
{
    return _pixelWidth;
}

void TileCuttInfo::setPixelWidth(const int &w)
{
    _pixelWidth = w;
}

int TileCuttInfo::getPixelHeight()
{
    return _pixelHeight;
}

void TileCuttInfo::setPixelHeight(const int &h)
{
    _pixelHeight = h;
}

bool TileCuttInfo::operator==(TileCuttInfo info)
{
    return (info.getLeft() == _left) && (info.getRight() == _right) && (info.getTop() == _top) && (info.getBottom() == _bottom);
}

bool TileCuttInfo::operator <(TileCuttInfo info)
{
    return (info.getLeft() < _left) && (info.getRight() < _right) && (info.getTop() < _top) && (info.getBottom() < _bottom);
}

bool TileCuttInfo::operator >(TileCuttInfo info)
{
    return (info.getLeft() > _left) && (info.getRight() > _right) && (info.getTop() > _top) && (info.getBottom() > _bottom);
}

/**************************************************/

TileCuttKey::TileCuttKey(const TileCuttInfo &info) : _x(0), _y(0), _xLeft(0), _xRight(0), _yTop(0), _yBottom(0), _layer(0)
{

}

