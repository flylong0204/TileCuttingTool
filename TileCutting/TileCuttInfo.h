#ifndef TILECUTTINFO_H
#define TILECUTTINFO_H


class TileCuttInfo
{
public:
    TileCuttInfo();
    TileCuttInfo( const double &l, const double &r, const double &t, const double &b, const int &min, const int &max );

    double getLeft();
    double getRight();
    double getTop();
    double getBottom();
    int getMinLayer();
    int getMaxLayer();
    double getWidth();
    double getHeight();

    //重载运算符（判断范围关系）
    bool operator==(TileCuttInfo info);
    bool operator <(TileCuttInfo info);
    bool operator >(TileCuttInfo info);

private:
    double _left;
    double _right;
    double _top;
    double _bottom;
    int _minLayer;
    int _maxLayer;

};

class TileCuttKey
{
public:
    TileCuttKey( const TileCuttInfo &info );

    void setTileSize( const int &width, const int &height);

private:
    int _x;
    int _y;
    int _xLeft;
    int _xRight;
    int _yTop;
    int _yBottom;
    int _layer;
    int _tileWidth;
    int _tileHeight;
};

#endif // TILECUTTINFO_H
