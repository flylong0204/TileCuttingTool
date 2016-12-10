#include "Extent.h"

using namespace rxtiler;

int rxtiler::Extent::compara( Extent &ext )
{
	if (this->left == ext.left
		&& this->bottom == ext.bottom
		&& this->right == ext.right
		&& this->top == ext.top
		)
	{
		return 0;
	}else
	if (this->left <= ext.left
		&& this->bottom <= ext.bottom
		&& this->right >= ext.right
		&& this->top >= ext.top)
	{
		return 1;
	}else
	if (this->left >= ext.left
		&& this->bottom >= ext.bottom
		&& this->right <= ext.right
		&& this->top <= ext.top)
	{
		return -1;
	}
	else if (this->left >= ext.right
		|| this->right <= ext.left
		|| this->bottom >= ext.top
		|| this->top <= ext.bottom
		)
	{
		return -2;
	}
	return 2;
}

void rxtiler::Extent::getCenter( double& x,double &y )
{
	x = (left + right)/2;
	y = (top + bottom)/2;
}
//
//rxtiler::Vec3d rxtiler::Extent::getCenter()
//{
//	return Vec3d((_left + _right)/2,(_top + _bottom)/2,0.0);
//}

bool rxtiler::Extent::valid()
{
	static Extent ext;
	return this->compara(ext) != 0;
}

//rxtiler::Extent rxtiler::Extent::expand( double d )
//{
//	return rxtiler::Extent(left -d,right +d,bottom -d,top +d);
//}

bool rxtiler::Extent::cover( Extent& e )
{
    return compara(e) > -2;
}

bool rxtiler::Extent::contain(Extent &e)
{
    return left <= e.left && right >= e.right && bottom <= e.bottom && top >= e.top;
}
