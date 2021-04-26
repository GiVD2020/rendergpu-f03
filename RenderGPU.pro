QT       += core gui opengl

TARGET = RenderGPU
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Geometry/Animation.cpp \
    Geometry/Cara.cpp \
    Geometry/ColorMapStatic.cpp \
    Geometry/Light.cpp \
    Geometry/Material.cpp \
    Geometry/Object.cpp \
    Geometry/Scene.cpp \
    Geometry/TG.cpp \
    Geometry/TranslateTG.cpp \
    GeometryBuilders/Builder.cpp \
    Main.cpp \
    Renders/Camera.cpp \
    Renders/GLWidget.cpp \
    Renders/MainWindow.cpp \
    library/Common.cpp

HEADERS += \
    Geometry/Animation.h \
    Geometry/Cara.h \
    Geometry/ColorMap.h \
    Geometry/ColorMapStatic.h \
    Geometry/Light.h \
    Geometry/Material.h \
    Geometry/Object.h \
    Geometry/Scene.h \
    Geometry/TG.h \
    Geometry/TranslateTG.h \
    GeometryBuilders/Builder.h \
    IncludeWin32/GL/glut.h \
    Renders/Camera.h \
    Renders/GLWidget.h \
    Renders/MainWindow.h \
    library/Common.h \
    library/mat.h \
    library/vec.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    libWin32/glut.dll \
    libWin32/glut.lib \
    libWin32/glut32.dll \
    libWin32/glut32.lib
