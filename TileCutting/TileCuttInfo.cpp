#include "TileCuttInfo.h"

TileCuttInfo::TileCuttInfo() : _left(-180),_bottom(-90),_right(180),_top(90)
{

}

TileCuttInfo::TileCuttInfo( const float &l, const float &r, const float &t, const float &b)
{
    _left = l;
    _right = r;
    _top = t;
    _bottom = b;
}

float TileCuttInfo::getLeft()
{
    return _left;
}

float TileCuttInfo::getRight()
{
    return _right;
}

float TileCuttInfo::getTop()
{
    return _top;
}

float TileCuttInfo::getBottom()
{
    return _bottom;
}

float TileCuttInfo::getWidth()
{
    return _right - _left;
}

float TileCuttInfo::getHeight()
{
    return _top - _bottom;
}

QVector4D TileCuttInfo::getRange()
{
    return QVector4D(_left,_right,_top,_bottom);
}

int TileCuttInfo::compara(const TileCuttInfo &info)
{
    return 0;
}

bool TileCuttInfo::operator==(TileCuttInfo info)
{
    return (info.getLeft() == _left);
}
