#include "datasourcegdal.h"
#include "mainwindow.h"

#include <gdal_priv.h>
#include <QDebug>
#include <osgDB/WriteFile>

#include <qmath.h>

rxtiler::DataSourceGDAL::DataSourceGDAL(const QString filePath)
{
    _xResolution=0.0;
    _yResolution=0.0;
    GDALAllRegister();//注册驱动
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");//支持中文路径
    poDataset = ( GDALDataset* )GDALOpen( filePath.toStdString().c_str(), GA_ReadOnly );

    double adfGeoTransform[6];
    CPLErr res = poDataset->GetGeoTransform(adfGeoTransform);
    if (res == CE_None)
//    if (poDataset->GetGeoTransform(adfGeoTransform) == CE_None)
    {
        _xResolution=adfGeoTransform[1];
        _yResolution=-adfGeoTransform[5];
    }
//    GDALClose(poDataset);

//    black= new osg::Image();
    img = new osg::Image();
    //tile = new rxtiler::Extent();
}

rxtiler::DataSourceGDAL::~DataSourceGDAL()
{
    delete poDataset;
    poDataset = NULL;

}



rxtiler::Extent rxtiler::DataSourceGDAL::getExtent()
{
    double adfGeoTransform[6];
    if (poDataset->GetGeoTransform(adfGeoTransform) == CE_None){
        int x=poDataset->GetRasterXSize();
        int y=poDataset->GetRasterYSize();
        double left=adfGeoTransform[0];
        double top=adfGeoTransform[3];
        double right=adfGeoTransform[0]+x*adfGeoTransform[1]+y*adfGeoTransform[2];
        double bottom=adfGeoTransform[3]+x*adfGeoTransform[4]+y*adfGeoTransform[5];
        _foemerTif.left = left;
        _foemerTif.right = right;
        _foemerTif.bottom = bottom;
        _foemerTif.top = top;


        return rxtiler::Extent(left,right,bottom,top);
    }else
    {
        return rxtiler::Extent(0,0,0,0);
    }
}

bool rxtiler::DataSourceGDAL::computerLevels(rxtiler::TileOption *option, int *min, int* max)
{
    rxtiler::Extent extent=getExtent();
    double deltX=extent.right-extent.left;
    double deltY=extent.top-extent.bottom;
    double delt=(deltX<deltY)?deltX:deltY;

    double resolution=(_xResolution<_yResolution)?_xResolution:_yResolution;

    if(delt>=36){
        min=0;
    }else{
        for(int i=0;i<21;i++){
           double t= 36.0/(pow(2,i));
           if(t>=delt){
               continue;
           }else{
               *min=i-1;
               break;
           }
        }
    }
    for(int i=0;i<21;i++){
       double t= double(36.0/pow(2,i))/256.0;
       if(t>=resolution){
           continue;
       }else{
            *max=i-1;
            break;
       }
    }

    return true;
}

osg::Image *rxtiler::DataSourceGDAL::getImage(rxtiler::TileKey &key, rxtiler::Extent &extent)
{

    static int bandmap[3] = {1,1,1};
    static int bandmap3[4] = {1,2,3,4};

    int src_bandsize = poDataset->GetRasterCount();
    int out_bandsize = 0;
    int * out_bandmap = 0;
    int iWidth = poDataset->GetRasterXSize();
    int iHeight = poDataset->GetRasterYSize();
    if (src_bandsize < 1)
    {
        GDALClose(poDataset);
        return NULL;
    }
    else if(src_bandsize == 1){
        out_bandsize = 3;
        out_bandmap = bandmap;
    }else if(src_bandsize == 3){
        out_bandsize = 3;
        out_bandmap = bandmap3;
    }else if(src_bandsize == 4){
        out_bandsize = 4;
        out_bandmap = bandmap3;
    }else{
        GDALClose(poDataset);
            return 0;
    }

    if( qAbs(_tif.left -  _foemerTif.left) <= 0.001 &&
        qAbs( _tif.right - _foemerTif.right) <= 0.001 &&
        qAbs( _tif.bottom - _foemerTif.bottom) <= 0.001 &&
        qAbs(_tif.top - _foemerTif.top) <= 0.0001 )
    {
        if (extent.compara(_tif) == -1)
        {
            int x = iWidth * (extent.left - _tif.left) / (_tif.right - _tif.left);
            int y = iHeight * ( _tif.top - extent.top) /  (_tif.top - _tif.bottom);
            int XSize = iWidth * extent.width() /  _tif.width();
            int YSize = iHeight * extent.height()  /  _tif.height();


            unsigned char *buffer = (unsigned char*)malloc(256*256*out_bandsize);
            CPLErr err = poDataset->RasterIO(GF_Read, x, y, XSize, YSize, buffer, 256
                                , 256, GDT_Byte, out_bandsize,out_bandmap,out_bandsize,256*out_bandsize,1);

            img->allocateImage(256,256,out_bandsize,GL_RGBA,GL_BYTE);
            for(int x =0; x< 256;x++){
                for(int y = 0; y< 256; y++){
                    char r,g,b,a;
                    r=g=b=buffer[x*256*out_bandsize+out_bandsize*y];
                    a=1;
                    img->setColor(osg::Vec4(r,g,b,a),x,y);
                }
            }

           return img;
       }
       else
       {
            //black
            img->allocateImage(256,256,4,GL_RGBA,GL_BYTE);
                for(int x =0; x< 256;x++){
                  for(int y = 0; y< 256; y++){

                      img->setColor(osg::Vec4(0,0,0,1),x,y);
                  }
                }
              return img;
        }
    }
    else
    {
        //无重叠
        if( _tif.left > _foemerTif.right ||
            _tif.right < _foemerTif.left ||
            _tif.bottom > _foemerTif.top ||
            _tif.top < _foemerTif.bottom)
        {
            //black
            img->allocateImage(256,256,4,GL_RGBA,GL_BYTE);
                for(int x =0; x< 256;x++){
                  for(int y = 0; y< 256; y++){

                      img->setColor(osg::Vec4(0,0,0,1),x,y);
                  }
                }
              return img;
        }
        //计算重叠区域
        overLapTif.right = _tif.right > _foemerTif.right ? _foemerTif.right : _tif.right;
        overLapTif.left = _tif.left > _foemerTif.left ? _tif.left : _foemerTif.left;
        overLapTif.bottom = _tif.bottom > _foemerTif.bottom ? _tif.bottom : _foemerTif.bottom;
        overLapTif.top = _tif.top > _foemerTif.top ? _foemerTif.top : _tif.top;
        if(extent.compara(overLapTif) == -1)
        {
            int x = iWidth * (extent.left - _tif.left) / (_tif.right - _tif.left);
            int y = iHeight * ( _tif.top - extent.top) /  (_tif.top - _tif.bottom);
            int XSize = iWidth * extent.width() /  _tif.width();
            int YSize = iHeight * extent.height()  /  _tif.height();


            unsigned char *buffer = (unsigned char*)malloc(256*256*out_bandsize);
            CPLErr err = poDataset->RasterIO(GF_Read, x, y, XSize, YSize, buffer, 256
                                , 256, GDT_Byte, out_bandsize,out_bandmap,out_bandsize,256*out_bandsize,1);

            img->allocateImage(256,256,out_bandsize,GL_RGBA,GL_BYTE);
            for(int x =0; x< 256;x++){
                for(int y = 0; y< 256; y++){
                    char r,g,b,a;
                    r=g=b=buffer[x*256*out_bandsize+out_bandsize*y];
                    a=1;
                    img->setColor(osg::Vec4(r,g,b,a),x,y);
                }
            }

           return img;
        }
    }
}

osg::HeightField *rxtiler::DataSourceGDAL::getDEM(rxtiler::TileKey &key, rxtiler::Extent &extent)
{
    static int bandmap[3] = {1,1,1};
    static int bandmap3[4] = {1,2,3,4};

    int src_bandsize = poDataset->GetRasterCount();
    int out_bandsize = 0;
    int * out_bandmap = 0;
    int iWidth = poDataset->GetRasterXSize();
    int iHeight = poDataset->GetRasterYSize();
    if (src_bandsize < 1)
    {
        GDALClose(poDataset);
        return NULL;
    }
    else if(src_bandsize == 1){
        out_bandsize = 3;
        out_bandmap = bandmap;
    }else if(src_bandsize == 3){
        out_bandsize = 3;
        out_bandmap = bandmap3;
    }else if(src_bandsize == 4){
        out_bandsize = 4;
        out_bandmap = bandmap3;
    }else{
        GDALClose(poDataset);
            return 0;
    }

    if( qAbs(_tif.left -  _foemerTif.left) <= 0.001 &&
        qAbs( _tif.right - _foemerTif.right) <= 0.001 &&
        qAbs( _tif.bottom - _foemerTif.bottom) <= 0.001 &&
        qAbs(_tif.top - _foemerTif.top) <= 0.0001 )
    {
        if (extent.compara(_tif) == -1)
        {
            int x = iWidth * (extent.left - _tif.left) / (_tif.right - _tif.left);
            int y = iHeight * ( _tif.top - extent.top) /  (_tif.top - _tif.bottom);
            int XSize = iWidth * extent.width() /  _tif.width();
            int YSize = iHeight * extent.height()  /  _tif.height();


            unsigned char *buffer = (unsigned char*)malloc(256*256*out_bandsize);
            CPLErr err = poDataset->RasterIO(GF_Read, x, y, XSize, YSize, buffer, 256
                                , 256, GDT_Byte, out_bandsize,out_bandmap,out_bandsize,256*out_bandsize,1);

            dem->allocate(60,60);
            for(int x =0; x< 256;x++){
                for(int y = 0; y< 256; y++){
                    char r,g,b,a;
                    r=g=b=buffer[x*256*out_bandsize+out_bandsize*y];
                    a=1;
                    dem->setHeight(x,y,r);
                }
            }

           return dem;
       }
       else
       {
            //black
            dem->allocate(60,60);
                for(int x =0; x< 60;x++){
                  for(int y = 0; y< 60; y++){

                      dem.setHeight(x,y,0);
                  }
                }
              return dem;
        }
    }
    else
    {
        //无重叠
        if( _tif.left > _foemerTif.right ||
            _tif.right < _foemerTif.left ||
            _tif.bottom > _foemerTif.top ||
            _tif.top < _foemerTif.bottom)
        {
            //black
            //img->allocateImage(256,256,4,GL_RGBA,GL_BYTE);
            dem.allocate(60,60);
                for(int x =0; x< 60;x++){
                  for(int y = 0; y< 60; y++){

                      //img->setColor(osg::Vec4(0,0,0,1),x,y);
                      dem.setHeight(x,y,0);
                  }
                }
              return dem;
        }
    }
}

void rxtiler::DataSourceGDAL::setNowLrbt(const rxtiler::Extent &lrbt)
{
    _tif.left = lrbt.left;
    _tif.right = lrbt.right;
    _tif.top = lrbt.top;
    _tif.bottom = lrbt.bottom;
}

rxtiler::Extent rxtiler::DataSourceGDAL::getFoemerLrbt()
{
    return _foemerTif;
}
