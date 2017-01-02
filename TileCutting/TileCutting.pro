QT       += core gui widgets

TARGET = TileCutting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    TileCuttImage.cpp \
    TileCuttDEM.cpp \
    TileCuttInfo.cpp

HEADERS  += mainwindow.h \
    TileCuttImage.h \
    TileCuttDEM.h \
    TileCuttInfo.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/../sdk/osg/x64/include
INCLUDEPATH += $$PWD/../sdk/3rd/x64/include


LIBS += -L"$$PWD/../sdk/osg/x64/lib"
LIBS += -L"$$PWD/../sdk/3rd/x64/lib"

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
}

LIBS += "E:/workspace/GitProject/TileCuttingTool/sdk/3rd/x64/lib/gdal_i.lib"

DLLDESTDIR = $$PWD/../bin
DESTDIR = $$PWD/../bin
