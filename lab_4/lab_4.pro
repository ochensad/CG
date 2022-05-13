QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algorithms.cpp \
    circle_alg.cpp \
    ellipse_alg.cpp \
    error_code.cpp \
    main.cpp \
    mainwindow.cpp \
    point.cpp \
    request.cpp

HEADERS += \
    algorithms.h \
    circle_alg.h \
    colors.h \
    ellipse_alg.h \
    error_code.h \
    mainwindow.h \
    point.h \
    request.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
