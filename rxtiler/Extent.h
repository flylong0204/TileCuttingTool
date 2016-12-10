#ifndef RXEARTH_EXTENT
#define RXEARTH_EXTENT 1

namespace rxtiler{
    //表示一个空间范围
    class Extent
    {
    public:
        inline Extent():left(-180),bottom(-90),right(180),top(90){}
        inline Extent(double l,double r,double b,double t)
        {
            right = r;
            left = l;;
            top = t;
            bottom = b;
        }
        inline double height()
        {
            return top - bottom;
        }
        inline double width()
        {
            return right - left;
        }

        //判断两个范围的拓扑关系
        //范围相等 返回 0
        //EXT 包含 this 返回 -1
        //this 包含 EXT 返回 1
        //有重叠 返回 2
        //不重叠 返回 -2
        int compara(Extent& ext);
        //获取中心点坐标
        void getCenter(double& x,double &y);
        //Vec3 getCenter();
        //当上下左右都为0 时返回FALSE
        bool valid();
        inline double centerx(){return (left+right)/2;}
        inline double centery(){return (bottom+top)/2;}
        inline bool containx(double x){return x <= right && x >= left;}
        inline bool containy(double y){return y <= top && y >= bottom;}
        inline bool contain(double x, double y){return containx(x) && containy(y);}

        bool cover(Extent& e);
        bool contain(Extent& e);
        inline Extent expand(double d){return Extent(left -d,right +d,bottom -d,top +d);}
        double left;
        double right;
        double bottom;
        double top;
    };
}
#endif
