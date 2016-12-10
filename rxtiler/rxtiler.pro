#-------------------------------------------------
#
# Project created by QtCreator 2016-08-22T09:45:05
#
#-------------------------------------------------

QT += core network opengl widgets gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rxtiler
TEMPLATE = app

DEFINES += RT_EXPORTS

include(../setting.pri)

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
    LIBS += -losg \
        -losgDB \
        -losgUtil \
        -losgGA \
        -losgViewer \
        -losgText \
        -losgWidget \
        -losgQt \
        -lOpenThreads \
        -losgFX
}

HEADERS += \
    Extent.h \
    TileKey.h \
    TileOption.h \
    mainwindow.h \
    datasource.h \
    datasourcegdal.h \
    datasourcetiles.h \
    ProgressBar.h

SOURCES += \
    Extent.cpp \
    TileKey.cpp \
    TileOption.cpp \
    mainwindow.cpp \
    main.cpp \
    datasource.cpp \
    datasourcegdal.cpp \
    datasourcetiles.cpp \
    ProgressBar.cpp

FORMS += \
    mainwindow.ui \
    ProgressBar.ui

LIBS += "E:/Project/rxtiler/osg/3rd/lib/gdal_i.lib"
#LIBS += -lgdal

LIBS += -lproj
LIBS += -lproj_i

