QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomDelegate.cpp \
    CustomEclipseItem.cpp \
    CustomLineItem.cpp \
    GraphEdge.cpp \
    MatrixWidget.cpp \
    Scene.cpp \
    WorkingField.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CustomDelegate.h \
    CustomEclipseItem.h \
    CustomLineItem.h \
    GraphEdge.h \
    MatrixWidget.h \
    Scene.h \
    WorkingField.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    GraphV.pro.user \
    resources/Vis.png
    resources/load.png
    README.md

RESOURCES += \
    resources/resources.qrc \

#RC_FILE = recources.rc

SUBDIRS += \
    GraphV.pro
