#ifndef TILECUTTINFO_H
#define TILECUTTINFO_H

#include <QVector4D>

class TileCuttInfo
{
public:
    TileCuttInfo();
    TileCuttInfo( const float &l, const float &r, const float &t, const float &b);

    float getLeft();
    float getRight();
    float getTop();
    float getBottom();
    float getWidth();
    float getHeight();
    QVector4D getRange();

    int compara(const TileCuttInfo &info);

    //重载运算符
    bool operator == (const TileCuttInfo &info) const;

private:
    float _left;
    float _right;
    float _top;
    float _bottom;

};

#endif // TILECUTTINFO_H
