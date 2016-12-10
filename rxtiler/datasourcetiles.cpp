#include "datasourcetiles.h"
#include <QString>
#include <osgDB/WriteFile>
#include <QDebug>
#include <TileKey.h>
#include <QDir>
#include <QColor>
#include <osgDB/ReadFile>

rxtiler::DataSourceTiles::DataSourceTiles()
{

}

rxtiler::DataSourceTiles::~DataSourceTiles()
{

}

//设置保存的根目录
void rxtiler::DataSourceTiles::setRootDir(QString dir)
{
    _root_dir = dir;
}

//设置无背景的颜色值
void rxtiler::DataSourceTiles::setNoDataColor(osg::Vec4 color)
{
    _nodata = color;
}

//保存图片
bool rxtiler::DataSourceTiles::saveImage(rxtiler::TileKey &key, osg::Image *img)
{
    QDir _dir;
    //把int型的lod、y、x转化成QString四位，不够用0补齐
    //leftTustified,左对齐
    QString lstr = QString::number(key.lod);
    QString ystr = QString::number(key.y).rightJustified(4,'0');
    QString xstr = QString::number(key.x).rightJustified(4,'0');

    //创建目录，用“/”分隔
    QString str_dir = _root_dir;
    //qDebug()<<"_root_dir"<<_root_dir<<endl;
    str_dir += "/" + lstr;
    if(!_dir.exists(str_dir))
    {
        _dir.mkdir(str_dir);
    }

    str_dir += "/" + xstr;//2222
    if(!_dir.exists(str_dir))
    {
        _dir.mkdir(str_dir);
    }
    str_dir += "/" + xstr + "_" + ystr + ".png";//111

    //法二:
//    str= _root_dir/1/0001/0001_0001.png
//    QString str = QString(_root_dir + "/" + "%1/%2/%3_%4.png")
//            .arg(key.lod)
//            .arg(ystr)
//            .arg(ystr)
//            .arg(xstr);

    //向目录里存图片
    if(!_dir.exists(str_dir))
    {
       osgDB::writeImageFile(*img,str_dir.toStdString().c_str());
    }
    else
    {
        osg::Vec4 nodata = _nodata;
        //读取已保存的图片
        osg::Image* previous_img = osgDB::readImageFile(str_dir.toStdString().c_str());
        for(int x = 0; x <  img->s(); x ++)
        {
            for(int y = 0; y < img->t(); y++)
            {
                osg::Vec4 c1 = img->getColor(x,y);
                osg::Vec4 c2 = previous_img->getColor(x,y);
                //判断覆盖黑边区域
                //qDebug()<< c1.r() << c1.g() <<c1.b() << c1.a() <<endl;
                if(nodata == c1)
                {
                    //设置像素点的值
                    img->setColor(c2,x,y);
                }
            }
        }
        //最后将融合后的照片保存
        osgDB::writeImageFile(*img,str_dir.toStdString().c_str());
    }
    return true;
}

bool rxtiler::DataSourceTiles::saveDEM(rxtiler::TileKey &key, osg::HeightField *dem)
{
    return true;
}
