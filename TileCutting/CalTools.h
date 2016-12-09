#ifndef CALCULATINGTOOLS_H
#define CALCULATINGTOOLS_H

#include <QtGlobal>
#include <QString>

#include <osg/Image>

/**
 * @brief The CalculatingTools class
 * @作用 计算区域位置的各种算法
 */
class CalExtent
{
public:
    CalExtent();
    CalExtent( const qreal &top, const qreal &bottom, const qreal &left, const qreal &right );
    qreal getTop();
    qreal getBottom();
    qreal getLeft();
    qreal getRight();
    qreal height();
    qreal width();
    /**
     * 范围相等 返回 0
     * 包含 返回 -1
     * 被包含 返回 1
     * 有重叠 返回 2
     * 无重叠 返回 -2
     */
    int compara( CalExtent &value);
    //计算中心点
    qreal centerx();
    qreal centery();
    //计算所在瓦片范围
    int getTileLeftX();
    int getTileRightX();
    int getTileTopY();
    int getTileBottomY();


private:
    qreal _top;
    qreal _bottom;
    qreal _left;
    qreal _right;
    int _minLayer;
    int _maxLayer;

};

/**
 * brief The TileKey class
 * 作用 一个TileKey(层级、横纵)确定一个瓦片
 */
class TileKey
{
public:
    TileKey():_layer(0),_x(0),_y(0) {}
    bool operator == (TileKey& key)
    {
        return this->getLayer() == key.getLayer() && this == key.x && y == key.y;
    }
    int getLayer()
    {
        return _layer;
    }
    int getX()
    {
        return _x;
    }
    int getY()
    {
        return _y;
    }

private:
    int _layer;
    int _x;
    int _y;
};


#endif // CALCULATINGTOOLS_H
