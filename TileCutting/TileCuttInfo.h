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
    //范围宽和高
    double getWidth();
    double getHeight();
    //像素宽和高
    int getPixelWidth();
    void setPixelWidth( const int &w );
    int getPixelHeight();
    void setPixelHeight(const int &h );

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
    int _pixelWidth;
    int _pixelHeight;

};

class TileCuttKey
{
public:
    TileCuttKey( const TileCuttInfo &info );

private:
    int _x;
    int _y;
    int _xLeft;
    int _xRight;
    int _yTop;
    int _yBottom;
    int _layer;
};

#endif // TILECUTTINFO_H
