
OSGPATH = $$PWD/osg
OSG3RDPATH = $$OSGPATH/3rd

INCLUDEPATH += $$OSGPATH/include
INCLUDEPATH += $$OSG3RDPATH/include


LIBS += -L"$$OSGPATH/lib"
LIBS += -L"E:/Project/rxtiler/osg/3rd/lib"

DLLDESTDIR = $$PWD/bin
DESTDIR = $$PWD/bin

#设置Obj输出目录与Target
SUFFIX_STR =
 CONFIG(debug, debug|release) {
     message(Building $$TARGET with debug mode.)
     SUFFIX_STR =d

 }else {
}
TARGET              = $$TARGET$$SUFFIX_STR

