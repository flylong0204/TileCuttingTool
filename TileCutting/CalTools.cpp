#include "CalTools.h"

CalExtent::CalExtent():_top(90),_bottom(-90),_left(-180),_right(180)
{

}

CalExtent::CalExtent(const qreal &top, const qreal &bottom, const qreal &left, const qreal &right)
{
    _top = top;
    _bottom = bottom;
    _left = left;
    _right = right;
}

qreal CalExtent::getTop()
{
    return _top;
}

qreal CalExtent::getBottom()
{
    return _bottom;
}

qreal CalExtent::getLeft()
{
    return _left;
}

qreal CalExtent::getRight()
{
    return _right;
}

qreal CalExtent::height()
{
    return _top - _bottom;
}

qreal CalExtent::width()
{
    return _right - _left;
}


int CalExtent::compara( CalExtent &value)
{
    if (this->_left == value.getLeft()
            && this->_bottom == value.getBottom()
            && this->_right == value.getRight()
            && this->_top == value.getTop())
    {
        return 0;
    }
    else if (this->_left <= value.getLeft()
                && this->_bottom <= value.getBottom()
                && this->_right >= value.getRight()
                && this->_top >= value.getTop())
    {
        return 1;
    }
    else if (this->_left >= value.getLeft()
                    && this->_bottom >= value.getBottom()
                    && this->_right <= value.getRight()
                    && this->_top <= value.getTop())
    {
        return -1;
    }
    else if (this->_left >= value.getRight()
             || this->_right <= value.getLeft()
             || this->_bottom >= value.getTop()
             || this->_top <= value.getBottom())
    {
        return -2;
    }
    return 2;
}

qreal CalExtent::centerx()
{
    return (_left+_right)/2;
}

qreal CalExtent::centery()
{
    return (_bottom+_top)/2;
}

int CalExtent::getTileLeftX()
{
    return 0;
}

int CalExtent::getTileRightX()
{
    return 0;
}

int CalExtent::getTileTopY()
{
    return 0;
}

int CalExtent::getTileBottomY()
{
    return 0;
}


SavePicture::SavePicture():_filePath("")
{

}

void SavePicture::setFilePath(const QString &filePath)
{
    if( filePath != _filePath )
    {
        _filePath = filePath;
    }
}
