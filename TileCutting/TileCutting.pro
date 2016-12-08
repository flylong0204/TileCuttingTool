QT       += core gui widgets

TARGET = TileCutting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CalDataGDAL.cpp \
    CalTools.cpp

HEADERS  += mainwindow.h \
    CalDataGDAL.h \
    CalTools.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/../sdk/osg/include
INCLUDEPATH += $$PWD/../sdk/3rd/include


LIBS += -L"$$PWD/../sdk/osg/lib"
LIBS += -L"$$PWD/../sdk/3rd/lib"

CONFIG(debug, debug|release){
    LIBS += -lOpenThreadsd \
        -losgd \
        -losgDBd \
        -losgUtild \
        -losgGAd \
        -losgViewerd \
        -losgTextd \
        -losgWidgetd \
        -losgFXd \
        -losgQtd
}else{
    LIBS += -lOpenThreads \
        -losg \
        -losgDB \
        -losgUtil \
        -losgGA \
        -losgViewer \
        -losgText \
        -losgWidget \
        -losgFX \
        -losgQt \
}

LIBS += "E:/Project/TileCuttingTool/sdk/3rd/lib/gdal_i.lib"

DLLDESTDIR = $$PWD/../bin
DESTDIR = $$PWD/../bin
